#include "mutating.h"
#include "helper.h"

#include <cstdlib>

using namespace std;

namespace algorithms {
namespace mutating {

void reverse_order_demo()
{
    /*
     *  void
        reverse (BidirectionalIterator beg, BidirectionalIterator end)

        OutputIterator
        reverse_copy (BidirectionalIterator sourceBeg, BidirectionalIterator sourceEnd,
                      OutputIterator destBeg)

        • reverse() reverses the order of the elements inside the range [beg,end).
        • reverse_copy() reverses the order of the elements while copying them from the source range
          [sourceBeg,sourceEnd) to the destination range starting with destBeg.
        • reverse_copy() returns the position after the last copied element in the destination range (the
          first element that is not overwritten).
        • Lists provide an equivalent member function, reverse(), which offers better performance be-
          cause it relinks pointers instead of assigning element values
     */
    deque<int> coll;
    helper::INSERT_ELEMENTS(coll, 1, 9);
    helper::PRINT_ELEMENT(coll, "coll: ");

    reverse(coll.begin(), coll.end());
    helper::PRINT_ELEMENT(coll, "reverse coll: ");

    reverse(coll.begin() + 1, coll.end() - 1);
    helper::PRINT_ELEMENT(coll, "reverse coll 2: ");

    reverse_copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

void rotate_demo()
{
    /*
     *  ForwardIterator
        rotate (ForwardIterator beg, ForwardIterator newBeg, ForwardIterator end)

        • Rotates elements in the range [beg,end) so that *newBeg is the new first element after the call.
        • Since C++11, returns beg+(end-newbeg), which is the new position of the first element. Before
          C++11, the return type was void.
        • The caller must ensure that newBeg is a valid position in the range [beg,end); otherwise, the call
          results in undefined behavior.
        这个要理解如何填写第二个参数，看下面的例子体会下
        比如要将 1, 2, 3, 4 变为 2, 3, 4, 1, 那么原先的第二个元素就变成了第一个元素，所以第二个参数应该是 begin() + 1
     */
    vector<int> coll;
    helper::INSERT_ELEMENTS(coll, 1, 9);
    helper::PRINT_ELEMENT(coll, "coll: ");

    //shift one element left
    rotate(coll.begin(), coll.begin() + 1, coll.end());
    helper::PRINT_ELEMENT(coll, "rotate first: ");

    //shift 2 elements right
    rotate(coll.begin(), coll.end() - 2, coll.end());
    helper::PRINT_ELEMENT(coll, "rotate second: ");

    /*
     *  OutputIterator
        rotate_copy (ForwardIterator sourceBeg, ForwardIterator newBeg,
                     ForwardIterator sourceEnd,
                     OutputIterator destBeg)
        • Is a combination of copy() and rotate().
        • Copies the elements of the source range [sourceBeg,sourceEnd) into the destination range start-
          ing with destBeg in rotated order so that *newBeg is the new first element.
     */
    set<int> coll2;
    helper::INSERT_ELEMENTS(coll2, 1, 9);
    helper::PRINT_ELEMENT(coll2, "coll2: ");

    rotate_copy(coll2.cbegin(), coll2.find(4), coll2.cend(),
                ostream_iterator<int>(cout, " "));
    cout << endl;
}

void permuting_demo()
{
    /*
     * 这个用得比较少，看看就行
     *  bool
        next_permutation (BidirectionalIterator beg, BidirectionalIterator end)
        bool
        next_permutation (BidirectionalIterator beg, BidirectionalIterator end,
                          BinaryPredicate op)
        bool
        prev_permutation (BidirectionalIterator beg, BidirectionalIterator end)
        bool
        prev_permutation (BidirectionalIterator beg, BidirectionalIterator end,
                          BinaryPredicate op)
        • next_permutation() changes the order of the elements in [beg,end) according to the next permutation.
        • prev_permutation() changes the order of the elements in [beg,end) according to the previous permutation.
        • The first forms compare the elements by using operator <.
        • The second forms compare the elements by using the binary predicate
            op(elem1,elem2)
          which should return true if elem1 is “less than” elem2.
        • Both algorithms return false if the elements got the “normal” (lexicographical) order: that is,
          ascending order for next_permutation() and descending order for prev_permutation().
          So, to run through all permutations, you have to sort all elements (ascending or descending),
          and start a loop that calls next_permutation() or prev_permutation() as long as these
          algorithms return true.
     */
    vector<int> coll;
    helper::INSERT_ELEMENTS(coll, 1, 3);
    helper::PRINT_ELEMENT(coll, "coll: ");

    // permute elements until they are sorted
    // - runs through all permutations because the elements are sorted now
    while (next_permutation(coll.begin(), coll.end())) {
        helper::PRINT_ELEMENT(coll);
    }
    helper::PRINT_ELEMENT(coll, "afterward: ");

    coll = {3, 2, 1};
    helper::PRINT_ELEMENT(coll, "coll now: ");
    // permute elements until they are sorted in descending order
    // - runs through all permutations because the elements are sorted in descending order now
    while (prev_permutation(coll.begin(), coll.end())) {
        helper::PRINT_ELEMENT(coll," ");
    }
    helper::PRINT_ELEMENT(coll,"afterward: ");
}

void shuffling_demo()
{
    /*
     * -- Shuffling Using the Random-Number Library --
        void
        shuffle (RandomAccessIterator beg, RandomAccessIterator end,
                 UniformRandomNumberGenerator&& eng)
        void
        random_shuffle (RandomAccessIterator beg, RandomAccessIterator end)

        void
        random_shuffle (RandomAccessIterator beg, RandomAccessIterator end,
                        RandomFunc&& op)

        • The first form, available since C++11, shuffles the order of the elements in the range [beg,end),
          using an engine eng as introduced by the random numbers and distributions library
        • The second form shuffles the order of the elements in the range [beg,end), using an implemen-
          tation-defined uniform distribution random-number generator, such as the C function rand().
        • The third form shuffles the order of the elements in the range [beg,end), using op. op is called
          with an integral value of difference_type of the iterator:
            op(max)
          which should return a random number greater than or equal to zero and less than max. Thus, it
          should not return max itself.
        • For shuffle(), you should not pass an engine just temporarily created.
     */

    vector<int> coll;
    helper::INSERT_ELEMENTS(coll, 1, 9);
    helper::PRINT_ELEMENT(coll, "coll: ");

    random_shuffle(coll.begin(), coll.end());
    helper::PRINT_ELEMENT(coll, "coll shuffled: ");

    sort(coll.begin(), coll.end());
    helper::PRINT_ELEMENT(coll, "coll sorted: ");

    default_random_engine dre;
    shuffle(coll.begin(), coll.end(), dre);
    helper::PRINT_ELEMENT(coll, "coll shuffled: ");
}

void moving_partition_demo()
{
    /*  Moving Elements to the Front 前面有 is_partitioned() .. 等方法
     *  ForwardIterator
        partition (ForwardIterator beg, ForwardIterator end,
                   UnaryPredicate op)
        BidirectionalIterator
        stable_partition (BidirectionalIterator beg, BidirectionalIterator end,
                          UnaryPredicate op)

        • Both algorithms move all elements in the range [beg,end) to the front, for which the unary predicate
            op(elem)
          yields true.
        • Both algorithms return the first position for which op() yields false.
        • The difference between partition() and stable_partition() is that the algorithm
          stable_partition() preserves the relative order of elements that match the criterion and those that do not.
        • You could use this algorithm to split elements into two parts according to a sorting criterion. The
          nth_element() algorithm has a similar ability.
        • Before C++11, partition() required bidirectional iterators instead of forward iterators and
          guaranteed at most numElems/2 swaps.
        • Use partition_copy() to copy elements into one destination range for fulfilling and
          one for not fulfilling a predicate (available since C++11)
     */
    vector<int> coll1;
    helper::INSERT_ELEMENTS(coll1, 1, 9);
    helper::PRINT_ELEMENT(coll1, "coll1: ");
    vector<int> coll2;
    helper::INSERT_ELEMENTS(coll2, 1, 9);
    helper::PRINT_ELEMENT(coll2, "coll2: ");

    // 将所有偶数移到队列的前面
    auto pos1 = partition(coll1.begin(), coll1.end(), [] (int elem) -> bool { return elem % 2 == 0; });
    helper::PRINT_ELEMENT(coll1, "coll1 partitioned: ");
    if (pos1 != coll1.end())
        cout << "first odd element: " << *pos1 << endl;

    // 保留之前的元素的相对顺序
    auto pos2 = stable_partition(coll2.begin(), coll2.end(), [] (int elem) -> bool {return elem % 2 == 0;});
    helper::PRINT_ELEMENT(coll2, "coll2 stable partitioned: ");
    if (pos2 != coll2.end())
        cout << "first odd element: " << *pos2 << endl;

    /*
     *  pair<OutputIterator1,OutputIterator2>
        partition_copy (InputIterator sourceBeg, InputIterator sourceEnd,
                        OutputIterator1 destTrueBeg, OutputIterator2 destFalseBeg,
                        UnaryPredicate op)
        • Splits all elements in the range [beg,end) according to the predicate op() into two subranges.
        • All elements for which the unary predicate
            op(elem)
          yields true are copied into the range starting with destTrueBeg. All elements for which the
          predicate yields false are copied into the range starting with destFalseBeg.
        • The algorithm returns a pair of the position after the last copied elements of the destination ranges
          (the first element that is not overwritten)
     */
    vector<int> src = { 1, 6, 33, 7, 22, 4, 11, 33, 2, 7, 0, 42, 5 };
    helper::PRINT_ELEMENT(src, "source: ");

    // destination collections:
    vector<int> evenColl;
    vector<int> oddColl;

    partition_copy(src.cbegin(), src.cend(),
                   back_inserter(evenColl),
                   back_inserter(oddColl),
                   [] (int elem) -> bool {
                       return elem % 2 == 0;
                   }); //stable
    helper::PRINT_ELEMENT(evenColl, "evenColl: ");
    helper::PRINT_ELEMENT(oddColl, "oddColl: ");
}

void Run()
{
    /*
     * Mutating algorithms change the order of elements but not their values. Because elements of associa-
       tive and unordered containers have an order defined by the container, you can’t use these algorithms
       as a destination for mutating algorithms.
     */
    reverse_order_demo();
    rotate_demo();
    permuting_demo();
    shuffling_demo();
    moving_partition_demo();
}

}
}