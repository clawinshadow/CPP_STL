#include "removing.h"
#include "helper.h"

using namespace std;

namespace algorithms {
namespace removing {

void remove_certain_values()
{
    /*
     *  ForwardIterator
        remove (ForwardIterator beg, ForwardIterator end,
                const T& value)

        ForwardIterator
        remove_if (ForwardIterator beg, ForwardIterator end,
                   UnaryPredicate op)

        • remove() removes each element in the range [beg,end) that is equal to value.
        • remove_if() removes each element in the range [beg,end) for which the unary predicate
            op(elem)
          yields true.
        • Both algorithms return the logical new end of the modified sequence (the position after the last
          element not removed).
        • The algorithms overwrite “removed” elements by the following elements that were not removed.
        • The order of elements that were not removed remains stable.
        • Note that remove_if() usually copies the unary predicate inside the algorithm and uses it twice.
          This may lead to problems if the predicate changes its state due to the function call.
        • Due to modifications, you can’t use these algorithms for an associative or unordered container.
          However, these containers provide a similar member function, erase()
        • Lists provide an equivalent member function, remove(), which offers better performance be-
          cause it relinks pointers instead of assigning element values

        反正特别反常识的一点就是，这个remove并没有在物理上删除这些元素，只是逻辑上删除了
     */
    vector<int> coll;
    helper::INSERT_ELEMENTS(coll, 2, 6);
    helper::INSERT_ELEMENTS(coll, 4, 9);
    helper::INSERT_ELEMENTS(coll, 1, 7);
    helper::PRINT_ELEMENT(coll, "coll: ");

    auto pos = remove(coll.begin(), coll.end(), 5);
    helper::PRINT_ELEMENT(coll, "coll size not changed: ");

    coll.erase(pos, coll.end());
    helper::PRINT_ELEMENT(coll, "coll size changed: ");

    pos = remove_if(coll.begin(), coll.end(),
                    [] (int elem) -> bool {
                        return elem < 5;
                    });
    coll.erase(pos, coll.end());
    helper::PRINT_ELEMENT(coll, "coll remove elements less than 5: ");

    /*
     *  OutputIterator
        remove_copy (InputIterator sourceBeg, InputIterator sourceEnd,
                     OutputIterator destBeg,
                     const T& value)
        OutputIterator
        remove_copy_if (InputIterator sourceBeg, InputIterator sourceEnd,
                        OutputIterator destBeg,
                        UnaryPredicate op)
        • remove_copy() is a combination of copy() and remove(). It copies each element in the source
          range [sourceBeg,sourceEnd) that is not equal to value into the destination range starting with
          destBeg.
        • remove_copy_if() is a combination of copy() and remove_if(). It copies each element in
          the source range [sourceBeg,sourceEnd) for which the unary predicate
            op(elem)
          yields false into the destination range starting with destBeg.
     */
}

void remove_duplicates()
{
    /*
     *  ForwardIterator
        unique (ForwardIterator beg, ForwardIterator end)

        ForwardIterator
        unique (ForwardIterator beg, ForwardIterator end,
                BinaryPredicate op)

     *  • Both forms collapse consecutive equal elements by removing the following duplicates.
        • The first form removes from the range [beg,end) all elements that are equal to the previous
          elements. Thus, only when the elements in the sequence are sorted, or at least when all elements
          of the same value are adjacent, does it remove all duplicates.
        • The second form removes all elements that follow an element e and for which the binary predicate
            op(e,elem)
          yields true. In other words, the predicate is not used to compare an element with its predecessor;
          the element is compared with the previous element that was not removed
        • Both forms return the logical new end of the modified sequence (the position after the last element
          not removed).
     */
    list<int> coll = { 1, 4, 4, 6, 1, 2, 2, 3, 1, 6, 6, 6, 5, 7,
                       5, 4, 4 };
    helper::PRINT_ELEMENT(coll, "coll: ");

    auto pos = unique(coll.begin(), coll.end());
    cout << "coll unique: ";
    copy(coll.begin(), pos, ostream_iterator<int>(cout, " "));
    cout << endl;

    list<int> coll2 = { 1, 4, 4, 6, 1, 2, 2, 3, 1, 6, 6, 6, 5, 7,
                        5, 4, 4 };
    // remove elements if there was a previous greater element
    // 要注意的是：比如循环到2的时候，并不是将2与前面的1来比较，因为此时1已经被删掉了
    //           它要比较的是前面的存活着的最后一个元素: 6
    auto pos2 = unique(coll2.begin(), coll2.end(),
                      [] (int elem1, int elem2) -> bool {
                          return elem2 < elem1;
                      });
    coll2.erase(pos2, coll2.end());
    helper::PRINT_ELEMENT(coll2, "coll2 unique: ");
}

void Run()
{
    /*
     * The following algorithms remove elements from a range according to their value or to a criterion.
       These algorithms, however, cannot change the number of elements.
       The algorithms move logically only by overwriting “removed” elements with the following elements that were not removed.
       They return the new logical end of the range (the position after the last element not removed)
     */
    remove_certain_values();
    remove_duplicates();
}

}
}