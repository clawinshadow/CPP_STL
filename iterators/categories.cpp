#include "categories.h"

#include <iterator>
#include <vector>
#include <iostream>

using namespace std;

namespace iterators {
namespace categories {

/*绝大部分iterator都是基于原始指针封装的，主要分为以下几大类：
    Output iterator          Writes forward               Ostream, inserter
    Input iterator           Reads forward once           Istream
    Forward iterator         Reads forward                Forward list, unordered containers
    Bidirectional iterator   Reads forward and backward   List, set, multiset, map, multimap
    Random-access iterator   Reads with random access     Array, vector, deque, string, C-style array

 1. Output iterator: Output iterators can only step forward with write access，只支持以下几个操作
        Expression          Effect
        *iter = val         Writes val to where the iterator refers
        ++iter              Steps forward (returns new position)
        iter++              Steps forward (returns old position)
        TYPE(iter)          Copies iterator (copy constructor)
    典型的比如 standard output 和 inserters
 2. Input iterator: Input iterators can only step forward element-by-element with read access
        Expression          Effect
        *iter               Provides read access to the actual element
        iter->member        Provides read access to a member of the actual element
        ++iter              Steps forward (returns new position)
        iter++              Steps forward (returns old position)
        iter1 == iter2      Returns whether two iterators are equal
        iter1 != iter2      Returns whether two iterators are not equal
        TYPE(iter)          Copies iterator (copy constructor)
     For input iterators, operators == and != are provided only to check whether an iterator is equal to
     a past-the-end iterator
     You should always prefer the preincrement operator over the postincrement operator because it
     might perform better. This is because the preincrement operator does not have to return an old value
     that must be stored in a temporary object. So, for any iterator pos (and any abstract data type), you
     should prefer
        ++pos   // OK and fast
     rather than
        pos++   // OK, but not so fast

 3. Forward iterator: Forward iterators are input iterators that provide additional guarantees while reading forward.
        Expression          Effect
        *iter               Provides read access to the actual element
        iter->member        Provides read access to a member of the actual element
        ++iter              Steps forward (returns new position)
        iter++              Steps forward (returns old position)
        iter1 == iter2      Returns whether two iterators are equal
        iter1 != iter2      Returns whether two iterators are not equal
        TYPE(iter)          Copies iterator (copy constructor)
        iter1 = iter2       Assigns an iterator
    看上去这些功能似乎跟input interator没什么区别，但是：
      Unlike for input iterators, it is guaranteed that for two forward iterators that refer to the same element,
      operator == yields true and that they will refer to the same value after both are incremented
    主要是 forward_list 这个单向链表和 unordered containers 用这个迭代器

 4. Bidirectional iterator: forward iterators + the additional ability to iterate backward over the elements
    所以除了上面 Forward Iterator 的功能之外，还提供回溯元素的功能
        Expression          Effect
        --iter              Steps backward (returns new position)
        iter--              Steps backward (returns old position)
    主要是双向链表 list 和 associative containers 用这个

 5. Random-Access iterator: 功能最齐全的iterator, provide all the abilities of bidirectional iterators plus random access
    主要是新增了迭代器的算术运算 和 随机访问操作符：[]
        Expression          Effect
        iter[n]             Provides access to the element that has index n
        iter+=n             Steps n elements forward (or backward, if n is negative)
        iter-=n             Steps n elements backward (or forward, if n is negative)
        iter+n              Returns the iterator of the nth next element
        n+iter              Returns the iterator of the nth next element
        iter-n              Returns the iterator of the nth previous element
        iter1-iter2         Returns the distance between iter1 and iter2
        iter1<iter2         Returns whether iter1 is before iter2
        iter1>iter2         Returns whether iter1 is after iter2
        iter1<=iter2        Returns whether iter1 is not after iter2
        iter1>=iter2        Returns whether iter1 is not before iter2
    Random-access iterators are provided by the following objects and types:
    • Containers with random access (array, vector, deque)
    • Strings (string, wstring)
    • Ordinary C-style arrays (pointers)

  再就是某些情况下，需要慎用iterators的++或者--运算符，特别是对于arrays, vectors and strings 来说，这个操作在某些平台上可能无法编译
  因此是Non-portable的
    std::vector<int> coll;
    ...
    // sort, starting with the second element
    // - NONPORTABLE version
    if (coll.size() > 1) {
        std::sort(++coll.begin(), coll.end());
    }

  C++11后，应该使用 std::next() 可以保证它们是 portable 的
        std::vector<int> coll;
        ...
        // sort, starting with the second element
        // - PORTABLE version since C++11
        if (coll.size() > 1) {
            std::sort(std::next(coll.begin()), coll.end());
        }
*/
void Demo()
{
    // 主要是针对 random-access iterator 的demo
    vector<int> coll;
    // insert elements from -3 to 9
    for (int i = -3; i <= 9; ++i) {
        coll.push_back(i);
    }

    // print number of elements by processing the distance between beginning and end
    // - NOTE: uses operator - for iterators
    cout << "number/distance: " << coll.end()-coll.begin() << endl;
    // print all elements
    // - NOTE: uses operator < instead of operator !=
    vector<int>::iterator pos;
    for (pos = coll.begin(); pos < coll.end(); ++pos) {
        cout << *pos << " ";
    }

    cout << endl;
    // print all elements
    // - NOTE: uses operator [ ] instead of operator *
    for (int i = 0; i < coll.size(); ++i) {
        cout << coll.begin()[i] << " ";  // [] 操作符
    }
    cout << endl;

    // print every second element
    // - NOTE: uses operator +=
    for (pos = coll.begin(); pos < coll.end() - 1; pos += 2) {
        cout << *pos << " ";
    }
    cout << endl;
}

}
}