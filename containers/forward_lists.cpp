#include "forward_lists.h"
#include "helper.h"

#include <forward_list>
#include <iterator>

using namespace std;
using namespace helper;

namespace containers {
namespace forward_lists {

/*
 * ---- Abilities of forward_lists
 * 它是个单向链表，功能上只是list的一个子集，但是占用更少的内存，运行时的性能要稍微好一点
 * 1. 它只提供前向的iterators, 逆向的不提供。
 *    即 rbegin(), rend(), crbegin(), crend(), reverse_iterator<>等等均不适用
 * 2. 不提供size()函数
 * 3. 不提供back(), push_back(), and pop_back()等函数，只能在链表头部操作
 * 4. 因为它的anchor都是单向的，所以我们在插入或者删除元素时，在传递pos参数的时候，通常会有一些
 *    insert_after(), before_begin()之类的方法，习惯就好
 *    "when element positions are involved, you have to pass the preceding position,
 *     and the member function has the suffix _after in its name."
 * 其余的特性基本上和list一样
 *
 * ---- Insert and Remove operations
 *  c.push_front(elem)
    c.pop_front()
    c.insert_after(pos,elem)
    c.insert_after(pos,n,elem)
    c.insert_after(pos,beg,end)
    c.insert_after(pos,initlist)
    c.emplace_after(pos,args...)
    c.emplace_front(args...)
    c.erase_after(pos)
    c.erase_after(beg,end)
    c.remove(val)
    c.remove_if(op)
    c.resize(num)
    c.resize(num,elem)
    c.clear()
 *
 */
void Run()
{
    // before_begin() 和 insert_after()的典型用法
    std::forward_list<int> fwlist = { 1, 2, 3 };
    fwlist.insert_after(fwlist.before_begin(), { 77, 88, 99 } );
    PRINT_ELEMENT(fwlist, "fwlist: ");

    // 单向链表一个很不方便的场景就是：find and insert
    // 即我们在链表中先找到一个特定的元素，然后在它的前面插入一个新的元素
    // 因为单向链表无法回溯，所以我们找到这个元素的位置了之后，很难简单的获取它之前的位置
    // 下面是一种思路
    forward_list<int> list = { 1, 2, 3, 4, 5, 97, 98, 99 };
    auto posBefore = list.before_begin();
    for (auto it = list.cbegin(); it != list.cend(); ++it, ++posBefore)
    {
        if (*it % 2 == 0)
            break;
    }
    //在遍历的时候递增posBefore来获取特定元素的前面的位置
    list.insert_after(posBefore, 42);
    PRINT_ELEMENT(list, "list: ");
    // C++11之后可以使用next()方法来代替
    //    for ( ; next(posBefore) != list.end(); ++posBefore) {
    //        if (*next(posBefore) % 2 == 0) {
    //            break; // element found
    //        }
    //    }

    // splice_after() instead of splice() in list
    //   c.splice_after(pos,c2) Moves all elements of c2 to c right behind the iterator position pos
    //   c.splice_after(pos,c2,c2pos)
    //   c.splice_after(pos,c2,c2beg,c2end)
    forward_list<int> l1 = { 1, 2, 3, 4, 5 };
    forward_list<int> l2 = { 97, 98, 99 };
    // find 3 in l1
    auto pos1 = l1.before_begin();
    for (auto pb1 = l1.begin(); pb1 != l1.end(); ++pb1, ++pos1) {
        if (*pb1 == 3) {
            break; // found
        }
    }

    l1.splice_after(pos1, l2);
    PRINT_ELEMENT(l1, "l1: ");
}

}
}