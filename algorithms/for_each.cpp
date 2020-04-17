#include "for_each.h"
#include "helper.h"

#include <vector>
#include <algorithm>

using namespace std;

namespace algorithms {
namespace for_each_ {

/*
 *  The for_each() algorithm is very flexible because it allows you to access, process, and modify
    each element in many different ways. Note, however, that since C++11, the range-based for loop
    provides this behavior more conveniently and more naturally.
    Thus, for_each() might lose its importance over time.

    UnaryProc
    for_each (InputIterator beg, InputIterator end, UnaryProc op)
    • Calls
        op(elem)
      for each element in the range [beg,end).
    • Returns the (internally modified) copy of op. Since C++11, the returned op is moved.
    • op might modify the elements. However, see Section 11.2.2, page 509, for a comparison with
      the transform() algorithm, which is able to do the same thing in a slightly different way.
    • Any return value of op is ignored.
    • Complexity: linear (numElems calls of op())
 */

void print(int elem)
{
    cout << elem << ' ';
}

void vanilla_for_each()
{
    vector<int> coll;
    helper::INSERT_ELEMENTS(coll,1,9);

    for_each (coll.cbegin(), coll.cend(),
              [](int elem){
                  cout << elem << ' ';
              });
    cout << endl;

    // for_each 接受 ordinary function, 不一定非得包装为 function object
    for_each (coll.begin(), coll.end(), print);
    cout << endl;
}

void modify_for_each()
{
    vector<int> coll;
    helper::INSERT_ELEMENTS(coll,1,9);

    // add 10 to each element
    for_each (coll.begin(), coll.end(),
              [](int& elem){
                  elem += 10;
              });
    helper::PRINT_ELEMENT(coll);

    // add value of first element to each element
    for_each (coll.begin(), coll.end(),
              [=](int& elem){
                  elem += *coll.begin();
              });
    helper::PRINT_ELEMENT(coll, "copy the first element: ");

    // 要注意lambdas表达式中, captures 里面是 = 还是 & 是完全不一样的结果
    // 上面的是 = 号，所以第一个元素一直都会是11，每个元素加的都是11
    // 下面的例子中是 & 符号，所以只有第一个元素第一次被使用的时候是22， 然后自己变为了44，
    // 此后每一次被+的时候，都是44
    for_each (coll.begin(), coll.end(),
              [&] (int& elem) {
                  elem += *coll.begin();
              });
    helper::PRINT_ELEMENT(coll, "reference the first element: ");
}

void Run()
{
    vanilla_for_each();
    modify_for_each();

    // 接受 function object 为参数的例子参见上一章节的demo
}

}
}