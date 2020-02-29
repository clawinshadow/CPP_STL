//
// Created by fhuang on 2020/2/29.
//

#ifndef STL_DEMO_HELPER_H
#define STL_DEMO_HELPER_H

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

}

#endif //STL_DEMO_HELPER_H
