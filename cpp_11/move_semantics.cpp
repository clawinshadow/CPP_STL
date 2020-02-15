/* 
One of the most important new features of C++11 is the support of move semantics

1. why do we need move action?
   Consider the following code example:
        void createAndInsert (std::set<X>& coll)
        {
            X x; // create an object of type X
            ...
            coll.insert(x); // insert it into the passed collection
        }
   Then std::set<T> class must provides a member function that creates an internal copy
   of the passed element:
        namespace std {
                template <typename T, ...> class set {
                public:
                    ... insert (const T& v); // copy value of v
                    ...
                };
            }
    now the set class provides "value semantics", copy all the passed arguments
    X x;
    coll.insert(x);    // inserts copy of x
    ...
    coll.insert(x+x); // inserts copy of temporary rvalue
    ...
    coll.insert(x);   // inserts copy of x (although x is not used any longer)
    
    However, for the last two insertions of x, it would be great to specify a behavior that the passed
values (the result of x+x and x) are no longer used by the caller so that coll internally could avoid
creating a copy and somehow move the contents of them into its new elements. Especially when
copying x is expensive — for example, if it is a large collection of strings — this could become a
big performance improvement.
     
    Then C++11 introduced "move semantics"

2. how to use move semantics and what's rvalue reference?
    X x;
    coll.insert(x); // inserts copy of x (OK, x is still used)
    ...
    coll.insert(x+x); // moves (or copies) contents of temporary rvalue
    ...
    coll.insert(std::move(x)); // moves (or copies) contents of x into coll

    With std::move(), declared in <utility>, x can be moved instead of being copied. However,
std::move() doesn’t itself do any moving, but merely converts its argument into a so-called rvalue
reference, which is a type declared with two ampersands: X&&

   std::set类里面先声明一个insert的重载方法，接受右值引用作为参数
           namespace std {
                template <typename T, ...> class set {
                public:
                    ... insert (const T& x); // for lvalues: copies the value
                    ... insert (T&& x);      // for rvalues: moves the value
                };
            }
    
   但是这个重载的insert方法，实际上做不了太多的事情，真正实现move操作的代码还需要写在类型X里面
    class X {
    public:
        X (const X& lvalue); // copy constructor
        X (X&& rvalue);      // move constructor
        ...
    };
   所以一般是在 move constructor 或者 move assignment 中实现move的操作

   下面例子中的vector对应上面的set类，string对应上面的X类，很典型
*/

#include "move_semantics.h"

namespace cpp_11 {
namespace move_feature {

void move_demo()
{
    std::string str = "Hello";
    std::vector<std::string> v;
 
    // uses the push_back(const T&) overload, which means 
    // we'll incur the cost of copying str
    v.push_back(str);
    std::cout << "After copy, str is \"" << str << "\"\n";
 
    // uses the rvalue reference push_back(T&&) overload, 
    // which means no strings will be copied; instead, the contents
    // of str will be moved into the vector.  This is less
    // expensive, but also means str might now be empty.
    v.push_back(std::move(str));
    std::cout << "After move, str is \"" << str << "\"\n";
 
    std::cout << "The contents of the vector are \"" << v[0]
                                         << "\", \"" << v[1] << "\"\n";
}

}
}