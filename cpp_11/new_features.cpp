/*
This code file demonstrate some new features introduced in C++11,
if we need to switch the compile option between C++98 and C++11,
just modify the below lines in CMakeLists.txt

    set (CMAKE_CXX_STANDARD 98)

or 

    set (CMAKE_CXX_STANDARD 11)

*/

#include <bitset>
#include <vector>
#include <iostream>
#include "move_semantics.h"
#include "exceptions.h"
#include "lambdas.h"

#define USE_CPP_11   //if this macro is open, and compile with C++ 98, compile errors happen

using namespace std;

namespace cpp_11 {

// Syntax Cleanup 1: Spaces in Template Expressions
vector<vector<int> > list_1;      // OK in each C++ version
#ifdef USE_CPP_11
    vector<vector<int>> list_2;   // OK since C++11, compile error in C++98
#endif

// nullptr VS (NULL or 0)
/* C++11 lets you use nullptr instead of 0 or NULL to specify that a pointer refers to no value (which
   differs from having an undefined value). This new feature especially helps to avoid mistakes that
   occurred when a null pointer was interpreted as an integral value.
*/
void f(int val) { cout << "call f(int)" << endl; }
void f(void* ptr) { cout << "call f(void*)" << endl; }
void nullptr_demo()
{
    f(0);
#ifdef USE_CPP_11
    // f(NULL); // in both C++98 or C++11, cause compile error: call of overloaded ‘f(NULL)’ is ambiguous
    f(nullptr);
#endif
}

// new keyword: auto
#ifdef USE_CPP_11
auto i = 42; //i has type int
auto l = [] (int x) -> bool { return false; }; // l has type lambda
#endif

// uniform initialization & initializer list
/* Before C++11, Initialization could happen with parentheses, braces, and/or assignment operators, 
   For this reason, C++11 introduced the concept of uniform initialization, which means that for
   any initialization, you can use one common syntax. This syntax uses braces
*/ 

struct P
{
public:
    P(int, int) {}
    explicit P(int, int, int) {}
};

void uniform_initialization_demo()
{
    // OK in each C++ version
    int i;   //undefined value
    int j(1);
    int k = 5;
    int arr[] = {1, 2, 3, 4, 5};
    std::cout << "i: " << i << std::endl; //compile error, because i was not initialized

#ifdef USE_CPP_11
    // ok since C++11, braces means initializer list
    int i2{}; 
    int j2{1};
    int k2 = {5};
    int arr2[]{1, 2, 3, 4, 5};
    std::cout << "i2 = " << i2 << std::endl; // initializer list forces value-initialization, initialize to zero or nullptr, instead of undefined value.
#endif

    // but initializer list does not support narrowing initialization, like double -> int
    int x1(5.3);
    int x2 = 5.3;
#ifdef USE_CPP_11
    // int x3{5.3};    //compile error of narrowing initialization
    // int x4 = {5.3}; //compile error
#endif    

    // initializer list make "explicit" now also becomes relevant for constructors taking more than one argument
    P p1(1, 2);                  //OK -> call P(int, int)
    P p2{1, 2};                  //OK -> call P(int, int)
    P p3{1, 2, 3};               //OK -> call P(int, int int) without implicit type conversion
    P p4 = {4, 5};               //OK -> call P(int, int) with implicit type conversion allowed
    // P p5 = {4, 5, 6};            //ERROR due to explicit (implicit type conversion forbidden)
}

// Range-based for loops
void for_demo()
{
    for (int i: {1, 2, 3, 4, 5})
    {
        std::cout << i << std::endl;
    }

    // reference
    std::vector<double> vec{1.0, 2.1, 3.3}; 
    for (auto &elem: vec)
    {
        elem *= 2;
    }
    std::cout << "vec[1] = " << vec[1] << std::endl;

    // const reference, avoid copy constructor & destructor during iteration
    // for (const auto &elem: collection)..
}

// New string literals: R"..."
const std::string str = R"(
abc
def
)";

// New keyword: constexpr
// Since C++11, constexpr can be used to enable that expressions be evaluated at compile time
// 下面方法前面的constexpr关键字也可以不写，不影响后面的使用
constexpr int square(int x)
{
    return x * x;
}

// templates new features
// 1. variadic template: 
//    Since C++11, templates can have parameters that accept a variable number of template arguments
void print()
{
}

template <typename T, typename... TArgs>
void print(const T& firstArg, const TArgs&... args)
{
    std::cout << firstArg << std::endl; // print first argument
    print(args...);                     // call print() for remaining arguments
}

// 2. Alias template
/*
template <typename T>
using Vec = std::vector<T, MyAlloc<T>>; // standard vector using own allocator

    Vec<int> coll;
is equivalent to
    std::vector<int,MyAlloc<int>> coll;
*/

// New keyword: decltype
// By using the new decltype keyword, you can let the compiler find out the type of an expression
// 主要是为了替换以前常用的 typeof 这个特性
// 典型应用场景：
//      template <typename T1, typename T2>
//      auto add(T1 x, T2 y) -> decltype(x+y);

// Scoped Enumerations
// C++11 allows the definition of scoped enumerations — also called strong enumerations, 
// or enumeration classes — which are a cleaner implementation of enumeration values (enumerators) in C++.
// For example:
enum class Salutaion: char {mr, ms, co, none};
// 主要有两个区别
// 1. enum后跟了个class
// 2. 枚举的定义之前有一个char关键字指明了枚举的underlying_type
// 他们的作用：
// 1. Implicit conversions to and from int are not possible.
// 2. Values like mr are not part of the scope where the enumeration is declared. You have to use
//    Salutation::mr instead
// 3. You can explicitly define the underlying type (char here) and have a guaranteed size (if you skip
//    “: char” here, int is the default).
Salutaion sa = Salutaion::mr;
// Salutaion sb = ms; //compile error
// int sc = Salutaion::co; //compile error

// 4. with the type trait std::underlying_type, you can evaluate the underlying type of an
//    enumeration type

// New fundamental datatypes in C++11
//      • char16_t and char32_t 
//      • long long and unsigned long long
//      • std::nullptr_t 

// Explicit initialization for fundamental types
/*

int i1;         // undefined value
int i2 = int(); // initialized with zero
int i3{};       // initialized with zero (since C++11)
这个在template中很有用，能赋一个默认初始值0，而不是undefined value
template <typename T>
void f()
{
    T x = T();
    ...
}
If a template forces the initialization with zero, its value is so-called zero initialized. 
Otherwise it’s default initialized.

*/

void Run()
{
    //nullptr_demo();
    //uniform_initialization_demo();
    //for_demo();
    //move_feature::move_demo();
    //std::cout << str << std::endl;
    // float a[square(3)];
    // a[8] = 8;

    //exceptions::normal_exception_handling_demo();
    //exceptions::exception_terminate_demo();
    //exceptions::stack_unwinding_demo();
    //exceptions::dynamic_exception_specifications_demo();

    //print(7.5, "hello", std::bitset<16>(377), 42);

    //lambdas::lambdas_demo();
    
}

}