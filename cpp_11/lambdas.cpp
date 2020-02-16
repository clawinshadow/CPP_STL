#include "lambdas.h"
#include <iostream>
#include <functional>

namespace cpp_11 {
namespace lambdas {

/*
Lambdas was introduced in C++11

[] : called "lambda introducer"

syntax:
either
    [...] {...}
or
    [...] (...) mutable_opt throwSpec_opt -> retType_opt {...}

*/

std::function<int(int, int)> returnLambda()
{
    return [] (int x, int y) -> int {
        return x * y;
    };
}

void lambdas_demo()
{
    // call it directly
    [] { std::cout << "minimal lambda funcion" << std::endl; } ();
    // pass it to an object to get called
    auto l = [] { std::cout << "lambda funcion with an object" << std::endl; };
    l();
    // lambda function with parameters
    auto l2 = [] (const std::string& s) {
        std::cout << s << std::endl;
    };
    l2("lambda function with a string parameter");
    // lambda function with a return type
    auto l3 = [] () -> double { return 42; };
    l3();

    // Capture (Access to outer scope)
    // lambda函数的参数是用在园括号里面的，但Capture是放在中括号里面的，表示访问当前scope外部的某些变量
    // • [=] means that the outer scope is passed to the lambda by value. 
    //       Thus, you can read but not modify all data that was readable where the lambda was defined.
    // • [&] means that the outer scope is passed to the lambda by reference. 
    //       Thus, you have write access to all data that was valid when the lambda was defined, provided that you had write access there.
    int x = 0;
    int y = 42;
    auto l_capture = [x, &y] { //省略=号
        std::cout << "x: " << x << std::endl;
        std::cout << "y: " << y << std::endl;
        ++y; // OK
        //++x; // Compile error, can't modify a capture passed by value
    };
    x = y = 77;
    l_capture();
    l_capture();
    // output: x will always be 0, 因为在lambda函数体内，它是作为原始值0的值拷贝传进去的
    //         即便之后x在out scope被改为了77, 在函数体内它依然一直是0
    //         y 就不一样了，它是作为引用传递的，外面变了，里面就会跟着变，并且lambda函数体内
    //         还可以对y进行修改
    std::cout << "final y: " << y << std::endl;
    
    //那么如果我们既想将capture作为值传递，又想在lambda函数体内更改它怎么办呢
    //使用mutable修饰lambda函数
    int id = 0;
    auto f = [id] () mutable {
        std::cout << "id: " << id << std::endl;
        ++id;// OK
    };
    id = 42;
    f();
    f();
    f();
    std::cout << id << std::endl;

    // Type of lambdas:
    // The type of a lambda is an anonymous function object (or functor) that is unique for each lambda expression
    // 为了声明这种类型的对象，一般像前面用auto，或者decltype(), 或者用标准库中的std::function来声明
    // 参考前面的 returnLambda() 函数的定义

    auto lf = returnLambda();
    std::cout << lf(6, 10) << std::endl;
}

}
}