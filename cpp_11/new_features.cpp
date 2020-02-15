/*
This code file demonstrate some new features introduced in C++11,
if we need to switch the compile option between C++98 and C++11,
just modify the below lines in CMakeLists.txt

    set (CMAKE_CXX_STANDARD 98)

or 

    set (CMAKE_CXX_STANDARD 11)

*/

#include <vector>
#include <iostream>
#include "move_semantics.h"

#define USE_CPP_11   //if this macro is open, and compile with C++ 98, compile errors happen

using namespace std;

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

void Run()
{
    //nullptr_demo();
    //uniform_initialization_demo();
    //for_demo();
    move_demo();
}