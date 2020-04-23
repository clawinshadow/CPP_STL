#include "numerics.h"
#include "helper.h"

#include <numeric>

using namespace std;

namespace algorithms {
namespace numerics_ {

void accumulate_demo()
{
    /*
     *  T
        accumulate (InputIterator beg, InputIterator end,
                    T initValue)
        T
        accumulate (InputIterator beg, InputIterator end,
                    T initValue, BinaryFunc op)
        • The first form computes and returns the sum of initValue and all elements in the range [beg,end).
          In particular, it calls the following for each element:
            initValue = initValue + elem
        • The second form computes and returns the result of calling op for initValue and all elements in
          the range [beg,end). In particular, it calls the following for each element:
            initValue = op(initValue,elem)
        • Thus, for the values
            a1 a2 a3 a4 ...
          they compute and return either
            initValue + a1 + a2 + a3 + ...
          or
            initValue op a1 op a2 op a3 op ...
          respectively.
     */
    vector<int> coll;
    helper::INSERT_ELEMENTS(coll, 1, 9);
    helper::PRINT_ELEMENT(coll, "coll: ");

    cout << accumulate(coll.cbegin(), coll.cend(), 0) << endl;    // 1+2+3+...+9
    cout << accumulate(coll.cbegin(), coll.cend(), -100) <<  endl; // -100 + (1 + 2 + 3 + .. + 9)
    cout << accumulate(coll.cbegin(), coll.cend(), 1, multiplies<int>()) << endl; // 1 * (9!)
    cout << accumulate(coll.cbegin(), coll.cend(), 0, multiplies<int>()) << endl; // 0 * 9!
}

void inner_product_demo()
{
    /*
     *  T
        inner_product (InputIterator1 beg1, InputIterator1 end1,
                       InputIterator2 beg2, T initValue)
        T
        inner_product (InputIterator1 beg1, InputIterator1 end1,
                       InputIterator2 beg2, T initValue,
                       BinaryFunc op1, BinaryFunc op2)
        • The first form computes and returns the inner product of initValue and all elements in the range
          [beg,end) combined with the elements in the range starting with beg2. In particular, it calls the
          following for all corresponding elements:
            initValue = initValue + elem1 * elem2
        • The second form computes and returns the result of calling op for initValue and all elements in
          the range [beg,end) combined with the elements in the range starting with beg2. In particular, it
          calls the following for all corresponding elements:
            initValue = op1(initValue,op2(elem1,elem2))
        • Thus, for the values
            a1 a2 a3 ...
            b1 b2 b3 ...
          they compute and return either
            initValue + (a1 * b1) + (a2 * b2) + (a3 * b3) + ...
          or
            initValue op1 (a1 op2 b1) op1 (a2 op2 b2) op1 (a3 op2 b3) op1 ...
          respectively.
     */
    list<int> coll;
    helper::INSERT_ELEMENTS(coll, 1, 6);
    helper::PRINT_ELEMENT(coll, "coll: ");

    // (0 + 1*1 + 2*2 + 3*3 + 4*4 + 5*5 + 6*6)
    int square = inner_product(coll.cbegin(), coll.cend(),
                               coll.cbegin(),
                               0);
    cout << "self inner product: " << square << endl;

    // (0 + 1*6 + 2*5 + 3*4 + 4*3 + 5*2 + 6*1)
    int reverse_product = inner_product(coll.cbegin(), coll.cend(),
                                        coll.crbegin(),
                                        0);
    cout << "self reverse product: " << reverse_product << endl;

    // [1 * (1 + 1) * (2 + 2) * (3 + 3) * ... * (6 + 6)]
    int product = inner_product(coll.cbegin(), coll.cend(),
                                coll.cbegin(),
                                1,
                                multiplies<int>(),
                                plus<int>());
    cout << "product: " << product << endl;
}

void partial_sum_demo()
{
    /*
     *  OutputIterator
        partial_sum (InputIterator sourceBeg, InputIterator sourceEnd,
                     OutputIterator destBeg)
        OutputIterator
        partial_sum (InputIterator sourceBeg, InputIterator sourceEnd,
                     OutputIterator destBeg, BinaryFunc op)

        • The first form computes the partial sum for each element in the source range [sourceBeg,
          sourceEnd) and writes each result to the destination range starting with destBeg.
        • The second form calls op for each element in the source range [sourceBeg,sourceEnd) combined
          with all previous values and writes each result to the destination range starting with destBeg.
        • Thus, for the values
            a1 a2 a3 ...
          they compute either
            a1, a1 + a2, a1 + a2 + a3, ...
          or
            a1, a1 op a2, a1 op a2 op a3, ...
          respectively.
     */
    list<int> coll;
    helper::INSERT_ELEMENTS(coll, 1, 6);
    helper::PRINT_ELEMENT(coll, "coll: ");

    cout << "partial sum: ";
    // 1, 1+2, 1+2+3, 1+2+3+4, ...
    partial_sum(coll.cbegin(), coll.cend(),
                ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << "partial product: ";
    // 1, 1*2, 1*2*3, ...
    partial_sum(coll.cbegin(), coll.cend(),
                ostream_iterator<int>(cout, " "),
                multiplies<int>());
    cout << endl;
}

void adjacent_difference_demo()
{
    /*
     *  OutputIterator
        adjacent_difference (InputIterator sourceBeg, InputIterator sourceEnd,
                             OutputIterator destBeg)
        OutputIterator
        adjacent_difference (InputIterator sourceBeg, InputIterator sourceEnd,
                             OutputIterator destBeg, BinaryFunc op)

        • The first form computes the difference of each element in the range [sourceBeg,sourceEnd) with
          its predecessor and writes the result to the destination range starting with destBeg.
        • The second form calls op for each element in the range [sourceBeg,sourceEnd) with its prede-
          cessor and writes the result to the destination range starting with destBeg.
        • The first element only is copied.
        • Thus, for the values
            a1 a2 a3 a4 ...
          they compute and write either the values
            a1, a2 - a1, a3 - a2, a4 - a3, ...
          or the values
            a1, a2 op a1, a3 op a2, a4 op a3, ...
          respectively.
     */
    list<int> coll;
    helper::INSERT_ELEMENTS(coll, 1, 6);
    helper::PRINT_ELEMENT(coll, "coll: ");

    cout << "adjacent difference: ";
    adjacent_difference(coll.cbegin(), coll.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << "Add adjacent: ";
    adjacent_difference(coll.cbegin(), coll.cend(), ostream_iterator<int>(cout, " "),
            plus<int>());
    cout << endl;
}

void Run()
{
    accumulate_demo();
    inner_product_demo();
    partial_sum_demo();
    adjacent_difference_demo();
}

}
}