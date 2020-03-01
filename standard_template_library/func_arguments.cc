#include "func_arguments.h"
#include "helper.h"

#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <iterator>
#include <cstdlib> //for abs()
#include <iostream>

using namespace std;
using namespace helper;

namespace stl_basics {
namespace func_arguments {

//function that prints the passed argument
void print_elem(int elem)
{
    cout << elem << ' ';
}

// for std::transform()
int square (int value)
{
    return value*value;
}

// 普通的应用场景
void Demo()
{
    vector<int> coll;
    for (int i = 1; i <= 9; ++i) {
        coll.push_back(i);
    }

    for_each(coll.cbegin(), coll.cend(), print_elem);
    cout << endl;

    deque<int> coll2;
    std::transform(coll.cbegin(), coll.cend(),
                   back_inserter(coll2),
                   square);
    PRINT_ELEMENT(coll2, "sqaured:  ");
    cout << endl;
}

// 返回bool类型的function作为参数传递时叫做predicate
// 根据参数的个数不同，分为一元和二元的

// Unary Predicate 
// predicate, which returns whether an integer is a prime number
bool IsPrime (int number)
{
    // ignore negative sign
    number = abs(number);
    
    // 0 and 1 are no prime numbers
    if (number == 0 || number == 1) {
        return false;
    }

    int divisor;
    for (divisor = number / 2; number % divisor != 0; --divisor) 
    { ; }

    return divisor == 1;
}

void PredicatesDemo()
{
    list<int> coll;
    for (int i = 24; i <= 30; ++i) {
        coll.push_back(i);
    }
    
    // search for prime number
    auto pos = find_if (coll.cbegin(), coll.cend(), IsPrime);
    if (pos != coll.end()) {
        cout << *pos << " is the first prime number found" << endl; }
    else {
        cout << "no prime number found" << endl;
    }

    // binary predicates 多见于各种排序的criterion
}

}
}