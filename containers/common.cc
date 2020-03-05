/*
 所有的STL容器都有以下三种alibities：
 1. All containers provide value than reference semantics. 
    Containers copy and/or move ele- ments internally when they are inserted rather than managing references to them. 
    Thus, ideally, each element of an STL container must be able to be copied and moved.
 2. The elements inside a container have a specific order. 
    即每个容器内部的顺序是固定不变的，即便对于 unordered containers 来说也是一样
    确保每次使用iterator遍历的时候，它的顺序都是一样的
    当然前提条件是我们不改变里面的元素
 3. In general, operations are not “safe” in the sense that they check for every possible error.
    STL 容器不负责检查每一种错误，即健壮性不好


 */
#include "common.h"
#include "helper.h"

#include <set>
#include <vector>
#include <unordered_set>
#include <list>
#include <deque>
#include <iterator>

using namespace std;
using namespace helper;

namespace containers {
namespace common {

void Run()
{
    Initialization();
}

void Initialization()
{
    // Initialize container 的 5 种方式：
    // Every container class provides a default constructor, a copy constructor, and a destructor. 
    // You can also initialize a container with elements of a given range and, since C++11, with an initializer list.
    /*
        1. Default Constructor: ContType c
        2. Copy constructor: ContType c(c2)， ContType c = c2
        3. Move constructor: ContType c(rv), ContType c = rv。Move拥有最好的性能，只是交换指针，常数复杂度
        4. Range: ContType c(beg,end), with copies
        5. Initializer list: ContType c(initlist), with copies
     */

    // -- with initializer list --
    // initialize a vector with some specific values (since C++11)
    const std::vector<int> v1 = { 1, 2, 3, 5, 7, 11, 13, 17, 21 };
    copy(v1.cbegin(), v1.cend(), 
         ostream_iterator<int>(cout, " "));
    cout << endl;
    // same with different syntax
    const std::vector<int> v2 { 1, 2, 3, 5, 7, 11, 13, 17, 21 };
    PRINT_ELEMENT(v2, "v2: ");
    // initialize an unordered set with ‘‘hello’’ and two empty strings 
    std::unordered_set<std::string> w = { "hello", std::string(), "" };

    // -- with range --
    std::list<int> l; // l is a linked list of ints
    l.push_back(1);
    l.push_front(0);
    
    std::vector<float> v3(l.begin(),l.end());
    PRINT_ELEMENT(v3, "v3: ");

    // -- with move semantics --
    std::list<string> s {"Hello", "world"};
    std::vector<string> v4 (std::make_move_iterator(s.begin()),
                            std::make_move_iterator(s.end()));
    PRINT_ELEMENT(v4, "v4: ");
    PRINT_ELEMENT(s, "s been moved: "); //被 move 之后的容器元素变为undefined

    // -- with an ordinary C-Style array
    int carray[] = { 2, 3, 17, 33, 45, 77 };

    // copy all elements of the C-style array into a set
    std::set<int> s1(std::begin(carray),std::end(carray));
    PRINT_ELEMENT(s1, "s1 with C array: ");

}

}
}