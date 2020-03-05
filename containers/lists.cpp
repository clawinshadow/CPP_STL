#include "lists.h"
#include "helper.h"

#include <iostream>
#include <list>
#include <algorithm>

using namespace std;
using namespace helper;

namespace containers {
namespace lists {

/*
 * ---- Abilities of Lists 双向链表
 * 1. A list does not provide random access
 *    只能从头部或者尾部开始遍历整个链表，访问具体某个位置的元素比较慢，O(N)
 *    故而不提供类似[]操作符或者at()等成员函数
 *    算法库里面需要容器提供random-access的函数也都不能用，典型的比如排序
 *    list有自己独特的sort()成员函数
 * 2. Inserting and removing elements is fast at each position , and not only at one or both ends.
 *    所以list提供自己独特的 remove() & remove_if() 函数，不要使用算法库里面的版本
 * 3. Inserting and deleting elements does not invalidate pointers, references, and iterators to other elements
 * 4. A list supports exception handling in such a way that almost every operation succeeds or is a no-op.
 *    Lists have the best support of exception safety of the standard containers in the STL.
 *    Almost all list operations will either succeed or have no effect.
 * 5. Lists don’t provide operations for capacity or reallocation
 *
 * ---- Insert and Remove Operations of Lists
 *  c.push_back(elem)
    c.pop_back()
    c.push_front(elem)
    c.pop_front()
    c.insert(pos, elem)
    c.insert(pos, n, elem)
    c.insert(pos, beg, end)
    c.insert(pos, initlist)
    c.emplace(pos, args...)
    c.emplace_back(args...)
    c.emplace_front(args...)
    c.erase(pos)       Removes the element at iterator position pos and returns the position of the next element
    c.erase(beg, end)  Removes all elements of the range [beg,end) and returns the position of the next element
    c.remove(val)      Removes all elements with value val
    c.remove_if(op)    Removes all elements for which op(elem) yields true
    c.resize(num)
    c.resize(num, elem)
    c.clear()
    要注意的就是 erase() 和 remove()的区别

 * ---- Special Modifying Operations for Lists
 *  c.unique()    //Removes duplicates of consecutive elements with the same value
    c.unique(op)
    c.splice(pos,c2)       将c2的所有元素插入到c的pos位置之前
    c.splice(pos,c2,c2pos) 将c2在c2pos位置的单个元素插入到c的pos位置之前
    c.splice(pos,c2, c2beg,c2end) 将c2的这个range中所有元素插入到c的pos位置之前
    c.sort()
    c.sort(op)
    c.merge(c2)            假设c和c2都是排好序的，将c2 merge到c里面去了之后c依然是排好序的
    c.merge(c2, op)
    c.reverse()
 */
void Run()
{
    list<int> coll1;
    coll1.insert(coll1.begin(), 3);
    coll1.insert(coll1.end(), { 1, 2});
    PRINT_ELEMENT(coll1, "coll1: ");

    coll1.emplace_back(5);
    coll1.emplace_front(4);
    PRINT_ELEMENT(coll1, "coll1: ");

    coll1.insert(coll1.end(), 5, 6);
    PRINT_ELEMENT(coll1, "coll1: ");

    coll1.erase(find(coll1.begin(), coll1.end(), 5)); //remove 1
    PRINT_ELEMENT(coll1, "coll1: ");

    coll1.remove(6); //remove all elements equal to 6
    PRINT_ELEMENT(coll1, "coll1: ");

    coll1.remove_if([=] (int i) { return i < 3; }); //remove the elements less than 3
    PRINT_ELEMENT(coll1, "coll1: ");

    list<int> coll2 = {2, 2, 6, 7, 6};
    coll1.splice(coll1.begin(), coll2);
    PRINT_ELEMENT(coll1, "coll1: ");

    coll1.unique();
    //注意unique()方法只去掉连续的重复值，比如 6 7 6 这两个6因为是不连续的，所以并没有去除其中一个
    PRINT_ELEMENT(coll1, "coll1: ");

    coll1.sort();
    PRINT_ELEMENT(coll1, "sorted coll1: ");

    list<int> coll3 = {1, 8, 9};
    coll1.merge(coll3);
    PRINT_ELEMENT(coll1, "merged coll1: ");
    //注意merge之后coll3被清空了
    PRINT_ELEMENT(coll3, "coll3: ");
}

}
}