/* An iterator is an object that can iterate over elements (navigate from element to element).
 * These elements may be all or a subset of the elements of an STL container.
 * An iterator represents a certain position in a container.
 * The following fundamental operations define the behavior of an iterator:
    • Operator * returns the element of the current position.
      If the elements have members, you can use operator -> to access those members directly from the iterator.
    • Operator ++ lets the iterator step forward to the next element.
      Most iterators also allow stepping backward by using operator --.
    • Operators == and != return whether two iterators represent the same position.
    • Operator = assigns an iterator (the position of the element to which it refers).
*/

#include "iterators.h"
#include "helper.h"

#include <set>
#include <list>
#include <deque>
#include <forward_list>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;
using namespace helper;

namespace stl_basics {
namespace iterators {

void Demo() {
    list<char> coll;
    for (char c = 'a'; c <= 'z'; ++c) {
        coll.push_back(c);
    }

    /*
     *  every container defines two iterator types:
        1. container::iterator is provided to iterate over elements in read/write mode.
        2. container::const_iterator is provided to iterate over elements in read-only mode.
     */
    list<char>::const_iterator pos;

    /*
     * ++pos VS. pos++
     * The latter internally involves a temporary object because it must return the old position of the iterator
     * 一般情况下我们都是用++pos来递增iterator，性能会更好一些
     */
    for (pos = coll.begin(); pos != coll.end(); ++pos)
        std::cout << *pos << " ";

    std::cout << std::endl;

    /*
     * Iterator Categories: 根据容器类型的不同，它们使用的迭代器也可以分为几类
     * 1. Forward iterators： they are able to iterate only forward, using the increment operator.
     *    The iterators of the class forward_list are forward iterators
     * 2. Bidirectional iterators: are able to iterate in two directions: forward, ++, and backward, --.
     *    The iterators of the container classes list, set, multiset, map, and multimap are bidirectional iterators.
     * 3. Random-access iterators: have all the properties of bidirectional iterators. 并且还支持iterator的各种算术运算，
     *    加减，offset，比较两个iterator的不同等等。 vector, deque, array, string 都是这类
     */
    std::forward_list<int> flist = {3, 2, 4, 5};
    // 正向遍历迭代器可以
    for (auto iter = flist.cbegin(); iter != flist.cend(); ++iter)
        cout << *iter << " ";
    cout << endl;
    // 反向迭代不行，Compile Error
//    for (auto iter = flist.cend(); iter != flist.cbegin(); --iter)
//        cout << *iter << " ";

    std::list<float> floats = {1.1, 2.2, 3.3, 4.5};
    // 反向迭代 OK
    auto iter = floats.cend();
    do
    {
        --iter;
        cout << *iter << endl;
    } while (iter != floats.cbegin());

    // 支持迭代器的算术运算
    std::vector<int> vec {1, 2, 3, 4, 5};
    auto it = vec.cbegin();
    cout << *(it + 2) << endl; //output 3

}

/*
 *  Iterators are pure abstractions: Anything that behaves like an iterator is an iterator. For this reason,
    you can write classes that have the interface of iterators but do something completely different.
    The C++ standard library provides several predefined special iterators: iterator adapters.
    They are more than auxiliary classes;
    The following subsections introduce the following iterator adapters:
    1. Insert iterators
    2. Stream iterators
    3. Reverse iterators
    4. Move iterators (since C++11)
 */

void StreamIteratorDemo()
{
    /*
     *  Stream iterators read from or write to a stream. Thus, they provide an abstraction that lets the input
        from the keyboard behave as a collection from which you can read.
        Similarly, you can redirect the output of an algorithm directly into a file or onto the screen.
     */
    vector<string> inputs;

    // read all words from the standard input
    // - source: all strings until end-of-file (or error)
    // - destination: coll (inserting)
    // istream_iterator 接受的参数必须重载操作符 operator >>, 就像cin
    copy(istream_iterator<string>(cin),
         istream_iterator<string>(),
         back_inserter(inputs));

    // sort elements
    sort(inputs.begin(), inputs.end());

    // print all elements without duplicates
    // - source: coll
    // - destination: standard output (with newline between elements)
    // ostream_iterator 接受的参数必须重载操作符 <<, like cout
    // The second argument behind cout is optional and serves as a separator between the elements
    unique_copy(inputs.cbegin(), inputs.cend(), // source
                ostream_iterator<string>(cout,"\n")); // destination
}

void IteratorAdaptersDemo()
{
    /*
     * Insert iterators: 也被称为inserters，STL中有以下三类
     * 1. Back inserters： insert the elements at the back of their container (appends them) by calling push_back()
     *        Of course, back inserters can be used only for containers that provide push_back() as a member function
     * 2. Front inserters： insert the elements at the front of their container by calling push_front()
     * 3. General inserters, or simply inserters, insert elements directly in front of the position that is
              passed as the second argument of its initialization
              A general inserter calls the insert() member function with the new value and the new position as arguments.
            所以这个方法是需要两个参数的，第二个参数指定插入的初始位置, 这是唯一可用于associative containers的inserter
     */
    list<int> coll1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    vector<int> coll2;
    copy(coll1.cbegin(), coll1.cend(), back_inserter(coll2));

    deque<int> coll3;
    copy (coll1.cbegin(), coll1.cend(), // source
          front_inserter(coll3));    // destination
    PRINT_ELEMENT(coll3);

    set<int> coll4;
    copy (coll1.cbegin(), coll1.cend(),      // source
          inserter(coll4,coll4.begin())); // destination

    //StreamIteratorDemo(); //不好调试，注释掉先

    /*
     * Reverse Iterators
     *   All containers with bidirectional iterators or random-access iterators (all sequence containers except forward_list
     *   and all associative containers) can create reverse iterators via their member functions rbegin() and rend().
     */
    vector<int> ints;
    for (int i = 1; i <= 9; ++i) {
        ints.push_back(i);
    }
    // print all element in reverse order
    copy (ints.crbegin(), ints.crend(),
          ostream_iterator<int>(cout, " "));
    cout << endl;

    /*
     * Move Iterators
     * They convert any access to the underlying element into a move operation.
     * As a result, they allow moving elements from one container into another
     * either in constructors or while applying algorithms
     */
}

}
}