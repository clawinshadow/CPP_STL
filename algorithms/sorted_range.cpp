#include "sorted_range.h"
#include "helper.h"

using namespace std;

namespace algorithms {
namespace sorted_range {

void binary_search_demo()
{
    /*
     *  bool
        binary_search (ForwardIterator beg, ForwardIterator end, const T& value)

        bool
        binary_search (ForwardIterator beg, ForwardIterator end, const T& value,
                       BinaryPredicate op)
        • Both forms return whether the sorted range [beg,end) contains an element equal to value.
        • op is an optional binary predicate to be used as the sorting criterion:
            op(elem1,elem2)
        • To obtain the position of an element for which you are searching, use lower_bound(),
          upper_bound(), or equal_range()
        • Complexity: logarithmic for random-access iterators, linear otherwise
     */
    list<int> coll;
    helper::INSERT_ELEMENTS(coll, 1, 9);
    helper::PRINT_ELEMENT(coll, "coll: ");

    if (binary_search(coll.begin(), coll.end(), 5)) {
        cout << "5 is present in coll" << endl;
    }
    else
        cout << "5 is not present in coll" << endl;

    if (binary_search(coll.begin(), coll.end(), 42)) {
        cout << "42 is present in coll" << endl;
    }
    else
        cout << "42 is not present in coll" << endl;
}

void includes_demo()
{
    /*
     *  bool
        includes (InputIterator1 beg, InputIterator1 end,
                  InputIterator2 searchBeg, InputIterator2 searchEnd)
        bool
        includes (InputIterator1 beg, InputIterator1 end,
                  InputIterator2 searchB

        • Both forms return whether the sorted range [beg,end) contains all elements in the sorted range
          [searchBeg,searchEnd). That is, for each element in [searchBeg,searchEnd), there must be an
          equal element in [beg,end). If elements in [searchBeg,searchEnd) are equal, [beg,end) must con-
          tain the same number of elements. Thus, [searchBeg,searchEnd) must be a subset of [beg,end).
          search里面元素也要是排好序了的
        • Complexity: linear
     */
    list<int> coll;
    helper::INSERT_ELEMENTS(coll, 1, 9);
    helper::PRINT_ELEMENT(coll, "coll: ");

    vector<int> search ={3, 4, 7};
    if (includes(coll.cbegin(), coll.cend(),
                 search.cbegin(), search.cend())) {
        cout << "search range found in coll" << endl;
    } else
        cout << "not found" << endl;
}

void search_pos_returned_demo()
{
    /*
     *  这个原理上跟binary_search应该是一样的，只不过它会返回找到的元素的位置
     *  ForwardIterator
        lower_bound (ForwardIterator beg, ForwardIterator end, const T& value)

        ForwardIterator
        lower_bound (ForwardIterator beg, ForwardIterator end, const T& value,
                     BinaryPredicate op)

        ForwardIterator
        upper_bound (ForwardIterator beg, ForwardIterator end, const T& value)

        ForwardIterator
        upper_bound (ForwardIterator beg, ForwardIterator end, const T& value,
                     BinaryPredicate op)

        • lower_bound() returns the position of the first element that has a value equal to or greater than
          value. This is the first position where an element with value value could get inserted without
          breaking the sorting of the range [beg,end).
        • upper_bound() returns the position of the first element that has a value greater than value. This
          is the last position where an element with value value could get inserted without breaking the
          sorting of the range [beg,end).
        • All algorithms return end if there is no such value.
        • Complexity: logarithmic for random-access iterators, linear otherwise
     */
    list<int> coll;
    helper::INSERT_ELEMENTS(coll, 1, 9);
    helper::INSERT_ELEMENTS(coll, 1, 9);
    coll.sort();
    helper::PRINT_ELEMENT(coll, "coll: ");

    // print first and last position 5 could get inserted
    // lower_bound 返回的是第一个5的位置，但是upper_bound返回的却是最后一个5后面一格的位置，这个要注意哦
    auto pos1 = lower_bound (coll.cbegin(), coll.cend(), 5);
    auto pos2 = upper_bound (coll.cbegin(), coll.cend(), 5);
    cout << "5 could get position "
         << distance(coll.cbegin(), pos1) + 1
         << " up to "
         << distance(coll.cbegin(), pos2) + 1
         << " without breaking the sorting" << endl;

    // insert 3 at the first possible position without breaking the sorting
    coll.insert(lower_bound(coll.cbegin(), coll.cend(), 3), 3);
    // insert 7 at the last possible position without breaking the sorting
    coll.insert(upper_bound(coll.cbegin(), coll.cend(), 7), 7);

    helper::PRINT_ELEMENT(coll, "coll inserted: ");
    // 感觉这两个函数就是为了insert而服务的
}

void equal_range_demo()
{
    /*
     *  pair<ForwardIterator,ForwardIterator>
        equal_range (ForwardIterator beg, ForwardIterator end, const T& value)

        pair<ForwardIterator,ForwardIterator>
        equal_range (ForwardIterator beg, ForwardIterator end, const T& value,
                     BinaryPredicate op)

        • Both forms return the range of elements that is equal to value. The range comprises the first and
          the last position an element with value value could get inserted without breaking the sorting of
          the range [beg,end).
        • This is equivalent to:
            make_pair(lower_bound(...),upper_bound(...))
     */
    list<int> coll;
    helper::INSERT_ELEMENTS(coll, 1, 9);
    helper::INSERT_ELEMENTS(coll, 1, 9);
    coll.sort ();
    helper::PRINT_ELEMENT(coll);

    // print first and last position 5 could get inserted
    pair<list<int>::const_iterator, list<int>::const_iterator> range;
    range = equal_range(coll.cbegin(), coll.cend(), 5);

    cout << "5 could get position "
         << distance(coll.cbegin(), range.first) + 1
         << " up to "
         << distance(coll.cbegin(), range.second) + 1
         << " without breaking the sorting" << endl;
}

void searching_elements_demos()
{
    binary_search_demo();
    includes_demo();
    search_pos_returned_demo();
    equal_range_demo();
}

void merge_demo()
{
    /*
     *  OutputIterator
        merge (InputIterator source1Beg, InputIterator source1End,
               InputIterator source2Beg, InputIterator source2End,
               OutputIterator destBeg)
        OutputIterator
        merge (InputIterator source1Beg, InputIterator source1End,
               InputIterator source2Beg, InputIterator source2End,
               OutputIterator destBeg, BinaryPredicate op)

        • Both forms merge the elements of the sorted source ranges [source1Beg,source1End) and
          [source2Beg,source2End) so that the destination range starting with destBeg contains all ele-
          ments that are in the first source range plus those that are in the second source range. For example,
          calling merge() for
            1 2 2 4 6 7 7 9
          and
            2 2 2 3 6 6 8 9
          results in
            1 2 2 2 2 2 3 4 6 6 6 7 7 8 9 9
        • All elements in the destination range are in sorted order.
        • The source ranges are not modified.
        • The destination range should not overlap the source ranges.
        • Lists and forward lists provide a special member function, merge(), to merge the elements of
          two lists.
        • To ensure that elements that are in both source ranges end up in the destination range only once,
          use set_union().
        • To process only the elements that are in both source ranges, use set_intersection()
     */
    list<int> coll1;
    set<int> coll2;
    helper::INSERT_ELEMENTS(coll1, 1, 4);
    helper::INSERT_ELEMENTS(coll2, 2, 5);
    helper::PRINT_ELEMENT(coll1, "coll1: ");
    helper::PRINT_ELEMENT(coll2, "coll2: ");

    cout << "merged: ";
    merge(coll1.cbegin(), coll1.cend(),
          coll2.cbegin(), coll2.cend(),
          ostream_iterator<int>(cout, " "));
    cout << endl;
}

void union_demo()
{
    /*
     *  OutputIterator
        set_union (InputIterator source1Beg, InputIterator source1End,
                   InputIterator source2Beg, InputIterator source2End,
                   OutputIterator destBeg)
        OutputIterator
        set_union (InputIterator source1Beg, InputIterator source1End,
                   InputIterator source2Beg, InputIterator source2End,
                   OutputIterator destBeg, BinaryPredicate op)

        • Both forms merge the elements of the sorted source ranges [source1Beg,source1End) and
          [source2Beg,source2End) so that the destination range starting with destBeg contains all ele-
          ments that are in the first source range, in the second source range, or in both. For example,
          calling set_union() for
            1 2 2 4 6 7 7 9
          and
            2 2 2 3 6 6 8 9
          results in
            1 2 2 2 3 4 6 6 7 7 8 9
          这个要怎么理解呢，就是一个一个的比对两个队列中相同位置的元素，如果相同，则只保留一个，如果不同，则两个都留下，
          然后再串成一个大的队列，比如上面的例子中：
          (1, 2) -> 2 -> 2 -> (4, 3) -> 6 -> (7, 6) -> (7, 8) -> 9
          最后排一下序即可

        • All elements in the destination range are in sorted order.
        • Elements that are in both ranges are in the union range only once. However, duplicates are pos-
          sible if elements occur more than once in one of the source ranges. The number of occurrences
          of equal elements in the destination range is the maximum of the number of their occurrences in
          both source ranges.
     */
    vector<int> c1 = { 1, 2, 2, 4, 6, 7, 7, 9 };
    deque<int>  c2 = { 2, 2, 2, 3, 6, 6, 8, 9 };
    helper::PRINT_ELEMENT(c1, "c1: ");
    helper::PRINT_ELEMENT(c2, "c2: ");

    cout << "c1 union c2: ";
    set_union(c1.cbegin(), c1.cend(),
              c2.cbegin(), c2.cend(),
              ostream_iterator<int>(cout, " "));
    cout << endl;
}

void intersection_demo()
{
    /*
     *  OutputIterator
        set_intersection (InputIterator source1Beg, InputIterator source1End,
                          InputIterator source2Beg, InputIterator source2End,
                          OutputIterator destBeg)
        OutputIterator
        set_intersection (InputIterator source1Beg, InputIterator source1End,
                          InputIterator source2Beg, InputIterator source2End,
                          OutputIterator destBeg, BinaryPredicate op)
        • Both forms merge the elements of the sorted source ranges [source1Beg,source1End) and
          [source2Beg,source2End) so that the destination range starting with destBeg contains all ele-
          ments that are in both source ranges. For example, calling set_intersection() for
            1 2 2 4 6 7 7 9
          and
            2 2 2 3 6 6 8 9
          results in
            2 2 6 9
        • All elements in the destination range are in sorted order.
     */
    vector<int> c1 = { 1, 2, 2, 4, 6, 7, 7, 9 };
    deque<int>  c2 = { 2, 2, 2, 3, 6, 6, 8, 9 };
    helper::PRINT_ELEMENT(c1, "c1: ");
    helper::PRINT_ELEMENT(c2, "c2: ");

    cout << "c1 intersect with c2: ";
    set_intersection(c1.cbegin(), c1.cend(),
                     c2.cbegin(), c2.cend(),
               ostream_iterator<int>(cout, " "));
    cout << endl;
}

void difference_demo()
{
    /*
     *  OutputIterator
        set_difference (InputIterator source1Beg, InputIterator source1End,
                        InputIterator source2Beg, InputIterator source2End,
                        OutputIterator destBeg)
        OutputIterator
        set_difference (InputIterator source1Beg, InputIterator source1End,
                        InputIterator source2Beg, InputIterator source2End,
                        OutputIterator destBeg, BinaryPredicate op)
        • Both forms merge the elements of the sorted source ranges [source1Beg,source1End) and
          [source2Beg,source2End) so that the destination range starting with destBeg contains all ele-
          ments that are in the first source range but not in the second source range. For example, calling
          set_difference() for
            1 2 2 4 6 7 7 9
          and
            2 2 2 3 6 6 8 9
          results in
            1 4 7 7
          就是说第一个队列里面有，而第二个队列里面没有的
     */
    vector<int> c1 = { 1, 2, 2, 4, 6, 7, 7, 9 };
    deque<int>  c2 = { 2, 2, 2, 3, 6, 6, 8, 9 };
    helper::PRINT_ELEMENT(c1, "c1: ");
    helper::PRINT_ELEMENT(c2, "c2: ");

    cout << "c1 different with c2: ";
    set_difference(c1.cbegin(), c1.cend(),
                   c2.cbegin(), c2.cend(),
                   ostream_iterator<int>(cout, " "));
    cout << endl;
}

void symmetric_difference_demo()
{
    /*
     *  OutputIterator
        set_symmetric_difference (InputIterator source1Beg, InputIterator source1End,
                                  InputIterator source2Beg, InputIterator source2End,
                                  OutputIterator destBeg)
        OutputIterator
        set_symmetric_difference (InputIterator source1Beg, InputIterator source1End,
                                  InputIterator source2Beg, InputIterator source2End,
                                  OutputIterator destBeg, BinaryPredicate op)
        • Both forms merge the elements of the sorted source ranges [source1Beg,source1End) and
          [source2Beg,source2End) so that the destination range starting with destBeg contains all ele-
          ments that are either in the first source range or in the second source range but not in both. For
          example, calling set_symmetric_difference() for
            1 2 2 4 6 7 7 9
          and
            2 2 2 3 6 6 8 9
          results in
            1 2 3 4 6 7 7 8
          就是将两个队列里面的元素，按位置逐个比较，比如：
          第一个位置中，两个队列面的元素分别为 1 和 2，是不同的，则都加入结果队列中: (1, 2)
          第二个位置中，两个均为2，忽略
          第三个忽略
          第四个位置，3 和 4 不同，加入结果队列: (3, 4)
          ......
          等等
     */
    vector<int> c1 = { 1, 2, 2, 4, 6, 7, 7, 9 };
    deque<int>  c2 = { 2, 2, 2, 3, 6, 6, 8, 9 };
    helper::PRINT_ELEMENT(c1, "c1: ");
    helper::PRINT_ELEMENT(c2, "c2: ");

    cout << "c1 symmetric different with c2: ";
    set_symmetric_difference(c1.cbegin(), c1.cend(),
                             c2.cbegin(), c2.cend(),
                             ostream_iterator<int>(cout, " "));
    cout << endl;
}

void merge_consecutive_demo()
{
    /*
     *  void
        inplace_merge (BidirectionalIterator beg1, BidirectionalIterator end1beg2,
                       BidirectionalIterator end2)
        void
        inplace_merge (BidirectionalIterator beg1, BidirectionalIterator end1beg2,
                       BidirectionalIterator end2, BinaryPredicate op)
        • Both forms merge the consecutive sorted source ranges [beg1,end1beg2) and [end1beg2,end2)
          so that the range [beg1,end2) contains the elements as a sorted summary rang
        不知道这个算法的意义是什么，可能只有预先知道这个队列是由连续的两个有序队列组成的，然后需要重新对整个队列排序才能用得到
     */
    vector<int> coll;
    helper::INSERT_ELEMENTS(coll, 1, 7);
    helper::INSERT_ELEMENTS(coll, 1, 8);
    helper::PRINT_ELEMENT(coll, "coll: ");

    auto pos = find(coll.begin(), coll.end(), 7);
    ++pos;

    inplace_merge(coll.begin(), pos, coll.end());
    helper::PRINT_ELEMENT(coll, "coll inplace merged: ");
}

void merge_elements_demos()
{
    /*
     * The following algorithms merge elements of two ranges. The algorithms process the sum, the union,
       the intersection, and so on.
     */
    merge_demo();
    union_demo();
    intersection_demo();
    difference_demo();
    symmetric_difference_demo();
    merge_consecutive_demo();
}

void Run()
{
    /*
     *  Sorted-range algorithms require that the source ranges have the elements sorted according to their
        sorting criterion. These algorithms may have significantly better performance than similar algo-
        rithms for unsorted ranges (usually logarithmic instead of linear complexity). You can use these
        algorithms with iterators that are not random-access iterators. However, in this case, the algorithms
        have linear complexity because they have to step through the sequence element-by-element. Never-
        theless, the number of comparisons may still have logarithmic complexity.

        According to the standard, calling these algorithms for sequences that are not sorted on entry
        results in undefined behavior. However, for most implementations, calling these algorithms also
        works for unsorted sequences. Nevertheless, to rely on this fact is not portable.

        Associative and unordered containers provide special member functions for some of the search-
        ing algorithms presented here. When searching for a special value or key, you should use them.
     */
    searching_elements_demos();
    merge_elements_demos();
}

}
}