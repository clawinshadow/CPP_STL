#include "auxiliary_functions.h"

#include <utility>
#include <iostream>
#include <algorithm>

namespace utility {
namespace auxiliary_funcs {

void minmax_demo()
{
    // std::min() 有以下四种形式
    // 1. min(a, b): returns the minimum of a and b, comparing with < 
    // 2. min(a, b, cmp): returns the minimum of a and b, comparing with cmp
    // 3. min(initlist): returns the minimum in a initializer list, comparing with <
    // 4. min(initlist, cmp): returns... comparing with cmp
    // std::max(), std::minmax() 都有相同的这四种形式
    std::cout << std::min(3, 4) << std::endl;
    std::cout << std::min({2, 3, 4}) << std::endl;

    // minmax() returns a Pair
    std::pair<double, double> extremes = std::minmax({1.0, -2.3, 5.1, 7.9, 6.0});
    printf("extremes: [%f, %f]\n", extremes.first, extremes.second);

}

}
}