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

void Run()
{
    nullptr_demo();
}