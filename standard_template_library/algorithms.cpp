/*
 * Algorithms are not member functions of the container classes but instead are global functions
   that operate with iterators.
   不是每个容器都实现自己的算法，而是算法支持每个容器的迭代器来使用，算法是全局的方法，甚至可以支持user-defined containers
   Note that this is not an object-oriented programming paradigm, it is a generic functional programming paradigm
 */

#include "algorithms.h"
#include "helper.h"

#include <set>
#include <list>
#include <deque>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

namespace stl_basics {
namespace algorithms {

void Demo()
{
    vector<int> coll = { 2, 5, 4, 1, 6, 3 };
    // 返回的值也是一个迭代器类型，指向某一个位置
    auto minpos = min_element(coll.cbegin(), coll.cend());
    cout << "min: " << *minpos << endl;
    auto maxpos = max_element(coll.cbegin(), coll.cend());
    cout << "max: " << *maxpos << endl;

    // sort all elements, 此处不能使用cbeing()和cend()，因为sort会改变迭代器的值
    sort (coll.begin(), coll.end());

    // find the first element with value 3
    auto pos3 = find (coll.begin(), coll.end(), 3);

    // reverse the order of the found element with value 3 and all following elements
    reverse(pos3, coll.end());

    // print all elements
    for (auto elem : coll) {
        cout << elem << ' ';
    }
    cout << endl;
}

void RangeDemo()
{
    /*
     * All algorithms process one or more ranges of elements, 一般用两个参数来分别指定range的开始和结尾
     * This interface is flexible but dangerous.
     * The caller must ensure that the first and second arguments define a valid range
     * 调用方必须保证这两个开始和结束的参数是来自同一个容器，并且开始的位置一定在结束的位置之前等等
     * Every algorithm processes half-open ranges. [begin,end)
     */
    list<int> coll;
    for (int i = 20; i <= 40; ++i) {
        coll.push_back(i);
    }
    auto pos25 = find (coll.begin(), coll.end(),// range
                   25);                     // value
    auto pos35 = find (coll.begin(), coll.end(),// range
                   35);                     // value
    cout << "max: " << *max_element (pos25, pos35) << endl;

    /*
     * Multiple ranges
     * Several algorithms process more than one range. In this case, you usually must define both the
       beginning and the end only for the first range. For all other ranges, you need to pass only their beginnings.
       The ends of the other ranges follow from the number of elements in the first range
       指定第一个range的首尾，其余的ranges只用指定开始的位置即可
       所以特别要 注意的一点就是： When you call algorithms for multiple ranges,
       make sure that the second and additional ranges have at least as many elements as the first range.
     */
    list<int> coll1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    vector<int> coll2;
    // RUNTIME ERROR:
    // - overwrites nonexisting elements in the destination
//    copy (coll1.cbegin(), coll1.cend(), // source
//          coll2.begin());               // destination

    // resize destination to have enough room for the overwriting algorithm
    coll2.resize (coll1.size());
    // will be ok
    copy (coll1.cbegin(), coll1.cend(), // source
          coll2.begin());               // destination
    cout << coll2[3] << endl;

    deque<int> coll3(coll1.size());
    copy (coll1.cbegin(), coll1.cend(),
          coll3.begin());
    for (auto &ele3: coll3)
        cout << ele3 << " ";
    cout << endl;
}

/*
 * 算法库中并不是每一个方法都是straightforward的，也不一定是性能最好的
 * 因为算法库基于模板的编程方式决定了它的局限性，它将数据结构和算法分离开了，实现了很好的灵活性
 * 但同样的，它只能实现一种最广义上的算法，支持所有容器类型的通用算法，所以有些功能它可能做的不那么彻底
 * 同时，也无法利用某一种容器的先天优势去更深入的优化性能
 */
void RemovingDemo()
{
    list<int> coll;
    // insert elements from 6 to 1 and 1 to 6
    for (int i=1; i<=6; ++i) {
        coll.push_front(i);
        coll.push_back(i);
    }

    // print all elements of the collection
    cout << "pre: ";
    copy (coll.cbegin(), coll.cend(),
          ostream_iterator<int>(cout," "));
    cout << endl;

    // remove all elements with value 3
    remove(coll.begin(), coll.end(), 3);

    // print all elements of the collection
    cout << "post: ";
    copy (coll.cbegin(), coll.cend(),
          ostream_iterator<int>(cout," "));
    cout << endl;

    /*
     * 可以看到在上面的例子中，remove不是物理上删除了容器中值为3的元素，而只是把后面的iterator逐个往前移位
     * 在依据iterator进行遍历的时候，容器中的元素数量实际上并未改变
     * 如果需要物理上删除值为3的元素，我们需要调用list的成员函数erase()
     * 这就是一部分algorithm的局限性，有些功能它为了顾及到通用性和灵活性，就会损失一部分功能的完备性
     * 另外性能上也有损失，我们知道list是一个双向链表，它删除某个元素的操作是非常高效的，O(1)
     * 但如果使用algorithm中的remove()方法进行操作，因为后面的元素要依次进行移动，复杂度变为O(N)
     *
     * 另外，在 associative containers 和 unordered container 中，类似于
     * remove elements and those that reorder or modify elements 这类 manipulation algorithms还不能用
     * 因为会破坏它原有的排好序的结果，或者hash table
     * 这时候只能使用容器各自的成员函数比如erase()
     * 多数情况下，容器本身提供的成员函数要比通用的算法库更高效
     */
    coll.clear();
    for (int i=1; i<=6; ++i) {
        coll.push_front(i);
        coll.push_back(i);
    }

    //先保存一下remove后的logical end iterator指向的位置
    list<int>::iterator end = remove(coll.begin(), coll.end(), 3);

    cout << "number of removed elements: " << distance(end, coll.end()) << endl;
    coll.erase(end, coll.end());  //删除尾部的冗余元素
    copy(coll.cbegin(), coll.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;

    // -----------associate container 中的删除----------
    set<int> coll2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    copy (coll2.cbegin(), coll2.cend(),
          ostream_iterator<int>(cout," "));
    cout << endl;

    // Remove all elements with value 3
    // - algorithm remove() does not work
    // - instead member function erase() works
    int num = coll2.erase(3);

    cout << "number of removed elements: " << num << endl;
    copy (coll2.cbegin(), coll2.cend(),
          ostream_iterator<int>(cout," "));
    cout << endl;

}

}
}