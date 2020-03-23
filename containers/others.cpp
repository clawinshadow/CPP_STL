#include "others.h"

#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;

namespace containers {
namespace others {

/*
 * 一般而言我们有三种方式来实现STL-like的容器，这样我们就可以方便的使用STL中的算法库：
 * 1. Invasive approach: You simply provide the interface that an STL container requires. In
            particular, you need the usual member functions of containers, such as begin() and end().
            This approach is invasive because it requires that a container be written in a certain way.
   2. Noninvasive approach: You write or provide special iterators that are used as an interface
            between the algorithms and special containers.
            This approach is noninvasive.
            All it requires is the ability to step through all the elements of a container,
            an ability that any container provides
   3. Wrapper approach: Combining the two previous approaches, you write a wrapper class
            that encapsulates any data structure with an STL container-like interface. in some way.
 */

void StringsDemo()
{
  // Invasive approach 的典型实现
  //details in Chapter 13
}

void C_Arrays_Demo()
{
    //Noninvasive approach 的典型实现
    //C数组并不是一个类，所以无法提供类似于begin()或者end()的成员函数，我们只需要赋予它们能按照STL iterator interface
    //遍历自己就可以了
    int vals[] = { 33, 67, -4, 13, 5, 2 };

    //能使用 std::begin() 和 std::end() 就行
    std::copy(std::begin(vals), std::end(vals),
              std::ostream_iterator<int>(std::cout, " "));

    std::cout << std::endl;

    // Before C++11, we use raw pointers to the algorithms
    int coll[] = { 5, 6, 2, 4, 1, 3 };

    // square all elements
    transform(coll, coll+6,       // first source
              coll,               // second source
              coll,               // destination
              multiplies<int>());

    // sort beginning with the second element
    sort (coll+1, coll+6);
    // print all elements
    copy (coll, coll+6,
          ostream_iterator<int>(cout," "));
    cout << endl;
}

}
}