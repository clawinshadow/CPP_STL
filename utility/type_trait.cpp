/*
Type traits, which were introduced with TR1 and extended with C++11, provide a mechanism
to define behavior depending on types. They can be used to optimize code for types that provide
special abilities.
*/

#include "type_trait.h"

#include <iostream>
#include <vector>
#include <type_traits>
#include <functional>                                                                   

namespace utility {
namespace type_trait {

//类似于这种is_pointer, is_fundamental之类的方法都叫做type predicates, 他们都是一元的方法(Unary)
//会返回一个基于 std::integral_constant 的类型，通常是 std::true_type 或者是 std::false_type
//他们的value就是bool类型的true和false

template<typename T>
void foo(const T &val) {
    if (std::is_pointer<T>::value) {
        std::cout << "foo called for a pointer" << std::endl;
    } else
        std::cout << "foo called for a value" << std::endl;
}

void basic_demo() {
    foo<int>(1);
    int *i = new int{ 5 };
    foo<int*>(i);
    // 1. Unary: type predicates, 还有好几十个 std::is_integral<T>, is_enum<T>, is_signed<T>...

    std::cout << "----------------Unary type predicates----------------\n";
    std::cout << std::boolalpha << std::is_pointer<int>::value << '\n';
    std::cout << std::is_pointer<int *>::value << '\n';
    std::cout << std::is_pointer<int[10]>::value << '\n';

    // 2. Traits for type relations, 二元的, is_same<T1, T2>, is_base_of<T, D>, is_convertible<T, T2>...
    std::cout << "----------------Type relations----------------\n";
    std::cout << std::is_same<int, int>::value << "\n";          // true
    std::cout << std::is_same<int, unsigned int>::value << "\n"; // false
    std::cout << std::is_same<int, signed int>::value << "\n";   // true
    std::cout << std::is_assignable<int,int>::value << "\n";          // false
    std::cout << std::is_assignable<int&,int>::value << "\n";         // true
    std::cout << std::is_assignable<int&&,int>::value << "\n";        // false

    // 3. Type modifiers, 加const修饰符, 变成指针类型, 引用类型等等
    std::cout << "----------------Type modifiers----------------\n";
    typedef int T;
    std::cout << std::is_same<T, std::int32_t>::value << std::endl;
    std::cout << std::is_const<T>::value << std::endl;
    typedef std::add_const<T>::type CT;
    std::cout << std::is_same<CT, std::int32_t>::value << std::endl;
    std::cout << std::is_const<CT>::value << std::endl;
    /*
     *  add_pointer<T>::type   // int*
        make_signed<T>::type   // int
        make_unsigned<T>::type // unsigned int
        remove_const<T>::type  // int
        remove_reference<T>::type // int
        remove_pointer<T>::type   // int
     */

    // 4. Other type traits
    // 用于数组的 rank<T>, extent<T, I=0>
    // rank 获取数组的维度
    std::cout << std::rank<int>::value << std::endl;   //0
    std::cout << std::rank<int[5]>::value << std::endl;   //1
    std::cout << std::rank<int[5][7]>::value << std::endl;   //2
    // extent 获取某一个维度的数组长度
    std::cout << std::extent<int>::value << std::endl;   //0
    std::cout << std::extent<int[5]>::value << std::endl;   //5
    std::cout << std::extent<int[7][5]>::value << std::endl;   //7
    std::cout << std::extent<int[7][5], 1>::value << std::endl;   //5
    // 移除某一个维度
    typedef std::remove_extent<int[][7]>::type ONE_DIMENSION_ARRAY; // int[7]
    std::cout << std::rank<ONE_DIMENSION_ARRAY>::value << std::endl; //1
    // 移除所有维度
    typedef std::remove_all_extents<int[5][7]>::type NAKE_INT;  // int
    std::cout << std::boolalpha << std::is_same<NAKE_INT, int>::value << std::endl;
}

int func(int x, int y)
{
    return x * y;
}

void wrappers_demo()
{
    /*
    Class std::reference_wrapper<>, declared in <functional>, is used primarily to “feed” refer-
    ences to function templates that take their parameter by value
    e.g. use std::ref() for an implicit conversion from T to T&
         use std::cref() for an implicit conversion from T to const T&
    另外, reference_wrapper<T> allows you to use references as first-class objects
    */
    //std::vector<int&> coll; // Error
    std::vector<std::reference_wrapper<int>> list;
    int a = 3;
    int b = 3;
    list.push_back(a);
    list.push_back(b);

    for (int l : list)
    {
        std::cout << l << std::endl;
    }

    b = 5;
    for (int l : list)
    {
        std::cout << l << std::endl;
    }

    /*
    Function Type Wrappers: std::function<>
    This class allows you to use callable objects (functions, member functions, function objects, and lambdas)
    as first-class objects.
    */
    std::vector<std::function<int(int, int)>> tasks;
    tasks.push_back(func);
    tasks.push_back([](int x, int y) -> int { return x * y; } );

    for (auto f: tasks)
        std::cout << f(5, 6) << std::endl;

    //要先初始化f之后才能使用
    try {
        std::function<int(int, int)> f;
        f(33, 66); // throws std::bad_function_call
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    std::function<int(int, int)> f = func;  //OK
    std::cout << f(33, 55) << std::endl;
}

} //namespace type_trait
} //namespace utility