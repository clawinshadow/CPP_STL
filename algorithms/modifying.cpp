#include "modifying.h"
#include "helper.h"

#include <cstdlib>

using namespace std;

namespace algorithms {
namespace modifying {

void copy_demo()
{
    /*
     *  OutputIterator
        copy (InputIterator sourceBeg, InputIterator sourceEnd,
              OutputIterator destBeg)

        OutputIterator
        copy_if (InputIterator sourceBeg, InputIterator sourceEnd,
                 OutputIterator destBeg,
                 UnaryPredicate op)

        OutputIterator
        copy_n (InputIterator sourceBeg,
                Size num,
                OutputIterator destBeg)

        BidirectionalIterator2
        copy_backward (BidirectionalIterator1 sourceBeg,
                       BidirectionalIterator1 sourceEnd,
                       BidirectionalIterator2 destEnd)
        • All algorithms copy all elements of a source range ([sourceBeg,sourceEnd) or num elements
          starting with sourceBeg) into the destination range starting with destBeg or ending with destEnd,
          respectively.
        • They return the position after the last copied element in the destination range (the first element
          that is not overwritten).
        • For copy(), destBeg should not be part of [sourceBeg,sourceEnd). For copy_if(), source and
          destination ranges should not overlap. For copy_backward(), destEnd should not be part of
          (sourceBeg,sourceEnd].
          要注意这点：就是说在copy()和copy_backward()方法中，第三个参数都不应该在[sourceBeg,sourceEnd)范围内
                    另外，copy_if()的目标范围不能和原范围有重合的地方
        • copy() iterates forward through the sequence, whereas copy_backward() iterates backward.
          This difference matters only if the source and destination ranges overlap.
            – To copy a subrange to the front, use copy(). Thus, for copy(), destBeg should have a
              position in front of sourceBeg.
            – To copy a subrange to the back, use copy_backward(). Thus, for copy_backward(),
              destEnd should have a position after sourceEnd.
          注意：在copy()方法中，第三个参数叫destBeg，顾名思义就是目标范围的起点，但是在 copy_backward() 方法中，
               第三个参数叫 destEnd, 那就是说这是目标范围的终点，是从(destEnd - 1)这个位置开始往前插入元素的。
               destBeg应该在sourceBeg的前面，destEnd应该在sourceEnd的就后面，这些主要是阐明在同一个队列里面复制
               元素的情况下应该注意的事项。
        • Since C++11, if the source elements are no longer used, you should prefer move() over copy()
          and move_backward() over and copy_backward()
        • Before C++11, no copy_if() and copy_n() algorithms were provided. To copy only those
          elements meeting a certain criterion, you had to use remove_copy_if()
        • Use reverse_copy() to reverse the order of the elements during the copy.
          Note that reverse_copy() may be slightly more efficient than using copy() with reverse iterators.
        • To assign all elements of a container, use the assignment operator if the containers have the
          same type or the assign() member function if the containers have different types
        • To remove elements while they are being copied, use remove_copy() and remove_copy_if()
        • To modify elements while they are being copied, use transform() or replace_copy()
        • Use partition_copy() to copy elements into two destination ranges: one fulfilling and one not fulfilling a predicate.
        • Complexity: linear (numElems assignments).
     */
    vector<string> coll1 = { "Hello", "this", "is", "an", "example" };

    list<string> coll2;
    // copy elements of coll1 into coll2
    // - use back inserter to insert instead of overwrite
    copy(coll1.cbegin(), coll1.cend(), back_inserter(coll2));

    copy(coll2.cbegin(), coll2.cend(), ostream_iterator<string>(cout, " "));
    cout << endl;

    //overwriting
    copy(coll1.crbegin(), coll1.crend(), coll2.begin());

    copy(coll2.cbegin(), coll2.cend(), ostream_iterator<string>(cout, " "));
    cout << endl;

    list<string> coll3;
    copy_n(coll1.cbegin(), 3, back_inserter(coll3)); //copy 3 elements from coll1 to coll3;
    helper::PRINT_ELEMENT(coll3, "coll3: ");

    vector<string> coll4 = {"1", "2", "3", "4", "5"}; //reserve same elements size with coll1
    //copy完毕后，所有元素的顺序与coll1一样，只不过内部工作机制是从coll4的屁股后面开始往前copy
    copy_backward(coll1.cbegin(), coll1.cend(), coll4.end());
    helper::PRINT_ELEMENT(coll4, "coll4: ");

    // --- 单个容器中的copy ---
    vector<char> chars (10, '.');
    for (int c = 'a'; c < 'g'; c++ )
        chars.push_back(c);
    chars.insert(chars.end(), 10, '.');
    helper::PRINT_ELEMENT(chars, "chars: ");

    vector<char> c1(chars.cbegin(), chars.cend());
    copy(c1.begin() + 10, c1.begin() + 16, c1.begin() + 7);
    helper::PRINT_ELEMENT(c1, "c1   : ");

    vector<char> c2(chars.cbegin(), chars.cend());
    copy_backward(c2.begin() + 10, c2.begin() + 16, c2.begin() + 19);
    helper::PRINT_ELEMENT(c2, "c2   : ");
}

void move_demo()
{
    /*
     *  OutputIterator
        move (InputIterator sourceBeg, InputIterator sourceEnd,
              OutputIterator destBeg)

        BidirectionalIterator2
        move_backward (BidirectionalIterator1 sourceBeg,
                       BidirectionalIterator1 sourceEnd,
                       BidirectionalIterator2 destEnd)

        • Both algorithms move all elements of the source range [sourceBeg,sourceEnd) into the destina-
          tion range starting with destBeg or ending with destEnd, respectively.
        • Call for each element:
            *destElem=std::move(*sourceElem)
          Thus, if the element type provides move semantics, the value of the source elements becomes
          undefined, so the source element should no longer be used except to reinitialize or assign a
          new value to it. Otherwise, the elements are copied as with copy() or copy_backward()
          其余关于 destBeg, destEnd 这些第三个参数的约束，都与copy, copy_backward()一致
     */
    vector<string> coll1 = { "Hello", "this", "is", "an", "example" };
    helper::PRINT_ELEMENT(coll1, "coll1 before moved: ");

    list<string> dest;
    move(coll1.cbegin(), coll1.cend(), back_inserter(dest));
    helper::PRINT_ELEMENT(dest, "dest: ");
    helper::PRINT_ELEMENT(coll1, "coll1 after being moved: ");
}

void transform_and_combine_demo()
{
    /*
     *  The transform() algorithms provide two abilities:
        1. The first form has four arguments. It transforms elements from a source to a destination range.
        Thus, this form copies and modifies elements in one step.
        2. The second form has five arguments. It combines elements from two source sequences and writes
        the results to a destination range.

        -- transforming elements --
        OutputIterator
        transform (InputIterator sourceBeg, InputIterator sourceEnd,
                   OutputIterator destBeg,
                   UnaryFunc op)
       • Calls
            op(elem)
         for each element in the source range [sourceBeg,sourceEnd) and writes each result of op to the
         destination range starting with destBeg
       • sourceBeg and destBeg may be identical. Thus, as with for_each(), you can use this algorithm
         to modify elements inside a sequence. for_each()也能实现这种功能，只不过需要在op里面按引用传入elem参数
       • To replace elements matching a criterion with a particular value, use the replace() algorithms
     */
    vector<int> coll1;
    helper::INSERT_ELEMENTS(coll1, 1, 9);
    helper::PRINT_ELEMENT(coll1, "coll1: ");

    list<int> coll2;
    transform(coll1.cbegin(), coll1.cend(),
              coll1.begin(),
              negate<int>());
    helper::PRINT_ELEMENT(coll1, "negate coll1: ");

    transform(coll1.cbegin(), coll1.cend(),
              back_inserter(coll2),
              bind(multiplies<int>(), std::placeholders::_1, 10));
    helper::PRINT_ELEMENT(coll2, "coll2: ");

    transform(coll2.crbegin(), coll2.crend(),
              ostream_iterator<int>(cout, " "),
              negate<int>());
    cout << endl;

    /*
     * -- combining elements of 2 sequences --
        OutputIterator
        transform (InputIterator1 source1Beg, InputIterator1 source1End,
                   InputIterator2 source2Beg,
                   OutputIterator destBeg,
                   BinaryFunc op)
       • Calls
            op(source1Elem,source2Elem)
         for all corresponding elements from the first source range [source1Beg,source1End) and the sec-
         ond source range starting with source2Beg and writes each result to the destination range starting
         with destBeg
         区别就在于这里的source有两个队列，然后op是一个binaryFunc，类似于 elem1 + elem2 .. 然后结果输出给 dest 队列等等
       • source1Beg, source2Beg, and destBeg may be identical. Thus, you can process the results of
         elements that are combined with themselves, and you can overwrite the elements of a source
         with the results.
     */

    transform(coll1.cbegin(), coll1.cend(),
              coll1.cbegin(),
              coll1.begin(),
              multiplies<int>()); // coll1 square
    helper::PRINT_ELEMENT(coll1, "square of coll1: ");
}

void swap_range_demo()
{
    /*
     * ForwardIterator2
       swap_ranges (ForwardIterator1 beg1, ForwardIterator1 end1,
                    ForwardIterator2 beg2)

     1. Swaps the elements in the range [beg1,end1) with the corresponding elements starting with beg2.
     2. The caller must ensure that the second range is big enough.
     3. Both ranges must not overlap.
     4. To swap all elements of a container of the same type, use its swap() member function because
        the member function usually has constant complexity
     */
    vector<int> coll1;
    deque<int> coll2;
    helper::INSERT_ELEMENTS(coll1, 1, 9);
    helper::INSERT_ELEMENTS(coll2, 10, 23);
    helper::PRINT_ELEMENT(coll1, "coll1: ");
    helper::PRINT_ELEMENT(coll2, "coll2: ");

    swap_ranges(coll1.begin(), coll1.end(),
                coll2.begin());
    helper::PRINT_ELEMENT(coll1, "coll1 swapped: ");
    helper::PRINT_ELEMENT(coll2, "coll2 swapped: ");

    //同队列内互换元素也是可以的, 但是range不能overlap
    swap_ranges(coll2.begin(), coll2.begin() + 3,
                coll2.rbegin());
    helper::PRINT_ELEMENT(coll2, "coll2 swapped internal: ");
}

void assign_new_values_demo()
{
    /*
     *  void
        fill (ForwardIterator beg, ForwardIterator end,
              const T& newValue)

        void
        fill_n (OutputIterator beg, Size num,
                const T& newValue)

        • fill() assigns newValue to each element in the range [beg,end).
        • fill_n() assigns newValue to the first num elements in the range starting with beg. If num is
          negative, fill_n() does nothing (specified only since C++11).
        • The caller must ensure that the destination range is big enough or that insert iterators are used.
        • Since C++11, fill_n() returns the position after the last modified element (beg+num) or beg if
          num is negative (before C++11, fill_n() had return type void).
     */
    fill_n(ostream_iterator<double>(cout, " "),
           10,
           8.8);
    cout << endl;

    list<string> coll;
    fill_n(back_inserter(coll),
           9,
           "Hello");
    helper::PRINT_ELEMENT(coll, "coll: ");

    fill(coll.begin(), coll.end(), "hi ");
    helper::PRINT_ELEMENT(coll, "coll: ");

    /*
     * Assigning Generated Values
     *  void
        generate (ForwardIterator beg, ForwardIterator end,
                  Func op)

        void
        generate_n (OutputIterator beg, Size num,
                    Func op)

        • generate() assigns the values that are generated by a call of
            op()
          to each element in the range [beg,end).
        • generate_n() assigns the values that are generated by a call of
            op()
          to the first num elements in the range starting with beg. If num is negative, generate_n() does
          nothing (specified only since C++11).
     */
    list<int> randoms;
    generate_n(back_inserter(randoms),
               10,
               rand);
    helper::PRINT_ELEMENT(randoms, "int randoms: ");

    int n = 0;
    generate(randoms.begin(), randoms.end(), [n] () mutable -> int {
        return ++n;
    });
    helper::PRINT_ELEMENT(randoms, "++n: ");

    /*
     * -- Assigning Sequence of Increments Values --
     *  void
        iota (ForwardIterator beg, ForwardIterator end,
              T startValue)

        • assigns startValue, startValue+1, startValue+2, and so on.
        • Provided since C++11.
     */
    array<int, 10> arr;
    iota(arr.begin(), arr.end(), 42);
    helper::PRINT_ELEMENT(arr,"arr: ");
}

void replace_demo()
{
    /*
     *  void
        replace (ForwardIterator beg, ForwardIterator end,
                 const T& oldValue, const T& newValue)

        void
        replace_if (ForwardIterator beg, ForwardIterator end,
                    UnaryPredicate op, const T& newValue)

        • replace() replaces each element in the range [beg,end) that is equal to oldValue with newValue.
        • replace_if() replaces each element in the range [beg,end) for which the unary predicate
            op(elem)
          yields true with newValue.
     */
    list<int> coll;
    helper::INSERT_ELEMENTS(coll, 1, 7);
    helper::INSERT_ELEMENTS(coll, 3, 9);
    helper::PRINT_ELEMENT(coll, "coll: ");

    replace(coll.begin(), coll.end(),
            6,
            42);
    helper::PRINT_ELEMENT(coll, "coll replace 6 with 42: ");

    replace_if(coll.begin(), coll.end(),
               [] (int elem) -> bool {
                   return elem < 5;
               },
               0);
    helper::PRINT_ELEMENT(coll, "coll replace_if: ");

    /*
     *  OutputIterator
        replace_copy (InputIterator sourceBeg, InputIterator sourceEnd,
                      OutputIterator destBeg,
                      const T& oldValue, const T& newValue)

        OutputIterator
        replace_copy_if (InputIterator sourceBeg, InputIterator sourceEnd,
                         OutputIterator destBeg,
                         UnaryPredicate op, const T& newValue)
     */
}

void Run()
{
    /*
     *  This section describes algorithms that modify the elements of a range. There are two ways to modify
        elements:
        1. Modify them directly while iterating through a sequence.
        2. Modify them while copying them from a source range to a destination range.
        Several modifying algorithms provide both ways of modifying the elements of a range. In this case,
        the name of the latter uses the _copy suffix.

        You can’t use an associative or unordered container as a destination range, because the elements
        in these containers are constant. If you could, it would be possible to compromise the automatic
        sorting or the hash based position, respectively.

        All algorithms that have a separate destination range return the position after the last copied
        element of that range.
     */
    copy_demo();
    move_demo();
    transform_and_combine_demo();
    swap_range_demo();
    assign_new_values_demo();
    replace_demo();
}

}
}