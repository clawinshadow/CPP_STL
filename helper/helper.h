//
// Created by fhuang on 2020/2/29.
//

#ifndef STL_DEMO_HELPER_H
#define STL_DEMO_HELPER_H

#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>
#include <iostream>
#include <string>

namespace helper {

template<typename T>
inline void PRINT_ELEMENT(const T &coll, const std::string &optStr = "") {
    std::cout << optStr;
    for (const auto &elem: coll)
        std::cout << elem << ' ';
    std::cout << std::endl;
}

// INSERT_ELEMENTS (collection, first, last)
// - fill values from first to last into the collection
// - NOTE: NO half-open range
template <typename T>
inline void INSERT_ELEMENTS(T& coll, int first, int last)
{
    for (int i = first ; i <= last; ++i) {
        coll.insert(coll.end(), i);
    }
}

// PRINT_MAPPED_ELEMENTS()
// - prints optional string optcstr followed by
// - all elements of the key/value collection coll
// - separated by spaces
template <typename T>
inline void PRINT_MAPPED_ELEMENTS (const T& coll,
                                   const std::string& optcstr="")
{
    std::cout << optcstr;
    for (auto elem : coll) {
        std::cout << '[' << elem.first
                << ',' << elem.second << "] ";
    }
    std::cout << std::endl;
}

}

#endif //STL_DEMO_HELPER_H
