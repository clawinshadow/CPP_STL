#include "auxiliary.h"
#include "helper.h"

#include <iterator>
#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

namespace iterators {
namespace auxiliary {

/*
 * The C++ standard library provides some auxiliary functions for dealing with iterators:
 *     advance(), next(), prev(), distance(), and iter_swap().
 * The first four give all iterators some abilities usually provided only for random-access iterators:
 * to step more than one element forward (or back-ward) and to process the difference between iterators.
 * The last auxiliary function allows you to swap the values of two iterators.
 *
 * 简而言之，前面四个辅助函数就是给所有的 iterators 都赋予了一些本该只有 random-access iterators 才具备的功能
 */


/*
 * void advance (InputIterator& pos, Dist n)
    • Lets the input iterator pos step n elements forward (or backward).
    • For bidirectional and random-access iterators, n may be negative to step backward.
    • Dist is a template type. Normally, it must be an integral type because operations such as <, ++,
    --, and comparisons with 0 are called.
    • Note that advance() does not check whether it crosses the end() of a sequence (it can’t check
    because iterators in general do not know the containers on which they operate). Thus, calling this
    function might result in undefined behavior because calling operator ++ for the end of a sequence
    is not defined.

    For random-access iterators, it simply calls pos+=n.
    Thus, for such iterators, advance() has constant complexity.

    For all other iterators, it calls ++pos n times (or --pos if n is negative).
    Thus, for all other iterator categories, advance() has linear complexity.
 */
void advance_demo()
{
    list<int> coll;

    for (int i = 1; i <= 9; i++) {
        coll.push_back(i);
    }

    list<int>::iterator pos = coll.begin();
    cout << *pos << endl;

    advance(pos, 3); //step 3 elements forward
    cout << *pos << endl;

    advance(pos, -1); // step 1 element backward
    cout << *pos << endl;
}

/*
 * ForwardIterator next(ForwardIterator pos)
   ForwardIterator next(ForwardIterator pos, Dist n)
    • Yields the position the forward iterator pos would have if moved forward 1 or n positions.
    • For bidirectional and random-access iterators, n may be negative to yield previous positions.
    • Dist is type std::iterator_traits<ForwardIterator>::difference_type.
    • Calls advance(pos,n) for an internal temporary object.
    • Note that next() does not check whether it crosses the end() of a sequence. Thus, it is up to
      the caller to ensure that the result is valid.
   prev()也是差不多的
 */

/*
 * Dist distance(InputIterator pos1, InputIterator pos2)
    • Returns the distance between the input iterators pos1 and pos2.
    • Both iterators have to refer to elements of the same container.
    • If the iterators are not random-access iterators, pos2 must be reachable from pos1;
      that is, it must have the same position or a later position.
    • The return type, Dist, is the difference type according to the iterator type:
        iterator_traits<InputIterator>::difference_type
 */
void distance_demo()
{
    list<int> coll;
    for (int i = -3; i <= 9; ++i)
    {
        coll.push_back(i);
    }

    // search element with value 5
    list<int>::iterator pos;
    pos = find(coll.begin(), coll.end(), 5);

    if (pos != coll.end())
    {
        cout << "distance between beginning and 5: " << distance(coll.begin(), pos) << endl;
    } else {
        cout << "5 not found" << endl;
    }
}

/*
 * void iter_swap(ForwardIterator1 pos1, ForwardIterator2 pos2)
    • Swaps the values to which iterators pos1 and pos2 refer.
    • The iterators don’t need to have the same type. However, the values must be assignable.
 */
void iter_swap_demo()
{
    list<int> coll;
    // insert elements from 1 to 9
    for (int i = 1; i <= 9; ++i) {
        coll.push_back(i);
    }
    helper::PRINT_ELEMENT(coll);

    // swap first and second value
    iter_swap(coll.begin(), next(coll.begin()));
    helper::PRINT_ELEMENT(coll);

    // swap first and last value
    iter_swap(coll.begin(), prev(coll.end()));
    helper::PRINT_ELEMENT(coll);
}

void Demo()
{
    advance_demo();
    distance_demo();
    iter_swap_demo();
}

}
}