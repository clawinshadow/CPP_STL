#include "demos.h"
#include "for_each.h"
#include "non_modifying.h"

#include <iostream>

namespace algorithms {

/*
 * Algorithms - Overview
 * All STL algorithms process one or more iterator ranges.
 *   - The first range is usually specified by its beginning and its end.
 *   - For additional ranges, you generally need to pass only the beginning
 *     because the end follows from the number of elements of the first range.
 * The caller must ensure that the ranges are valid.
 *   - That is, the beginning must refer to a previous or the same element of the same container as the end.
 *   - Additional ranges must have enough elements.
 *
 * Algorithms work in overwrite mode rather than in insert mode.
 * Thus, the caller must ensure that destination ranges have enough elements.
 * You can use special insert iterators to switch from overwrite to insert mode.
 *
 * Classification of algorithms
 *  • Nonmodifying algorithms
    • Modifying algorithms
    • Removing algorithms
    • Mutating algorithms
    • Sorting algorithms
    • Sorted-range algorithms
    • Numeric algorithms
   一些命名上的规则：
   1. _if suffix:   the version without the suffix is used for values, and the version with the _if suffix is used for
                    functions and function objects. For example, find() searches for an element that has a certain
                    value, whereas find_if() searches for an element that meets the criterion passed as a function,
                    a function object, or a lambda.
   2. _copy suffix: elements are not only manipulated but also copied into a destination range.
                    For example, reverse() reverses the order of elements inside a range,
                    whereas reverse_copy() copies the elements into another range in reverse order.
 */
void Demos()
{
    std::cout << "Algorithms Demos .. " << std::endl;

    //for_each_::Run();
    non_modifying::Run();
}

}