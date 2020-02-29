//  - Containers 是数据怎么存放在容器里，Algorithms是如何实现各种算法，Iterators相当于两者之间的桥梁，
//               如何访问容器内的元素
//     1. Sequence containers: ordered collections in which every element has a certain position. 
//          This position depends on the time and place of the insertion. STL 包含5个预定义好的sequance
//          containers: array, vector, deque, list, forward_list
//             -- 一般都是用array或者linked list来实现的
//     2. Associative containers: sorted collections in which the position of an element depends on its value
//          due to a certain sorting criterion. STL包含4个预定义的 associative containers: 
//          set, map, multiset, multimap
//             -- 一般都是用binary tree来实现的
//     3. Unordered containers: unordered collections in which the position of an element doesn't matter
//          唯一需要关心的只是这个容器里是否存在这个元素，它的位置在哪里无关紧要。
//          STL provides: unordered_set, unordered_multiset, unordered_map, and unordered_multimap
//             -- 一般都是用hash tables来实现的
#include "containers.h"

#include <iostream>
#include <vector>
#include <deque>
#include <array>
#include <list>
#include <forward_list>

#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

#include <exception>

using namespace std;

namespace stl_basics {
namespace containers {

void SequenceContainersDemo()
{
    //vector在队尾插入或者删除元素都是很快的，在队伍中间就相对比较慢，因为要移动后面的所有元素
    vector<int> coll;
    
    // append elements with values 1 to 6 
    for (int i = 1; i <= 6; ++i) {
        coll.push_back(i);
    }
    // print all elements followed by a space
    for (int i=0; i<coll.size(); ++i) {
        cout << coll[i] << " ";
    }

    cout << endl;

    // deque 是"double-ended queue"的缩写，双向队列
    // 在队列头部和尾部插入元素都很快，O(1), 所以提供了 push_front() 的方法
    // 其实vector也可以提供push_front()的方法，但因为特别影响性能，所以就没提供
    // 对整个STL来说都是这样，STL只提供性能较好的方法，以免用户不恰当的使用性能不好的方法
    deque<float> coll2;
    for (int i = 1; i <= 6; i++)
        coll2.push_front(i * 1.1);

    for (auto element: coll2)
        cout << element << " ";  // reverse-order, 6.6, 5.5, ... 1.1

    cout << endl;

    // array 最大的特点就是长度在创建的时候就固定死了，后期不能再修改数组长度
    // Note that the number of elements is a part of the type of an array. Thus, array<int,5> and
    // array<int,10> are two different types, and you can’t assign or compare them as a whole.
    array<string, 5> coll3 = {"Huang", "Fan"};
    for (auto element: coll3)
        cout << element << std::endl;

    // list 双向链表，既然是链表了，那么他们的元素就不是存储在连续的内存块里面了
    // 每个元素都有predecessor 和 successor，在任意地方插入或者删除操作都是O(1),
    // 但是不支持随机访问，比如我们想访问第十个元素，那么需要先遍历它前面的九个，那么元素访问是O(N)
    // methods: push_back(), push_front(), pop_back(), pop_front()等等
    //          但不支持[]操作符
    list<char> coll4;
    for (char c = 'a'; c <= 'z'; ++c) {
        coll4.push_back(c);
    }
    for (auto elem : coll4) {
        cout << elem << ' ';
    }
    cout << endl;

    // forward_list, 单向链表，为了节约内存，每个元素只指向其后面的元素
    // 所以push_back()和 size()都不提供了，resize()方法的开销很大 O(N)
    // create forward-list container for some prime numbers
    forward_list<long> coll5 = { 2, 3, 5, 7, 11, 13, 17 };

    // - note: poor performance
    coll5.resize(9); //多出来的空间，默认填充0
    coll5.resize(10, 99); // 第二个参数指定了要填充的值
    // print all elements:
    for (auto elem : coll5) {
        cout << elem << ' ';
    }
    cout << endl;
}

/*
 *  Associative containers are typically implemented as binary trees. Thus, every element (every
    node) has one parent and two children. All ancestors to the left have lesser values; all ancestors to
    the right have greater values. The associative containers differ in the kinds of elements they support
    and how they handle duplicates.
    The major advantage of associative containers is that finding an element with a specific value
    is rather fast because it has logarithmic complexity (in all sequence containers, you have linear
    complexity)
    multiset 相比 set 最大的不同就是value允许重复
    multimap 相比 map 最大的不同就是key允许重复
 */
void AssociateContainersDemo()
{
    multiset<string> cities {
            "Braunschweig", "Hanover", "Frankfurt", "New York",
            "Chicago", "Toronto", "Paris", "Frankfurt"
    };
    for (const auto& elem : cities) {
        cout << elem << " ";
    }
    cout << endl;

    // insert additional values:
    cities.insert( {"London", "Munich", "Hanover", "Braunschweig"} );
    for (const auto& elem : cities) {
        cout << elem << " ";
    }
    cout << endl;

    multimap<int,string> coll;
    // container for int/string values
    // insert some elements in arbitrary order
    // - a value with key 1 gets inserted twice
    coll = { {5,"tagged"},
             {2,"a"},
             {1,"this"},
             {4,"of"},
             {6,"strings"},
             {1,"is"},
             {3,"multimap"} };

    for (auto elem : coll) {
        cout << elem.first << ", " << elem.second << endl;
    }

}

/*
 *  Unordered containers are typically implemented as a hash table (Figure 6.3). Thus, internally,
    the container is an array of linked lists. Using a hash function, the position of an element in the array
    gets processed.
    本质上是一个链表数组，因为没有完美的hash函数能将每一个不同的key值都映射到一个不同的bucket，所以一个bucket实际上可能拥有多个元素
    那么一个bucket对应的就是一个链表.

    The major advantage of unordered containers is that finding an element with a specific value
    is even faster than for associative containers
    在查找元素这一块，这个比Associate containers还要快，这个是接近O(1)的，只用遍历链表就可以，然而一个链表不可能存在太多的元素
    而Associate containers的查找要经过二叉树，是O(logN)的

    All these unordered container classes have a couple of optional template arguments to specify a hash
    function and an equivalence criterion
 */
void UnorderedContainersDemo()
{
    unordered_multiset<string> cities {
            "Braunschweig", "Hanover", "Frankfurt", "New York",
            "Chicago", "Toronto", "Paris", "Frankfurt"
    };
    for (const auto& elem : cities) {
        cout << elem << " ";
    }
    cout << endl;

    cities.insert( {"London", "Munich", "Hanover", "Braunschweig"} );
    for (const auto& elem : cities) {
        cout << elem << " ";
    }
    cout << endl;

    /*
     *  Both maps and unordered maps are collections of key/value pairs with unique keys. Such a collection
        can also be thought of as an "associative array", an array whose index is not an integer value. As a
        consequence, both containers provide the subscript operator [ ].
        一个特别方便的地方就是使用[]前不用检查key值是否存在，[]无论如何都不会报错，不存在就插入
        Not having an element for an index is not an error. A new index (or key) is taken
        as a reason to create and insert a new map element that has the index as the key.
        Thus, you can’t have an invalid index.
     */
    unordered_map<string, float> coll;
    coll["VAT1"] = 0.16;
    coll["VAT2"] = 0.07;
    coll["Pi"] = 3.1415;
    coll["an arbitrary number"] = 4983.223;
    coll["Null"] = 0;
    // change value
    coll["VAT1"] += 0.03;
    // print difference of VAT values
    cout << "VAT difference: " << coll["VAT1"] - coll["VAT2"] << endl;

    //Since C++11, you can, alternatively, use at() to access values of elements while passing the key
    //In this case, a key not found results in an out_of_range exception:
    try {
        coll.at("VAT3") = 0.16; // out_of_range exception if no element found
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

}

/*
 *  Container Adapters: In addition to the fundamental container classes, the C++ standard library provides so-called
    container adapters, which are predefined containers that provide a restricted interface to meet special
    needs. These container adapters are implemented by using the fundamental container classes. The
    predefined container adapters are as follows:
        • A stack (the name says it all) manages its elements by the LIFO (last-in-first-out) policy.
        • A queue manages its elements by the FIFO (first-in-first-out) policy. That is, it is an ordinary
            buffer.
        • A priority queue is a container in which the elements may have different priorities. The priority
            is based on a sorting criterion that the programmer may provide (by default, operator < is used).
            A priority queue is, in effect, a buffer in which the next element is always one having the highest
            priority inside the queue. If more than one element has the highest priority, the order of these
            elements is undefined.
 */

}
}