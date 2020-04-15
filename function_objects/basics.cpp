#include "basics.h"
#include "helper.h"

#include <functional>
#include <iostream>
#include <algorithm>
#include <set>
#include <string>
#include <list>

using namespace std;

namespace function_objects {
namespace basics {

/*
 * Concept:
 * A function object, or functor, is an object that has operator () defined so that in the following example
    FunctionObjectType fo;
    ...
    fo(...);

   At first, you could consider a function object as an ordinary function that is written in a more complicated way
   本来一个普通的函数是这样的
    void fo() {
        statements
    }
   使用function object的话就变成了这样：
    class FunctionObjectType fo
    {
    public:
        void operator() () {
            statements..
        }
    }

   这么定义看起来复杂，但它有几个优点：
   1. A function object might be smarter because it may have a state (associated members that in-
      fluence the behavior of the function object).
      In fact, you can have two instances of the same function object class, which may have different states at the same time.
      This is not possible for ordinary functions.
   2. Each function object has its own type.
      Thus, you can pass the type of a function object to a template to specify a certain behavior,
      and you have the advantage that container types with different function objects differ.
   3. A function object is usually faster than a function pointer.
 */

struct Person {
    string firstname;
    string lastname;

    Person(string _fn, string _ln) {
        firstname = _fn;
        lastname = _ln;
    }
};

class PersonSortingCriteria {
public:
    bool operator() (const Person &_p1, const Person &_p2) const {
        return _p1.lastname < _p2.lastname ||
                (_p1.lastname == _p2.lastname &&
                 _p1.firstname < _p2.firstname);
    }
};

void function_objects_sorting_criteria()
{
    set<Person, PersonSortingCriteria> coll;  // create a set with special sorting criterion

    coll.insert(Person("huang", "fan"));
    coll.insert(Person("chen", "fan"));
    coll.insert(Person("jing", "li"));

    for (auto pos = coll.cbegin(); pos != coll.cend(); ++pos) {
        cout << "Person: " << pos->firstname << ", " << pos->lastname << endl;
    }

    cout << endl;
}

/*
 * function objects with internal state
 */

class IntSequence {
private:
    int value;
public:
    IntSequence(int val): value(val) { };

    int operator() () {
        return ++value;
    }
};

void function_objects_internal_state()
{
    list<int> coll;

    // insert values from 1 to 9
    generate_n(back_inserter(coll),
            9,
            IntSequence(1));
    helper::PRINT_ELEMENT(coll);

    // replace second to last element but one with values starting at 100
    generate(next(coll.begin()),
             prev(coll.end()),
             IntSequence(100));
    helper::PRINT_ELEMENT(coll);

    /*
     * By default, function objects are passed by value rather than by reference.
     * Thus, the algorithm does not change the state of the function object.
     * 默认情况下，每个function object被使用时都是一个新的实例, 即便是同一个function object, 被多次调用
     * 也是复制了多份，互相不影响彼此的内部状态
     */
    list<int> coll2;
    IntSequence seq(1);

    //insert sequence beginning with 1
    generate_n(back_inserter(coll2), 9, seq);

    //insert sequence beginning with 1 again
    generate_n(back_inserter(coll2), 9, seq);
    helper::PRINT_ELEMENT(coll2);

    /*
     * 如果非要将 function object 以引用传递，那也是有办法的
     */
    list<int> coll3;
    IntSequence seq2(1);

    //模板参数里面声明好是按引用调用的
    generate_n<back_insert_iterator<list<int>>, int, IntSequence&>(back_inserter(coll3), 4, seq2);
    helper::PRINT_ELEMENT(coll3);

    generate_n(back_inserter(coll3), 4, IntSequence(100)); //another IntSequence
    helper::PRINT_ELEMENT(coll3);

    generate_n(back_inserter(coll3), 4, seq2); // 续上之前的seq2，从6开始添加元素
    helper::PRINT_ELEMENT(coll3);

    generate_n(back_inserter(coll3), 4, seq2); // seq2的内部状态依然还是没变，继续从6开始
    helper::PRINT_ELEMENT(coll3);
}

/*
 * The effort involved with passing a function object by reference in order to access its final state is
   not necessary if you use the for_each() algorithm.
   for_each() has the unique ability to return its function object (no other algorithm can do this).
   Thus, you can query the state of your function object by checking the return value of for_each()
   之前我很费劲的才实现了将function object作为引用传递给算法，但是对于 for_each 这个算法来说，我们可以直接通过获取它的返回值
   来获取一开始传入的 function object 的最终状态。不管for_each的过程中function object内部发生了什么，我们都可以获得它最终
   的状态。也只有 for_each 这个算法才支持这个功能
 */

class MeanValue {
private:
    int num;
    int sum;
public:
    MeanValue() : num(0), sum(0) { };

    void operator () (int elem) {
        sum += elem;
        ++num;
    }

    double value() {
        return static_cast<double>(sum) / static_cast<double>(num);
    }
};

// 实际上如果仅仅只是实现这个功能的话，lambda表示式要写起来更容易，但是 function object 相比 lambda 也有几个优点:
// 1. Function objects are more convenient when their type is required, such
//    as for a declaration of a hash function, sorting, or equivalence criterion of associative or unordered
//    containers.
// 2. The fact that a function object is usually globally introduced helps to provide them in
//    header files or libraries, whereas lambdas are better for specific behavior specified locally.
void function_objects_for_each()
{
    vector<int> coll = { 1, 2, 3, 4, 5, 6, 7, 8 };

    MeanValue mv = for_each(coll.begin(), coll.end(), MeanValue());  // 获取MeanValue实例的返回值

    std::cout << "MeanValue of coll: "<< mv.value() << std::endl;
}

/*
 * Predicates: functions or function objects that return a Boolean value
 * 要注意使用 predicates 的时候，最好是不要使用带有内部状态的 predicates，否则会带来一些匪夷所思的行为
 * 比如下面的例子中，因为 remove_if 的内部实现会 copy 一次 predicate，所以将第三个元素删除了两次
 * 我们在使用 predicate 的时候，切记不要依赖于它的内部状态
 *
 * A predicate should always be stateless
 */

// function object that returns true for the nth call
class Nth {
private:
    int nth;
    int count;
public:
    Nth (int n) : nth(n), count(0) { }

    bool operator() (int) {
        return ++count == nth;
    }
};

void predicate_misuse()
{
    list<int> coll = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    helper::PRINT_ELEMENT(coll, "original collection: ");

    // remove third element
    list<int>::iterator pos;
    pos = remove_if(coll.begin(), coll.end(),Nth(3));
    coll.erase(pos,coll.end());

    // remove criterion
    helper::PRINT_ELEMENT(coll, "collection after removed third: "); // 3 和 6都被删除了
}

void Run()
{
    function_objects_sorting_criteria();
    function_objects_internal_state();
    function_objects_for_each();
    predicate_misuse();
}

}
}