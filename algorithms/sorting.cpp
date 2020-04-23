#include "sorting.h"
#include "helper.h"

using namespace std;

namespace algorithms {
namespace sorting {

void sorting_all()
{
    /*
     *  void
        sort (RandomAccessIterator beg, RandomAccessIterator end)

        void
        sort (RandomAccessIterator beg, RandomAccessIterator end, BinaryPredicate op)

        void
        stable_sort (RandomAccessIterator beg, RandomAccessIterator end)

        void
        stable_sort (RandomAccessIterator beg, RandomAccessIterator end,
                     BinaryPredicate op)
        • The first forms of sort() and stable_sort() sort all elements in the range [beg,end) with operator <.
        • The second forms of sort() and stable_sort() sort all elements by using the binary predicate
            op(elem1,elem2)
          as the sorting criterion. It should return true if elem1 is “less than” elem2.
        • The difference between sort() and stable_sort() is that stable_sort() guarantees that
          the order of equal elements remains stable.
        • You can’t call these algorithms for lists or forward lists, because both do not provide random-
          access iterators. However, they provide a special member function to sort elements: sort()
        • sort() guarantees a good performance (n-log-n) on average. However, if avoiding worst-case
          performance is important, you should use partial_sort() or stable_sort()
     */
    deque<int> coll;
    helper::INSERT_ELEMENTS(coll, 1, 9);
    helper::INSERT_ELEMENTS(coll, 1, 9);
    helper::PRINT_ELEMENT(coll,"on entry: ");

    // sort elements
    sort (coll.begin(), coll.end());
    helper::PRINT_ELEMENT(coll,"sorted: ");

    // sorted reverse
    sort (coll.begin(), coll.end(),
          greater<int>());
    helper::PRINT_ELEMENT(coll,"sorted >: ");
}

void partial_sorting()
{
    /*
     *  void
        partial_sort (RandomAccessIterator beg, RandomAccessIterator sortEnd,
                      RandomAccessIterator end)
        void
        partial_sort (RandomAccessIterator beg, RandomAccessIterator sortEnd,
                      RandomAccessIterator end, BinaryPredicate op)

        • Unlike sort(), partial_sort() does not sort all elements but stops the sorting once the first
          elements up to sortEnd are sorted correctly. Thus, if, after sorting a sequence, you need only the
          first three elements, this algorithm saves time because it does not sort the remaining elements unnecessarily.
        • If sortEnd is equal to end, partial_sort() sorts the full sequence. It has worse performance
          than sort() on average but better performance in the worst case.
     */
    deque<int> coll;
    helper::INSERT_ELEMENTS(coll, 3, 7);
    helper::INSERT_ELEMENTS(coll, 2, 6);
    helper::INSERT_ELEMENTS(coll, 1, 5);
    helper::PRINT_ELEMENT(coll, "coll: ");

    // sort until the first five elements are sorted
    partial_sort(coll.begin(), coll.begin() + 5, coll.end());
    helper::PRINT_ELEMENT(coll, "coll partial sorted: ");

    // sort all elements
    partial_sort(coll.begin(), coll.end(), coll.end());
    helper::PRINT_ELEMENT(coll, "coll all sorted: ");
}

void nth_element_demo()
{
    /*
     * 其实没太搞明白这个跟partition有什么本质上的区别，只能说partition更准确一点，并且还有stable的版本
     * nth_element() 只负责提取出符合条件的几个元素，不保证stable
     * 另外，partition会返回第一个分水岭的位置，nth_element是void
     *  void
        nth_element (RandomAccessIterator beg, RandomAccessIterator nth,
                     RandomAccessIterator end)
        void
        nth_element (RandomAccessIterator beg, RandomAccessIterator nth,
                     RandomAccessIterator end, BinaryPredicate op)
        • Both forms sort the elements in the range [beg,end), so the correct element is at the nth position,
          and all elements in front are less than or equal to this element, and all elements that follow are
          greater than or equal to it. Thus, you get two subsequences separated by the element at position
          n, whereby each element of the first subsequence is less than or equal to each element of the
          second subsequence. This is helpful if you need only the set of the n highest or lowest elements
          without having all the elements sorted.
     */
    deque<int> coll;
    helper::INSERT_ELEMENTS(coll, 3, 7);
    helper::INSERT_ELEMENTS(coll, 2, 6);
    helper::INSERT_ELEMENTS(coll, 1, 5);
    helper::PRINT_ELEMENT(coll, "coll: ");

    // extract the four lowest elements
    nth_element(coll.begin(), coll.begin() + 3, coll.end());
    copy(coll.cbegin(), coll.cbegin() + 4,
         ostream_iterator<int>(cout, " "));
    cout << endl;

}

void heap_demo()
{
    /*
     *  In the context of sorting, a heap is used as a particular way to sort elements. It is used by heapsort.
        A heap can be considered a binary tree that is implemented as a sequential collection. Heaps have
        two properties:
        1. The first element is always (one of) the largest.
        2. You can add or remove an element in logarithmic time.

        A heap is the ideal way to implement a priority queue: a queue that sorts its elements automatically
        so that the “next” element always is (one of) the largest. Therefore, the heap algorithms are used by
        the priority_queue container (see Section 12.3, page 641). The STL provides four algorithms to
        handle a heap:
        1. make_heap() converts a range of elements into a heap.
        2. push_heap() adds one element to the heap.
        3. pop_heap() removes the next element from the heap.
        4. sort_heap() converts the heap into a sorted collection, after which it is no longer a heap.

        In addition, since C++11, is_heap() and is_heap_until() are provided to check whether a
        collection is a heap or to return the first element that breaks the property of a collection to be a heap

        As usual, you can pass a binary predicate as the sorting criterion. The default sorting criterion is
        operator <.

        void
        make_heap (RandomAccessIterator beg, RandomAccessIterator end)
        void
        make_heap (RandomAccessIterator beg, RandomAccessIterator end,
                   BinaryPredicate op)
        • Both forms convert the elements in the range [beg,end) into a heap.

        void
        push_heap (RandomAccessIterator beg, RandomAccessIterator end)
        void
        push_heap (RandomAccessIterator beg, RandomAccessIterator end,
                   BinaryPredicate op)
        • Both forms add the last element that is in front of end to the existing heap in the range [beg,end-1)
          so that the whole range [beg,end) becomes a heap

        void
        pop_heap (RandomAccessIterator beg, RandomAccessIterator end)
        void
        pop_heap (RandomAccessIterator beg, RandomAccessIterator end,
                  BinaryPredicate op)
        • Both forms move the highest element of the heap [beg,end), which is the first element, to the last
          position and create a new heap from the remaining elements in the range [beg,end-1)

        void
        sort_heap (RandomAccessIterator beg, RandomAccessIterator end)
        void
        sort_heap (RandomAccessIterator beg, RandomAccessIterator end,
                   BinaryPredicate op)
        • Both forms convert the heap [beg,end) into a sorted sequence.
     */
    vector<int> coll;
    helper::INSERT_ELEMENTS(coll, 3, 7);
    helper::INSERT_ELEMENTS(coll, 5, 9);
    helper::INSERT_ELEMENTS(coll, 1, 4);
    helper::PRINT_ELEMENT(coll, "on entry: ");

    // convert collection into a heap
    make_heap (coll.begin(), coll.end());
    helper::PRINT_ELEMENT(coll, "after make_heap(): ");

    // pop next element out of the heap
    pop_heap (coll.begin(), coll.end());
    coll.pop_back();
    helper::PRINT_ELEMENT(coll, "after pop_heap(): ");

    // push new element into the heap
    coll.push_back (17);
    push_heap (coll.begin(), coll.end());
    helper::PRINT_ELEMENT(coll, "after push_heap(): ");

    /*
     *  After make_heap(), the elements are sorted as a heap:
        9 8 6 7 7 5 5 3 6 4 1 2 3 4
        Transform the elements into a binary tree, and you’ll see that the value of each node is less than or
        equal to its parent node. Both push_heap() and pop_heap() change the elements
        so that the invariant of this binary tree structure — each node not greater than its parent node —
        remains stable.
                         9
                    8         6
                 7     7   5     5
               3   6  4 1 2 3     4
        从这个队列里面看，就是按照 1 - 2 - 4 - 8 这样截取元素，一层一层的叠成一棵树，比如：
        顶层就一个节点是9
        第二层两个子节点 8, 6
        第三层4个子节点 7 7 5 5, 分别隶属于 8 和 6
        ....等等等等
     */
}

void Run()
{
    /*
     *  The STL provides several algorithms to sort elements of a range. In addition to full sorting, the STL
        provides variants of partial sorting. If their result is enough, you should prefer them because they
        usually have better performance.
        Because (forward) lists and associative and unordered containers provide no random-access ite-
        rators, you can’t use these containers (as a destination) for sorting algorithms. Instead, you might
        use associative containers to have elements sorted automatically. Note, however, that sorting all
        elements once is usually faster than keeping them always sorted
     */
    sorting_all();
    partial_sorting();
    nth_element_demo();
    heap_demo();
}

}
}