#include "lambdas.h"
#include "helper.h"

#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

namespace function_objects {
namespace lambdas {

//compare with vanilla_bind() in binders.cpp
void vanilla_lambdas()
{
    auto plus10 = [] (int val) -> int { return val + 10; };
    std::cout << "+10: " << plus10(7) << endl;

    auto plus10times2 = [] (int val) -> int {
        return (val + 10) * 2;
    };
    std::cout << "+10 * 2: " << plus10times2(7) << std::endl; // should be 34

    auto pow3 = [] (int i) {
        return i*i*i;
    };
    std::cout << "x*x*x: " << pow3(7) << std::endl;
}

void lambdas_for_stateful_function_objects()
{
    // 定义一个外部变量，作为引用传递给lambda表达式即可
    vector<int> coll = {1, 2, 3, 4, 5};

    long sum = 0;
    for_each(coll.begin(), coll.end(), [&sum] (int elem) { sum += elem; });
    double mean_value = (double)sum / coll.size();

    std::cout << "Mean value: " << mean_value << std::endl;
}

void mutable_lambdas()
{
    // 一般对于外部变量的引用，lambdas表达式默认都是采用 const T 的常量值传递形式
    // 也就是说，默认情况下，我们在lambdas表达式内部无法更改外部变量的值，如果非要改，有两种形式
    // 1. 采用 mutable 标识符
    // 2. 采用 & 符号将外部变量声明为引用
    list<int> coll = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    helper::PRINT_ELEMENT(coll, "coll: ");

    // remove third element
    list<int>::iterator pos;
    int count=0;
    // 本来count是无法修改的，但是声明为 mutable 之后就可以修改了
    // 但是count本身还是以值传递的，所以在remove_if函数体内，依然存在移除了两个元素的问题，即3和6都被移除了
        pos = remove_if(coll.begin(),coll.end(),
                        [count] (int) mutable {
                            return ++count == 3;
                        });

    // 如果我们以引用传递count，就不会有这种 suprising behavior
    //    pos = remove_if(coll.begin(),coll.end(),
    //                    [&count] (int) {
    //                        return ++count == 3;
    //                    });

    coll.erase(pos,coll.end());
    helper::PRINT_ELEMENT(coll, "3rd removed: ");
}

void Run()
{
    vanilla_lambdas();
    lambdas_for_stateful_function_objects();
    mutable_lambdas();

    /*
     * lambdas as Hash Function, Sorting or Equivalence Criterion
     *
     *  class Person {
            ...
        };
        auto hash = [] (const Person& p) {
            ...
        };
        auto eq = [] (const Person& p1, Person& p2) {
            ...
        };

        // create unordered set with user-defined behavior
        unordered_set<Person, decltype(hash), decltype(eq)> pset(10, hash, eq);
     */
}

}
}