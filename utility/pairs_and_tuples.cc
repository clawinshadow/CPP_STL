#include "pairs_and_tuples.h"

#include <iostream>
#include <utility>
#include <functional>
#include <complex>
#include <vector>

using namespace std;

namespace utility {
namespace pairs_tuples {

class Foo {
public:
    Foo (tuple<int, float>) {
        cout << "Foo::Foo(tuple)" << endl;
    }

    template <typename... Args>
    Foo (Args... args) {
        cout << "Foo::Foo(args...)" << endl;
    }
};

void pairs_demo()
{
    // --How to initialize a pair
    // 1. Most trivial initialization
    std::pair<int, float> int_float_pair(2, 3.14);

    // 2. Use piecewise construction (一般用于复杂类型的初始化)
    //      template <typename... Args1, typename... Args2>
    //      pair(piecewise_construct_t,
    //          tuple<Args1...> first_args,
    //          tuple<Args2...> second_args);
    //    即这种构造函数接收三个参数，第一个是标志位piecewise_construct
    //    第二个和第三个都是一个std::tuple<>, 包含数目不等的参数，用于初始化
    //    pair的第一个和第二个类型，即 Args1...用于初始化pair的 T1, 
    //    Args2...用于初始化pair的T2
    std::tuple<int, float> int_float_tuple(2, 4.0);
    // construct Foo with the tuple as a whole
    std::pair<int, Foo> int_foo_pair(2, int_float_tuple);
    // construct Foo with the ELEMENTS of the tuple
    std::pair<int, Foo> int_foo_pair_2(std::piecewise_construct, make_tuple(2), int_float_tuple);

    // 3. std::make_pair(), 可以不用写具体的类型了，由编译器自己推断
    auto int_char_pair = std::make_pair(42, 'E');
    //    但也有缺点，比如下面的例子推断出来的类型就是double 而不是 float
    auto int_double_pair = std::make_pair(42, 7.9); // not a std::pair<int, float>
    //    pair的初始化还可以接受 move semantics
    string a_str = "A String";
    string b_str = "B String";
    auto string_move_pair = std::make_pair(std::move(a_str), std::move(b_str));
    //    will be empty string
    printf("a_str: %s, b_str: %s\n", a_str.c_str(), b_str.c_str());

    //    pair的初始化还可以接受引用传递，需要include functional
    int i = 0;
    auto int_ref_pair = std::make_pair(std::ref(i), std::ref(i));
    //    then modify the pair values
    ++int_ref_pair.first;
    ++int_ref_pair.second;
    //std::cout << "int_ref_pair: " << int_ref_pair << std::endl;
    std::cout << "i = " << i << std::endl;
    // 另一种方式将pair中的某个值绑定在一个变量上
    auto doubles_pair = std::make_pair(3.1, 1.5);
    double d;
    std::tie(std::ignore, d) = doubles_pair; // extract the second value to d
    std::cout << "doubles_pair: " << doubles_pair.first << ", " << doubles_pair.second << std::endl;
    std::cout << "d = " << d << std::endl;
    std::get<1>(doubles_pair) = 9.9;
    std::cout << "d = " << d << std::endl; //that's weird, 似乎还是个值拷贝

    // 另一种获取pair内的值的方式，
    double d1 = std::get<0>(doubles_pair);
    double d2 = std::get<1>(doubles_pair);
    printf("d1: %f, d2: %f\n", d1, d2);

    // pairs comparison, 以 first 为主
    auto pair_1 = std::make_pair(2, 6);
    auto pair_2 = std::make_pair(3, 4);
    std::cout << (pair_1 < pair_2) << std::endl;  //true, coz 2 < 3

    auto pair_3 = std::make_pair(2, 4);
    std::cout << (pair_1 < pair_3) << std::endl;  //false. coz 6 > 4
}

void tuple_demo()
{
    // 基本上是靠 make_tuple() 创建，然后 get<0>, get<1>, ... 来取值
    // create a four-element tuple
    // - elements are initialized with default value (0 for fundamental types)
    tuple<string, int, int, complex<double>> t;
    // create and initialize a tuple explicitly
    tuple<int, float, string> t1(41,6.3,"nico");
    // ‘‘iterate’’ over elements:
    cout << get<0>(t1) << " ";
    cout << get<1>(t1) << " ";
    cout << get<2>(t1) << " ";
    cout << endl;
    // create tuple with make_tuple()
    // - auto declares t2 with type of right-hand side
    // - thus, type of t2 is tuple
    auto t2 = make_tuple(22,44,"nico");
    // assign second value in t2 to t1
    get<1>(t1) = get<1>(t2);
    // comparison and assignment
    // - including type conversion from tuple<int,int,const char*>
    // to tuple<int,float,string>
    if (t1 < t2) { // compares value for value
        t1 = t2;
        // OK, assigns value for value
    }

    // 可以用 initializer list 初始化，但是不能用它来赋值
    std::tuple<int,double> tuple_1(42,3.14);// OK, old syntax
    std::tuple<int,double> tuple_2{42,3.14};// OK, new syntax
    // std::tuple<int,double> tuple_3 = {42,3.14}; // ERROR
    // std::vector<std::tuple<int,float>> v { {1,1.0}, {2,2.0} };// ERROR
    // 但是对pair可以
    std::vector<std::pair<int, float> > v1{ {1,1.0}, {2,2.0} };// OK

    // 几个有用的tuple helper函数
    // • tuple_size<tupletype>::value yields the number of elements.
    // • tuple_element<idx,tupletype>::type yields the type of the element with index idx (this
    //       is the type get() returns).
    // • tuple_cat() concatenates multiple tuples into one tuple.
    //constexpr typename std::tuple<int, float, std::string> tuple_type;
    using my_tuple = std::tuple<int, float, std::string>;
    constexpr auto tuple_size = std::tuple_size<my_tuple>::value; // yield 3
    std::cout << tuple_size << std::endl;
    using CT = std::tuple_element<1, my_tuple>::type; // should be float
    float i = 3.3;
    std::cout << std::boolalpha; //特别有用，控制台里面输出的值是bool类型时，显示true/false, 而不是 0/1
    std::cout << std::is_same<CT, decltype(i)>::value << std::endl;

    int n;
    auto tt = std::tuple_cat(std::make_tuple(42, 7.7, "hello"), std::tie(n));
    printf("(%d, %f, %s, %d)\n", std::get<0>(tt), std::get<1>(tt), std::get<2>(tt),
        std::get<3>(tt));
    n = 4;
    printf("(%d, %f, %s, %d)\n", std::get<0>(tt), std::get<1>(tt), std::get<2>(tt),
        std::get<3>(tt)); //the last element will be 4
}

} //namespace pairs_tuples
} //namespace utility