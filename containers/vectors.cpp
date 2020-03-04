#include "vectors.h"
#include "helper.h"

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
using namespace helper;

namespace containers {
namespace vectors {

/* Vector 本质上是一个动态数组，主要特性如下
 * 1. Ordered collection, 地址空间是连续的，支持 random-access, 即访问某个地址的元素时间是 O(1)
 * 2. 在尾部插入或者删除元素很快，但是在中间或者头部就不太好，线性复杂度
 * 3. vector的性能之所以好，是因为它一般会维持一个比实际元素更多的内存空间，只有元素个数超出了这个预先分配的空间
 *    它才会重新分配内存空间。可以用capacity()方法来查看目前该vector分配了多少内存空间，如果超出这个数就意味着
 *    要重新分配了。
 *    内存空间的重新分配不止消耗时间，还会让之前的所有iterators, pointers, references全部失效
 *    那么为了避免意外的reallocation, 我们可以通过reserve()方法预先指定分配多少内存空间，但是如果reserve()
 *    指定的内存空间小于现在的capacity(), 那么vector是不执行的，即reserve()不能收缩vector的空间
 *    C++11之后，vector提供了新的方法shrink_to_fit()来收缩vector空间，当然所有的iterators会失效
 *    同样的也可以通过在初始化时指定元素个数来分配内存空间，as below:
 *      std::vector<T> v(5); // creates a vector and initializes it with five values
 *    但是这样的话会默认初始化N个元素，如果仅仅只是想预留空间，reserve()无疑是性能最好的方法
 *
 */
void Run()
{
    //vector 的一个不常见的初始化方式
    std::vector<int> v1(5, 6); // 5个6
    PRINT_ELEMENT(v1, "v1: ");

    // ---- Assignments
    // ... 常见的
    // c.assign(n, elem)
    // c.assign(beg, end)
    // c.assign(initlist)
    std::vector<int> v2;
    v2.assign(v1.cbegin(), v1.cend());
    PRINT_ELEMENT(v2, "v2: ");

    // ---- Modifying
    // 考虑到性能，当插入或者删除vector内的元素时，要注意以下几点
    //    • Elements are inserted or removed at the end.
    //    • The capacity is large enough on entry.
    //    • Multiple elements are inserted by a single call rather than by multiple calls.

    // 没有提供删除某个具体元素的方法，但可以用算法库加上erase()成员函数来实现，如下
    std::vector<int> v3 = {1, 3, 2, 3, 4, 5, 3, 6};
    PRINT_ELEMENT(v3, "original v3： ");
    v3.erase(remove(v3.begin(), v3.end(), 3), v3.end());
    PRINT_ELEMENT(v3, "remove 3 in v3： ");

    // 只删除第一个符合条件的元素
    std::vector<int> v4 = {1, 3, 2, 3, 4, 5, 3, 6};
    auto pos = find(v4.begin(), v4.end(), 3);
    if (pos != v4.end()) {
        v4.erase(pos);
    }
    PRINT_ELEMENT(v4, "remove first 3 in v4： ");

    // ---- vectors 一样可以当做 C-Style array 来使用，使用data()即可

    // insert 支持下面几种格式
    //    c.insert(pos,elem)
    //    c.insert(pos,n,elem)
    //    c.insert(pos,beg,end)
    //    c.insert(pos,initlist)

    // create empty vector for strings
    vector<string> sentence;

    // reserve memory for five elements to avoid reallocation
    sentence.reserve(5);

    // append some elements
    sentence.push_back("Hello,");
    sentence.insert(sentence.end(),{"how", "are", "you", "?"});
    PRINT_ELEMENT(sentence, "original sentence: "); // 正好5个元素

    // print ‘‘technical data’’
    cout << " max_size(): " << sentence.max_size() << endl;
    cout << " size(): " << sentence.size() << endl;
    cout << " capacity(): " << sentence.capacity() << endl;

    // swap second and fourth element
    swap (sentence[1], sentence[3]); // swap也可以这样用

    // insert element "always" before element "?"
    sentence.insert (find(sentence.begin(), sentence.end(),"?"), "always");
    // assign "!" to the last element
    sentence.back() = "!";
    PRINT_ELEMENT(sentence, "sentence with answer: "); // 6个元素

    // print some ‘‘technical data’’ again
    cout << " size(): " << sentence.size() << endl;
    cout << " capacity(): " << sentence.capacity() << endl;  // 触发了reallocation

    // delete last two elements
    sentence.pop_back();
    sentence.pop_back();  // 此时只有4个元素了

    // shrink capacity (since C++11)
    sentence.shrink_to_fit();
    // print some ‘‘technical data’’ again
    cout << " size(): " << sentence.size() << endl;
    cout << " capacity(): " << sentence.capacity() << endl; // 空间收缩了

    VectorBoolDemo();
}

// vector<bool> 是一个特殊的vector类型，STL做了一些特殊处理
void VectorBoolDemo()
{
    // c.flip()
    // c[idx].flip()
    vector<bool> b = {true, false, true};
    std::cout << boolalpha;
    PRINT_ELEMENT(b, "vector bool : ");

    b.flip();
    PRINT_ELEMENT(b, "vector bool flipped: ");
}

}
}