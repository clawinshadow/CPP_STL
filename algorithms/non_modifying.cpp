#include "non_modifying.h"
#include "helper.h"

#include <iostream>
#include <string>

using namespace std;

namespace algorithms {
namespace non_modifying {

/*
 * Nonmodifying algorithms change neither the order nor the value of the elements they process. These
   algorithms operate with input and forward iterators; therefore, you can call them for all standard containers.

    Name                        Effect
    for_each()                  Performs an operation for each element
    count()                     Returns the number of elements
    count_if()                  Returns the number of elements that match a criterion
    min_element()               Returns the element with the smallest value
    max_element()               Returns the element with the largest value
    minmax_element()            Returns the elements with the smallest and largest value (since C++11)
    find()                      Searches for the first element with the passed value
    find_if()                   Searches for the first element that matches a criterion
    find_if_not()               Searches for the first element that matches a criterion not (since C++11)
    search_n()                  Searches for the first n consecutive elements with certain properties
    search()                    Searches for the first occurrence of a subrange
    find_end()                  Searches for the last occurrence of a subrange
    find_first_of()             Searches the first of several possible elements
    adjacent_find()             Searches for two adjacent elements that are equal (by some criterion)
    equal()                     Returns whether two ranges are equal
    is_permutation()            Returns whether two unordered ranges contain equal elements (since C++11)
    mismatch()                  Returns the first elements of two sequences that differ
    lexicographical_compare()   Returns whether a range is lexicographically less than another range
    is_sorted()                 Returns whether the elements in a range are sorted (since C++11)
    is_sorted_until()           Returns the first unsorted element in a range (since C++11)
    is_partitioned()            Returns whether the elements in a range are partitioned in two
                                groups according to a criterion (since C++11)
    partition_point()           Returns the partitioning element for a range partitioned into
                                elements fulfilling and elements not fulfilling a predicate (since C++11)
    is_heap()                   Returns whether the elements in a range are sorted as a heap (since C++11)
    is_heap_until()             Returns the first element in a range not sorted as a heap (since C++11)
    all_of()                    Returns whether all elements match a criterion (since C++11)
    any_of()                    Returns whether at least one element matches a criterion (since C++11)
    none_of()                   Returns whether none of the elements matches a criterion (since C++11)
 */

/*
 * difference_type count (InputIterator beg, InputIterator end, const T& value)
   difference_type count_if (InputIterator beg, InputIterator end, UnaryPredicate op)

    • The first form counts the elements in the range [beg,end) that are equal to value value.
    • The second form counts the elements in the range [beg,end) for which the unary predicate
        op(elem)
      yields true.
    • The type of the return value, difference_type, is the difference type of the iterator:
        typename iterator_traits<InputIterator>::difference_type
    • Note that op should not change its state during a function call.
    • op should not modify the passed arguments.
    • Associative and unordered containers provide a similar member function, count(), to count the
      number of elements that have a certain value as key.
    • Complexity: linear (numElems comparisons or calls of op(), respectively).
 */
void count_demo()
{
    vector<int> coll;
    helper::INSERT_ELEMENTS(coll,1,9);
    helper::PRINT_ELEMENT(coll,"coll: ");

    // count elements with value 4
    int num = count(coll.cbegin(), coll.cend(),4);
    cout << "number of elements equal to 4: " << num << endl;

    // count elements with even value
    num = count_if(coll.begin(), coll.end(),
                   [] (int elem) -> bool {
                        return elem % 2 == 0;
                    });
    cout << "number of elements with even value: " << num << endl;
}

/*
 *  ForwardIterator
    min_element (ForwardIterator beg, ForwardIterator end)

    ForwardIterator
    min_element (ForwardIterator beg, ForwardIterator end, CompFunc op)

    ForwardIterator
    max_element (ForwardIterator beg, ForwardIterator end)

    ForwardIterator
    max_element (ForwardIterator beg, ForwardIterator end, CompFunc op)

    pair<ForwardIterator,ForwardIterator>
    minmax_element (ForwardIterator beg, ForwardIterator end)

    pair<ForwardIterator,ForwardIterator>
    minmax_element (ForwardIterator beg, ForwardIterator end, CompFunc op)

    • The versions without op compare the elements with operator <.
    • op is used to compare two elements:
        op(elem1,elem2)
      It should return true when the first element is less than the second element.
    • If more than one minimum or maximum element exists, min_element() and max_element()
      return the first found; minmax_element() returns the first minimum but the last maximum
      element, so max_element() and minmax_element() don’t yield the same maximum element.
    • If the range is empty, the algorithms return be
 */
bool absLess(int elem1, int elem2)
{
    return abs(elem1) < abs(elem2);
}

void min_max_demo()
{
    deque<int> coll;
    helper::INSERT_ELEMENTS(coll, 2, 6);
    helper::INSERT_ELEMENTS(coll, -3, 6);

    helper::PRINT_ELEMENT(coll);

    // 注意它们返回的是一个iterator，是一个位置
    cout << "min element: " << *min_element(coll.begin(), coll.end()) << endl;
    cout << "max element: " << *max_element(coll.begin(), coll.end()) << endl;

    auto min_max = minmax_element(coll.begin(), coll.end());
    cout << "min elem: " << *(min_max.first) << endl;
    cout << "max elem: " << *(min_max.second) << endl; // 此处指向的是最后一个最大的元素
    cout << "distance of min & max: " << distance(min_max.first, min_max.second) << endl;

    // process and print minimum and maximum of absolute values
    cout << "minimum of absolute values: "
         << *min_element(coll.cbegin(), coll.cend(), absLess)
         << endl;
    cout << "maximum of absolute values: "
         << *max_element(coll.cbegin(), coll.cend(), absLess)
         << endl;
}

void search__fist_matching()
{
    /*
     *  InputIterator
        find (InputIterator beg, InputIterator end, const T& value)

        InputIterator
        find_if (InputIterator beg, InputIterator end, UnaryPredicate op)

        InputIterator
        find_if_not (InputIterator beg, InputIterator end, UnaryPredicate op)

        • The first form returns the position of the first element in the range [beg,end) that has a value equal to value.
        • The second form returns the position of the first element in the range [beg,end) for which the unary predicate
            op(elem)
          yields true.
        • The third form (available since C++11) returns the position of the first element in the range
          [beg,end) for which the unary predicate
            op(elem)
          yields false.
        • All algorithms return end if no matching elements are found.
        • Note that op should not change its state during a function call.
        • op should not modify the passed arguments.
        • If the range is sorted, you should use the lower_bound(), upper_bound(), equal_range(),
          or binary_search() algorithms (see Section 11.10, page 608).
        • Associative and unordered containers provide an equivalent member function, find(),
          which has a better complexity (logarithmic for associative and even constant for unordered containers).
        • Complexity: linear (at most, numElems comparisons or calls of op(), respectively).
     */
    list<int> coll;
    helper::INSERT_ELEMENTS(coll, 1, 9);
    helper::INSERT_ELEMENTS(coll, 1, 9);

    helper::PRINT_ELEMENT(coll, "coll: ");

    // find the first element with value 4
    list<int>::const_iterator  pos1 = find(coll.cbegin(), coll.cend(), 4);
    // find the second element with value 4
    list<int>::const_iterator  pos2 = find(++pos1, coll.cend(), 4);

    // print the elements between these 2 positions
    // 因为之前 pos1 被 ++ 过，所以这里为了囊括第一个4，需要再--一下
    std::copy(--pos1, ++pos2, ostream_iterator<int>(cout, " "));
    cout << endl;

    //find the first element which value is greater than 3
    auto pos3 = find_if(coll.begin(), coll.end(), bind(greater<int>(), std::placeholders::_1, 3));
    cout << "the " << distance(coll.begin(), pos3) + 1 << ". element is greater than 3" << endl;

    //find the first element which value is not less than 5
    auto pos4 = find_if_not(coll.begin(), coll.end(), [](int elem) -> bool { return elem < 5; });
    cout << "the " << distance(coll.begin(), pos4) + 1 << ". element is not less than 5" << endl;
}

void search_first_n()
{
    /*
     *  --Search First n Matching Consecutive Elements
        ForwardIterator
        search_n (ForwardIterator beg, ForwardIterator end, Size count, const T& value)

        ForwardIterator
        search_n (ForwardIterator beg, ForwardIterator end, Size count, const T& value, BinaryPredicate op)

        • The first form returns the position of the first of count consecutive elements in the range [beg,end)
          that all have a value equal to value.
        • The second form returns the position of the first of count consecutive elements in the range
          [beg,end) for which the binary predicate
            op(elem,value)
          yields true (value is the passed fourth argument).
        • Both forms return end if no matching elements are found.
        • These algorithms were not part of the original STL and were not introduced very carefully.
          The fact that the second form uses a binary predicate instead of a unary predicate breaks the
          consistency of the original STL.
        • Complexity: linear
     */

    deque<int> coll;
    coll = { 1, 2, 7, 7, 6, 3, 9, 5, 7, 7, 7, 3, 6 };
    helper::PRINT_ELEMENT(coll, "coll: ");

    // find three consecutive elements with value 7
    auto pos = search_n(coll.begin(), coll.end(), 3, 7);
    // print result
    if (pos != coll.end()) {
        cout << "three consecutive elements with value 7 "
             << "start with " << distance(coll.begin(),pos) +1
             << ". element" << endl;
    }
    else {
        cout << "no four consecutive elements with value 7 found"
             << endl;
    }
    // find four consecutive odd elements
    pos = search_n (coll.begin(), coll.end(),
                    4,
                    0,
                    // 这里的第二个参数 value 就很多余，这也是这个函数不符合STL一般标准的一个显著之处
                    [](int elem, int value){
                        return elem%2==1;
                    });

    if (pos != coll.end()) {
        cout << "first four consecutive odd elements are: ";
        for (int i=0; i<4; ++i, ++pos) {
            cout << *pos << ' ';
        }
    }
    else {
        cout << "no four consecutive elements with value > 3 found";
    }
    cout << endl;
}

// checks whether an element is even or odd
bool checkEven (int elem, bool even)
{
    if (even) {
        return elem % 2 == 0;
    }
    else {
        return elem % 2 == 1;
    }
}

void search_first_sub_range()
{
    /*
     *  ForwardIterator1
        search (ForwardIterator1 beg, ForwardIterator1 end,
                ForwardIterator2 searchBeg, ForwardIterator2 searchEnd)
        ForwardIterator1
        search (ForwardIterator1 beg, ForwardIterator1 end,
                ForwardIterator2 searchBeg, ForwardIterator2 searchEnd,
                BinaryPredicate op)
        • Both forms return the position of the first element of the first subrange matching the range
          [searchBeg,searchEnd) in the range [beg,end).
        • In the first form, the elements of the subrange have to be equal to the elements of the whole range.
        • In the second form, for every comparison between elements, the call of the binary predicate
            op(elem,searchElem)
          has to yield true.
        • Both forms return end if no matching elements are found.
     */
    deque<int> coll;
    list<int> subcoll;

    helper::INSERT_ELEMENTS(coll, 1, 7);
    helper::INSERT_ELEMENTS(coll, 1, 7);
    helper::INSERT_ELEMENTS(subcoll, 3, 6);

    helper::PRINT_ELEMENT(coll, "coll: ");
    helper::PRINT_ELEMENT(subcoll, "subcoll: ");

    auto pos = search(coll.begin(), coll.end(),
                      subcoll.begin(), subcoll.end());
    while (pos != coll.end())
    {
        cout << "subcoll found starting with element "
             << distance(coll.begin(), pos) + 1
             << endl;

        ++pos;
        pos = search(pos, coll.end(),
                     subcoll.begin(), subcoll.end());
    }

    // arguments for checkEven()
    // - check for: ‘‘even odd even’’
    bool checkEvenArgs[3] = { true, false, true };
    // search first subrange in coll
    deque<int>::iterator pos2;
    pos2 = search (coll.begin(), coll.end(),
                   checkEvenArgs, checkEvenArgs + 3, // subrange values
                   checkEven);    // subrange criterion
    cout << "subrange found starting with element "
         << distance(coll.begin(), pos2) + 1
         << endl;
}

void search_last_subrange()
{
    /*
     *  Search Last Subrange 从后往前找
        ForwardIterator1
        find_end (ForwardIterator1 beg, ForwardIterator1 end,
                  ForwardIterator2 searchBeg, ForwardIterator2 searchEnd)

        ForwardIterator1
        find_end (ForwardIterator1 beg, ForwardIterator1 end,
                  ForwardIterator2 searchBeg, ForwardIterator2 searchEnd,
                  BinaryPredicate op)

        • Both forms return the position of the first element of the last subrange matching the range
          [searchBeg,searchEnd) in the range [beg,end).
        • In the first form, the elements of the subrange have to be equal to the elements of the whole range.
        • In the second form, for every comparison between elements, the call of the binary predicate
            op(elem,searchElem)
          has to yield true.
        • These algorithms were not part of the original STL. Unfortunately, they were called find_end()
          instead of search_end(), which would be more consistent, because the algorithm used to search
          the first subrange is called search(). 确实应该叫 search_end() 更有意义
     */
    deque<int> coll;
    list<int> subcoll;
    helper::INSERT_ELEMENTS(coll, 1, 7);
    helper::INSERT_ELEMENTS(coll, 1, 7);
    helper::INSERT_ELEMENTS(subcoll,3,6);
    helper::PRINT_ELEMENT(coll, "coll: ");
    helper::PRINT_ELEMENT(subcoll,"subcoll: ");

    // search last occurrence of subcoll in coll
    deque<int>::iterator pos;
    pos = find_end (coll.begin(), coll.end(),
                    subcoll.begin(), subcoll.end());
    cout << "subcoll found starting with element "
         << distance(coll.begin(), pos) + 1
         << endl;
}

void search_first_of()
{
    /*
     * Search First of Several Possible Elements
     *  InputIterator
        find_first_of (InputIterator beg, InputIterator end,
                       ForwardIterator searchBeg, ForwardIterator searchEnd)

        InputIterator
        find_first_of (InputIterator beg, InputIterator end,
                       ForwardIterator searchBeg, ForwardIterator searchEnd,
                       BinaryPredicate op)

       • The first form returns the position of the first element in the range [beg,end) that is also in the
         range [searchBeg,searchEnd).
         从 beg 开始遍历直至 end, 一旦有一个元素存在于 [searchBeg,searchEnd) 这个范围内，就算是找到了
         ......
     */
    vector<int> coll;
    list<int> searchcoll;
    helper::INSERT_ELEMENTS(coll,1,11);
    helper::INSERT_ELEMENTS(searchcoll,3,5);
    helper::PRINT_ELEMENT(coll, "coll: ");
    helper::PRINT_ELEMENT(searchcoll,"searchcoll: ");

    // search first occurrence of an element of searchcoll in coll
    vector<int>::iterator pos;
    pos = find_first_of (coll.begin(), coll.end(), // range
                         searchcoll.begin(),
                         searchcoll.end());
    cout << "first element of searchcoll in coll is element "
         << distance(coll.begin(), pos) + 1
         << endl;

    auto pos2 = find_first_of (coll.rbegin(), coll.rend(),
                               searchcoll.begin(),
                               searchcoll.end()); // 从后面倒着往前找
    cout << "first element of searchcoll in coll is element "
         << distance(coll.begin(), pos2.base())  // 注意此处要使用 pos2.base() 获取 reverse_iterator 对应的原始位置
         << endl;
}

void search_adjacent_equal()
{
    /*
     *  Search Two Adjacent, Equal Elements 搜索队列中两个相邻的相等元素
        ForwardIterator
        adjacent_find (ForwardIterator beg, ForwardIterator end)

        ForwardIterator
        adjacent_find (ForwardIterator beg, ForwardIterator end,
                       BinaryPredicate op)

        • The first form returns the first element in the range [beg,end) that has a value equal to the value
          of the following element.
     */
    vector<int> coll;
    coll.push_back(1);
    coll.push_back(3);
    coll.push_back(2);
    coll.push_back(4);
    coll.push_back(5);
    coll.push_back(5);
    coll.push_back(0);

    helper::PRINT_ELEMENT(coll,"coll: ");
    // search first two elements with equal value
    vector<int>::iterator pos = adjacent_find (coll.begin(), coll.end());
    if (pos != coll.end()) {
        cout << "first two elements with equal value have position "
             << distance(coll.begin(),pos) + 1
             << endl;
    }

    pos = adjacent_find (coll.begin(), coll.end(),
            [](int elem1, int elem2) -> bool {
                return elem1 * 2 == elem2;
            });
    if (pos != coll.end())
    {
        cout << "first two elements with second value twice the "
             << "first have pos. "
             << distance(coll.begin(), pos) + 1
             << endl;
    }
}

void search_demos()
{
    search__fist_matching();
    search_first_n();
    search_first_sub_range();
    search_last_subrange();
    search_first_of();
    search_adjacent_equal();
}

void range_test_equality()
{
    /*
     *  bool
        equal (InputIterator1 beg, InputIterator1 end,
        InputIterator2 cmpBeg)

        bool
        equal (InputIterator1 beg, InputIterator1 end,
               InputIterator2 cmpBeg,
               BinaryPredicate op)

       • The first form returns whether the elements in the range [beg,end) are equal to the elements in
         the range starting with cmpBeg.
       .....
       • The caller must ensure that the range starting with cmpBeg contains enough elements.
       • To determine whether two sequences contain the same elements in different order, algorithm
         is_permutation() is provided since C++11
     */
    vector<int> coll1;
    list<int> coll2;
    helper::INSERT_ELEMENTS(coll1,1,7);
    helper::INSERT_ELEMENTS(coll2,3,9);
    helper::PRINT_ELEMENT(coll1, "coll1: ");
    helper::PRINT_ELEMENT(coll2, "coll2: ");

    // check whether both collections are equal
    bool all_equal = equal(coll1.begin(), coll1.end(), coll2.begin());
    cout << boolalpha << "coll1 == coll2: " << all_equal << endl;

    bool equal_plus_2 = equal(coll1.begin(), coll1.end(), coll2.begin(),
                              [](int elem1, int elem2) -> bool {
                                  return elem1 + 2 == elem2;
                              });
    cout << boolalpha << "coll1 + 2 == coll2: " << equal_plus_2 << endl;
}

void range_test_equality_unordered()
{
    /*
    bool
    is_permutation (ForwardIterator1 beg1, ForwardIterator1 end1,
                    ForwardIterator2 beg2)
    bool
    is_permutation (ForwardIterator1 beg1, ForwardIterator1 end1,
                    ForwardIterator2 beg2,
                    CompFunc op)
    • Both forms return whether the elements in the range [beg1,end1) are a permutation of the ele-
      ments in the range starting with beg2; that is, whether they return equal elements in whatever
      order.
    • Complexity: at worst quadratic (numElems1 comparisons or calls of op(), if all elements are
      equal and have the same order).
    */
    vector<int> coll1;
    list<int> coll2;

    coll1 = { 1, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    coll2 = { 1, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

    helper::PRINT_ELEMENT(coll1, "coll1: ");
    helper::PRINT_ELEMENT(coll2, "coll2: ");

    // check whether both collections have equal elements in any order
    if (is_permutation (coll1.cbegin(), coll1.cend(),
                        coll2.cbegin())) {
        cout << "coll1 and coll2 have equal elements - unordered: " << endl;
    }
    else {
        cout << "coll1 and coll2 don’t have equal elements - unordered: " << endl;
    }
}

void range_mismatch()
{
    /*
     * Search the First Difference 检测两个队列中，从哪个元素开始不一样的
     * pair<InputIterator1,InputIterator2>
       mismatch (InputIterator1 beg, InputIterator1 end,
                 InputIterator2 cmpBeg)

       pair<InputIterator1,InputIterator2>
       mismatch (InputIterator1 beg, InputIterator1 end,
                 InputIterator2 cmpBeg,
                 BinaryPredicate op)
       返回的pair中，分别标识了两个队列中的位置
       ......
       If no difference is found, a pair<> of end and the corresponding element of the second range
       is returned. Note that this does not mean that both sequences are equal, because the second
       sequence might contain more elements.

       To check whether two ranges are equal, you should use algorithm equal()
     */
    vector<int> coll1 = { 1, 2, 3, 4, 5, 6 };
    list<int>   coll2 = { 1, 2, 4, 8, 16, 3 };

    helper::PRINT_ELEMENT(coll1,"coll1: ");
    helper::PRINT_ELEMENT(coll2,"coll2: ");

    auto values = mismatch(coll1.cbegin(), coll1.cend(), coll2.cbegin());
    if (values.first == coll1.end())
    {
        cout << "no mismatch found.." << endl;
    } else {
        cout << "first mismatch: "
             << *values.first << " and "
             << *values.second << endl;
    }

    // find first position where the element of coll1 is not
    // less than the corresponding element of coll2
    values = mismatch (coll1.cbegin(), coll1.cend(),
                       coll2.cbegin(),
                       less_equal<int>());
    if (values.first == coll1.end()) {
        cout << "always less-or-equal" << endl;
    }
    else {
        cout << "not less-or-equal: "
             << *values.first << " and "
             << *values.second << endl;
    }
}

void range_lexico_compare()
{
    /*
     * Testing for “Less Than”
        bool
        lexicographical_compare(InputIterator1 beg1, InputIterator1 end1,
                InputIterator2 beg2, InputIterator2 end2)
        bool
        lexicographical_compare(InputIterator1 beg1, InputIterator1 end1,
                InputIterator2 beg2, InputIterator2 end2,
                CompFunc op)

        • Both forms return whether the elements in the range [beg1,end1) are “lexicographically less
          than” the elements in the range [beg2,end2).
        • The first form compares the elements by using operator <.
        • The second form compares the elements by using the binary predicate
            op(elem1,elem2)
          which should return true when elem1 is less than elem2.
        • Lexicographical comparison means that sequences are compared element-by-element until any
          of the following occurs:
            – When two elements are not equal, the result of their comparison is the result of the whole
              comparison.
            – When one sequence has no more elements, the sequence that has no more elements is less
              than the other. Thus, the comparison yields true if the first sequence is the one that has no
              more elements.
            – When both sequences have no more elements, both sequences are equal, and the result of the
              comparison is false.
            从队列开始，逐个逐个的比较元素，一旦发现队列1有元素小于队列2，就返回true，如果队列1遍历完了，而此时队列2还有元素，
            也返回true，如果此时队列2也没元素了，那就是false
     */
    list<int> c1, c2, c3, c4;
    helper::INSERT_ELEMENTS(c1, 1, 5);
    c4 = c3 = c2 = c1;

    c2.push_back(2);
    c3.push_back(7);
    helper::PRINT_ELEMENT(c1, "c1: ");
    helper::PRINT_ELEMENT(c2, "c2: ");
    helper::PRINT_ELEMENT(c3, "c3: ");
    helper::PRINT_ELEMENT(c4, "c4: ");

    cout << boolalpha << "c1 vs c2: "
         << lexicographical_compare(c1.begin(), c1.end(), c2.begin(), c2.end()) << endl;
    cout << boolalpha << "c2 vs c3: "
         << lexicographical_compare(c2.begin(), c2.end(), c3.begin(), c3.end()) << endl;
    cout << boolalpha << "c1 vs c4: "
         << lexicographical_compare(c1.begin(), c1.end(), c4.begin(), c4.end()) << endl;
}

void compare_ranges_demos()
{
    range_test_equality();
    range_test_equality_unordered();
    range_mismatch();
    range_lexico_compare();
}

void check_for_sorting()
{
    /* bool
       is_sorted (ForwardIterator beg, ForwardIterator end)
       bool
       is_sorted (ForwardIterator beg, ForwardIterator end, BinaryPredicate op)

       ForwardIterator
       is_sorted_until (ForwardIterator beg, ForwardIterator end)
       ForwardIterator
       is_sorted_until (ForwardIterator beg, ForwardIterator end, BinaryPredicate op)

       • is_sorted() returns whether the elements in the range [beg,end) are sorted.
       • is_sorted()_until returns the position of the first element in the range [beg,end), which
         breaks the sorting of this range, or end if none.
       • If the range is empty or has only one element, the algorithms return true or end, respectively.
       • Complexity: linear
    */
    vector<int> coll = {1, 1, 3, 4, 5, 7, 9};
    helper::PRINT_ELEMENT(coll, "coll: ");

    bool sorted = is_sorted(coll.cbegin(), coll.cend());
    std::cout << boolalpha << "coll is sorted: " << sorted << endl;

    map<int, string> dict = { {1,"Bill"}, {2,"Jim"}, {3,"Nico"}, {4,"Liu"}, {5,"Ai"} };
    helper::PRINT_MAPPED_ELEMENTS(dict, "dict: ");

    auto compare = [](const pair<int, string> &_p1,
                      const pair<int, string> &_p2) -> bool {
        return _p1.second < _p2.second;
    };
    bool dict_sorted = is_sorted(dict.cbegin(), dict.cend(), compare);
    cout << boolalpha << "dict is sorted: " << dict_sorted << endl;

    auto pos = is_sorted_until(dict.cbegin(), dict.cend(), compare);
    if (pos != dict.end())
    {
        cout << "dict is sorted until: " << pos->second << endl;
    }
}

void check_for_partition()
{
    /*
     *  bool
        is_partitioned (InputIterator beg, InputIterator end, UnaryPredicate op)

        ForwardIterator
        partition_point (ForwardIterator beg, ForwardIterator end, BinaryPredicate op)
        顾名思义，这个是检测队列是否是一团一团的聚集的，从头开始遍历，op返回true的是一团，之后的元素应该都是返回false的
        • is_partitioned() returns whether the elements in the range [beg,end) are partitions, so all the
          elements fulfilling the predicate op() are positioned before all elements that do not fulfill it.
        • partition_point() returns the position of the first element in the partitioned range [beg,end).
          Thus, for [beg,end), is_partitioned() has to yield true on entry.
     */
    auto isOdd = [](int elem) -> bool {
        return elem % 2 == 1;
    };
    vector<int> coll = { 5, 3, 9, 1, 3, 4, 8, 2, 6 };
    helper::PRINT_ELEMENT(coll, "coll: ");

    // 5, 3, 9, 1, 3 都是奇数，isOdd返回为true, 后面的 4,8,2,6 都是偶数，所以这个是 partitioned
    bool is_p = is_partitioned(coll.cbegin(), coll.cend(), isOdd);
    cout << "coll is partitioned: " << boolalpha << is_p << endl;

    if (is_p)
    {
        auto pos = partition_point(coll.cbegin(), coll.cend(), isOdd); //所以这里不用非得是 binary predicate
        cout << "partition point: " << *pos <<endl;
    }

    vector<int> coll2 = {2, 4, 1, 3};  // 前面一堆是false，后面一堆是true，是不行的
    helper::PRINT_ELEMENT(coll2, "coll2: ");

    bool is_p_2 = is_partitioned(coll2.cbegin(), coll2.cend(), isOdd);
    cout << "coll2 is partitioned: " << boolalpha << is_p_2 << endl;
}

void check_for_heap()
{
    /*
     *  bool
        is_heap (RandomAccessIterator beg, RandomAccessIterator end)
        bool
        is_heap (RandomAccessIterator beg, RandomAccessIterator end, BinaryPredicate op)
                 RandomAccessIterator

        is_heap_until (RandomAccessIterator beg, RandomAccessIterator end)
                       RandomAccessIterator
        is_heap_until (RandomAccessIterator beg, RandomAccessIterator end,
                       BinaryPredicate op)

        • is_heap() returns whether the elements in the range [beg,end) are a heap (详见 sorting algorithms),
          which means that beg is (one of) the maximum element(s).
        • is_heap()_until returns the position of the first element in the range [beg,end) that breaks the
          sorting as a heap (is larger than the first element) or end if none.
        • The first and third forms use operator < to compare elements. The second and fourth forms use
          the binary predicate
            op(elem1,elem2)
          which should return true if elem1 is “less than” elem2.
     */
    vector<int> coll1 = { 9, 8, 7, 7, 7, 5, 4, 2, 1 };
    vector<int> coll2 = { 5, 3, 2, 1, 4, 7, 9, 8, 6 };
    helper::PRINT_ELEMENT(coll1, "coll1: ");
    helper::PRINT_ELEMENT(coll2, "coll2: ");

    cout << boolalpha << "coll1 is heap: "
         << is_heap(coll1.cbegin(), coll1.cend()) << endl;
    cout << boolalpha << "coll2 is heap: "
         << is_heap(coll2.cbegin(), coll2.cend()) << endl;

    // print the first element that is not a heap in coll2
    auto pos = is_heap_until (coll2.cbegin(), coll2.cend());
    if (pos != coll2.end()) {
        cout << "first non-heap element: " << *pos << endl;
    }
}

void check_for_all_any_none()
{
    /*
     *  bool
        all_of (InputIterator beg, InputIterator end, UnaryPredicate op)

        bool
        any_of (InputIterator beg, InputIterator end, UnaryPredicate op)

        bool
        none_of (InputIterator beg, InputIterator end, UnaryPredicate op)

        • These algorithms return whether for all, any (at least one), or none of the elements in the range
          [beg,end), the unary predicate
            op(elem)
          yields true.
        • If the range is empty, all_of() and none_of() return true, whereas any_of() returns false.
     */
    vector<int> coll;
    helper::INSERT_ELEMENTS(coll, 1, 9);
    helper::PRINT_ELEMENT(coll, "coll: ");
    // define an object for the predicate (using a lambda)
    auto isEven = [](int elem) -> bool {
        return elem%2==0;
    };

    // print whether all, any, or none of the elements are/is even
    cout << boolalpha << "all even?: "
         << all_of(coll.cbegin(), coll.cend(), isEven) << endl;
    cout << "any even?: "
         << any_of(coll.cbegin(), coll.cend(), isEven) << endl;
    cout << "none even?: "
         << none_of(coll.cbegin(), coll.cend(), isEven) << endl;
}

void predicates_for_ranges()
{
    check_for_sorting();
    check_for_partition();
    check_for_heap();
    check_for_all_any_none();
}

void Run()
{
    count_demo();
    min_max_demo();
    search_demos();
    compare_ranges_demos();
    predicates_for_ranges();
}

}
}