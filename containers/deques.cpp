#include "deques.h"
#include "helper.h"

#include <iterator>
#include <iostream>
#include <deque>
#include <string>

using namespace std;
using namespace helper;

namespace containers {
namespace deques {

/*
 * deque基本上是和vector一样的，只不过它是双向队列
 *      The difference is that with a deque, the dynamic array is open at both ends.
 *      Thus, a deque is fast for insertions and deletions at both the end and the beginning
 * 特性：
 * 1. Inserting and removing elements is fast at both the beginning and the end, O(1)
 * 2. The internal structure has one more indirection to access the elements,
 *    so with deques, element access and iterator movement are usually a bit slower.
 * 3. Deques provide no support to control the capacity and the moment of reallocation.
 *    In particular, any insertion or deletion of elements other than at the beginning or end
 *    invalidates all pointers, references, and iterators that refer to elements of the deque
 * 4. 没有提供Reallocation的接口不代表reallocation不会发生，deque的reallocation性能比vector要好一点
 * 5. Blocks of memory might get freed when they are no longer used,
 *    so the memory size of a deque might shrink
 */
void Run()
{
    deque<string> coll;

    // insert several elements
    coll.assign (3, string("string"));
    coll.push_back ("last string");
    coll.push_front ("first string");

    copy(coll.begin(), coll.end(), ostream_iterator<string>(cout, " "));
    cout << endl;

    // remove first and last element
    coll.pop_front();
    coll.pop_back();

    // insert ‘‘another’’ into every element but the first
    for (unsigned i = 1; i < coll.size(); ++i) {
        coll[i] = "another " + coll[i];
    }
    // change size to four elements
    // resize(num, elem): Changes the number of elements to num (if size() grows
    //                    new elements are copies of elem)
    coll.resize (4, "resized string");

    copy (coll.cbegin(), coll.cend(),ostream_iterator<string>(cout,"\n"));
}

}
}
