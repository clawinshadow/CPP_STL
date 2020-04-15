#include "binders.h"
#include "helper.h"

#include <functional>
#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <memory>

using namespace std;

namespace function_objects {
namespace binders {

/*
 * 主要是两个概念 : predefined function objects 和 binders
 * C++ STL 提供这两个东西，主要就是为了方便用户自由组合更复杂的 function objects.
 * the C++ standard library provides many predefined function objects and binders that allow you to
 * compose them into more sophisticated function objects.
   This ability, called functional composition, requires fundamental function objects and adapters

   -- Predefined function objects --
    Expression                      Effect
    negate<type>()                  - param
    plus<type>()                    param1 + param2
    minus<type>()                   param1 - param2
    multiplies<type>()              param1 * param2
    divides<type>()                 param1 / param2
    modulus<type>()                 param1 % param2
    equal_to<type>()                param1 == param2
    not_equal_to<type>()            param1 != param2
    less<type>()                    param1 < param2
    greater<type>()                 param1 > param2
    less_equal<type>()              param1 <= param2
    greater_equal<type>()           param1 >= param2
    logical_not<type>()             !    param
    logical_and<type>()             param1 && param2
    logical_or<type>()              param1 || param2
    bit_and<type>()                 param1 & param2
    bit_or<type>()                  param1 | param2
    bit_xor<type>()                 param1 ^ param2

    Function Adapter: is a function object that enables the composition of function objects with each
                      other, with certain values, or with special functions

    C++11 共提供以下几种 Function Adapter:
    Expression              Effect
    bind(op,args...)        Binds args to op
    mem_fn(op)              Calls op() as a member function for an object or pointer to object
    not1(op)                Unary negation: !op(param)
    not2(op)                Binary negation: !op(param1,param2)

    而 Binder 就是其中最重要的一种 function adapter
    The most important adapter is bind(). It allows you to:
    • Adapt and compose new function objects out of existing or predefined function objects
    • Call global functions
    • Call member functions for objects, pointers to objects, and smart pointers to objects
    In general, bind() binds parameters for callable objects.
    Thus, if a function, member function, function object, or lambda requires some parameters,
    you can bind them to specific or passed arguments：
    - Specific arguments you simply name.
    - For passed arguments, you can use the predefined placeholders _1, _2, ... defined in namespace std::placeholders.
 */

void vanilla_bind()
{
    auto plus10 = std::bind(std::plus<int>(),
                            std::placeholders::_1,
                            10);  //重新组合成了一个新的function object
    std::cout << "+10: " << plus10(7) << std::endl;  //should be 10 + 7 = 17

    //嵌套的bind
    auto plus10times2 = std::bind(std::multiplies<int>(),
                                  std::bind(std::plus<int>(), 10, std::placeholders::_1),
                                  2); // (x + 10) * 2
    std::cout << "+10 * 2: " << plus10times2(7) << std::endl; // should be 34

    auto pow3 = std::bind(std::multiplies<int>(),
                          std::bind(std::multiplies<int>(),
                                    std::placeholders::_1,
                                    std::placeholders::_1),
                          std::placeholders::_1); // 一个placeholder可以使用多次
    std::cout << "x*x*x: " << pow3(7) << std::endl;

    auto inversDivide = std::bind(std::divides<double>(),
                                  std::placeholders::_2,
                                  std::placeholders::_1); // 用第二个参数除以第一个参数
    std::cout << "invdiv: " << inversDivide(49,7) << std::endl;

    list<int> coll = {1, 2, 3, 4, 5, 6, 7};
    std::transform(coll.begin(), coll.end(),
                   coll.begin(),
                   std::bind(std::plus<int>(), std::placeholders::_1, 10));
    helper::PRINT_ELEMENT(coll);
}

int plus_10(int val)
{
    return val + 10;
}

// bind() 不止能用于 predefined function objects 的互相组合，还能用来包装自定义的全局函数
void bind_global_function()
{
    list<int> coll = {1, 2, 3, 4};

    std::transform(coll.begin(), coll.end(),
                   coll.begin(),
                   std::bind(plus_10, std::placeholders::_1));
    helper::PRINT_ELEMENT(coll);
}

// bind() calling member functions
class Person {
private:
    string name;
public:
    Person (string _name): name(_name) { };

    void print() const {
        cout << name << endl;
    }

    void print2(const string &_prefix) const {
        cout << _prefix << name << endl;
    }
};

void bind_member_function()
{
    vector<Person> coll = { Person("Tick"), Person("Trick"), Person("Track") };

    // 此处 _1 表示每个Person元素
    for_each(coll.begin(), coll.end(), std::bind(&Person::print, std::placeholders::_1));
    cout << endl;

    // 如果有额外的参数，往后面排
    for_each (coll.begin(), coll.end(), bind(&Person::print2, std::placeholders::_1, "Person: "));
    cout << endl;

    // for temporary person
    std::bind(&Person::print, std::placeholders::_1)(Person("Temp Person"));
    cout << endl;

    // it also works for object pointers and smart pointers
    Person *p1 = new Person("Fan");
    Person *p2 = new Person("Li");
    std::vector<Person*> ptr_coll;
    ptr_coll.push_back(p1);
    ptr_coll.push_back(p2);

    for_each (ptr_coll.begin(), ptr_coll.end(), bind(&Person::print2, std::placeholders::_1, "Pointers to Person: "));
    cout << endl;

    delete p1;
    delete p2;

    std::shared_ptr<Person> shared_p1 = std::make_shared<Person>(Person("Huang"));
    std::shared_ptr<Person> shared_p2 = std::make_shared<Person>(Person("Li"));
    std::vector<std::shared_ptr<Person>> shared_ptr_coll;
    shared_ptr_coll.push_back(shared_p1);
    shared_ptr_coll.push_back(shared_p2);

    for_each (shared_ptr_coll.begin(), shared_ptr_coll.end(), bind(&Person::print2, std::placeholders::_1, "Pointers to Person: "));
    cout << endl;

    // mem_fn() adapter: 可以省略掉 std::placeholder
    //     For member functions, you can also use the mem_fn() adapter, whereby you can skip the placeholder
    //     for the object the member function is called for
    // 但是mem_fn()不支持额外的参数，比如print2的调用还是必须得使用bind()才能实现
    for_each (coll.begin(), coll.end(), std::mem_fn(&Person::print));
    cout << endl;
}

void Run()
{
    vanilla_bind();
    bind_global_function();
    bind_member_function();

    //not1(), not2() 这两个其实并没有什么实用的场景

    /* deprecated function adapters
     *  Expression              Effect
        bind1st(op,arg)         Calls op(arg,param)
        bind2nd(op,arg)         Calls op(param,arg)
        ptr_fun(op)             Calls *op(param) or *op(param1,param2)
        mem_fun(op)             Calls op() as a member function for a pointer to an object
        mem_fun_ref(op)         Calls op() as a member function for an object
        not1(op)                Unary negation: !op(param)
        not2(op)                Binary negation: !op(param1,param2)
     */
}

}
}