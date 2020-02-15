#include <stdexcept>
#include <limits>
#include <typeinfo>
#include <exception>
#include <cstdlib>
#include "exceptions.h"

using namespace std;

namespace cpp_11 {
namespace exceptions {

/*
C++ 里面的异常处理机制和C#的区别不大，但有以下几个地方需要注意
1. try..catch之后没有 finally 模块，释放资源通过 stack unwinding (堆栈解退) 来释放，所以我们写代码要注意 exception safety
   这是个挺深奥的话题，比较广泛的一个应用是我们在申请一个堆资源(malloc, new)的时候，多使用智能指针，可参考这篇文章：
   https://docs.microsoft.com/en-us/cpp/cpp/how-to-design-for-exception-safety?view=vs-2019
2. 一般不建议catch所有的异常，see below:
    try {
        throw CSomeOtherException();
    }
    catch(...) {
        // Catch all exceptions - dangerous!!!
        // Respond (perhaps only partially) to the exception, then
        // re-throw to pass the exception to some other handler
        // ...
        throw;
    }
3. Exceptions vs. Assertions
   这两种机制都用于检查运行时的错误，但还是有很多不同的地方
   - Use asserts to test for conditions during development that should never be true if all your code is correct
   - Use exceptions to check error conditions that might occur at run time even if your code is correct, 
     for example, "file not found" or "out of memory."
   
   - An assert stops execution at the statement so that you can inspect the program state in the debugger; 
   - An exception continues execution from the first appropriate catch handler
   
   简而言之，Assertion用于检查代码错误造成的运行时错误，这种错误一旦发生，没有恢复的必要，直接回头看代码哪里错了。
   而Exception用于防备代码无法控制的运行时错误，可能需要让程序继续运行的
*/

// normal exception handling
void MyFunc(int c)
{
    if (c > numeric_limits< char> ::max())
        throw invalid_argument("MyFunc argument too large.");
    //...
}

int normal_exception_handling_demo()
{
    try
    {
        MyFunc(256); //cause an exception to throw
    }
    catch (invalid_argument& e)
    {
        cerr << e.what() << endl;
        return -1;
    }
    //...
    return 0;
}

// if exception not handled, it will call std::terminate(), and users can DIY their own terminate function

// compile with: /EHsc
void term_func() {
   cout << "term_func was called by terminate." << endl;
   exit( -1 );
}

int exception_terminate_demo() {
   try
   {
      set_terminate( term_func );
      throw "Out of memory!"; // No catch handler for this exception
   }
   catch( int )
   {
      cout << "Integer exception raised." << endl;
   }
   return 0;
}

// stack unwinding: 从抛出异常的那一个点，到catch执行前，这中间所有的变量都会被依次销毁
//    In the C++ exception mechanism, control moves from the throw statement to the first catch statement that can handle the thrown type. 
//    When the catch statement is reached, all of the automatic variables that are in scope between the throw and catch statements are destroyed 
//    in a process that is known as stack unwinding.

class MyException{};
class Dummy
{
    public:
    Dummy(string s) : MyName(s) { PrintMsg("Created Dummy:"); }
    Dummy(const Dummy& other) : MyName(other.MyName){ PrintMsg("Copy created Dummy:"); }
    ~Dummy(){ PrintMsg("Destroyed Dummy:"); }
    void PrintMsg(string s) { cout << s  << MyName <<  endl; }
    string MyName;
    int level;
};

void C(Dummy d, int i)
{
    cout << "Entering FunctionC" << endl;
    d.MyName = " C";
    throw MyException();

    cout << "Exiting FunctionC" << endl;
}

void B(Dummy d, int i)
{
    cout << "Entering FunctionB" << endl;
    d.MyName = " B";
    C(d, i + 1);
    cout << "Exiting FunctionB" << endl;
}

void A(Dummy d, int i)
{
    cout << "Entering FunctionA" << endl;
    d.MyName = " A" ;
  //  Dummy* pd = new Dummy("new Dummy"); //Not exception safe!!!
    B(d, i + 1);
 //   delete pd;
    cout << "Exiting FunctionA" << endl;
}

int stack_unwinding_demo()
{
    cout << "Entering main" << endl;
    try
    {
        Dummy d(" M");
        A(d,1);
    }
    catch (MyException& e)
    {
        cout << "Caught an exception of type: " << typeid(e).name() << endl;
    }

    cout << "Exiting main." << endl;
    char c;
    cin >> c;
}

/* Output:
    Entering main
    Created Dummy: M
    Copy created Dummy: M
    Entering FunctionA
    Copy created Dummy: A
    Entering FunctionB
    Copy created Dummy: B
    Entering FunctionC
    Destroyed Dummy: C
    Destroyed Dummy: B
    Destroyed Dummy: A
    Destroyed Dummy: M
    Caught an exception of type: class MyException
    Exiting main.

*/

// Exception specifications: throw(), noexcept()
// 一般用在某个方法后面，表示希望这个方法抛出哪些类型的异常，或者不会抛出异常，然后编译器会根据这个信息来优化代码
//      The compiler can use this information to optimize calls to the function, 
//      and to terminate the program if an unexpected exception escapes the function.
// 1. dynamic exception specification: throw(typeid, typeid, ...)，C++11之后就过期了, 
//    如果函数内抛出的异常不在throw(..)指定的类型里面，则会调用 std::unexpected() 方法

class X {};
class Y {};
class Z : public X {};
class W {};
 
void f() throw(X, Y) 
{
    int n = 0;
    if (n) throw X(); // OK
    if (n) throw Z(); // also OK
    throw W(); // will call std::unexpected()
}
 
int dynamic_exception_specifications_demo() {
  std::set_unexpected([]{
      std::cout << "That was unexpected" << std::endl; // flush needed
      std::abort();
  });
  f();
}

// 2. noexcept specification: Since C++11, noexcept / noexcept(true) / noexcept(constant-expression)
//    表示该方法不抛出异常，或者只有constant-expression为true时才抛出异常，
//    If an exception does exit the outer scope of a function marked noexcept, std::terminate is invoked immediately, 
//    and there is no guarantee that destructors of any in-scope objects will be invoked
} 
}