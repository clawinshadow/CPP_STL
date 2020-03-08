#include "sets.h"
#include "helper.h"

#include <set>
#include <iostream>
#include <iterator>

using namespace std;
using namespace helper;

namespace containers {
namespace sets {

/*
  ---- Abilities of sets and multisets
  这两个都是有序的集合，后者允许有重复的元素而前者不允许
  须要指定一个sorting criterion，否则使用默认的 operator < 来排序
  自己写的排序函数中，不能使用<=符号，必须是严格的小于符号

  1. Sets and multisets don’t provide operations for direct element access.
  2. Indirect access via iterators has the constraint that, from the iterator’s point of view, the element
     value is constant.

  下面两种初始化方式是等价的
  set c(op) <=> set<Elem, op> c 

  c.key_comp()   Returns the comparison criterion

  limitations:
  1. you can’t use them in algorithms that are provided only for random-access iterators, 
     such as algorithms for sorting or random shuffling.
  2. you can’t call any modifying algorithm on the elements of a set or a multiset, such as remove()
     插入和删除只能使用自带的成员函数
     c.insert(val) 
     c.insert(pos,val)
     c.insert(beg,end) 
     c.insert(initlist) 
     c.emplace(args...)
     c.emplace_hint(pos,args...)
     c.erase(val) 
     c.erase(pos) 
     c.erase(beg,end) 
     c.clear()
 */
void Run()
{
   SpecialSearchOperationsDemo();

   //insert() difference in set & multiset
   //  set      -   pair<iterator,bool> insert (const value_type& val);
   //  multiset -   iterator insert (const value_type& val);
   //因为set不允许重复，所以它的return type是一个pair，第二个返回值表示插入成功与否
   std::set<double> ds = {1.1, 2.2, 3.3};
   if (ds.insert(3.3).second)
   {
      std::cout << "3.3 inserted " << std::endl;
   }
   else
   {
      std::cout << "3.3 already exists" << std::endl;
   }
   
   // 对multiset来说，c.erase(val) 会删除所有=val的元素
   // 那么如果我们只想删除第一个怎么办，参考下面
   multiset<int> ms = {1, 2, 2, 4, 4, 5};
   PRINT_ELEMENT(ms, "ms: ");
   ms.erase(2);
   PRINT_ELEMENT(ms, "ms remove 2: "); //remove all elements = 2

   auto pos = ms.find(4);
   if (pos != ms.end())
      ms.erase(pos);  //remove the first element = 4
   PRINT_ELEMENT(ms, "ms remove the first 4: ");

   // - descending order
   set<int,greater<int>> coll1;
   // insert elements in random order using different member functions
   coll1.insert({4,3,5,1,6,2});
   coll1.insert(5);
   PRINT_ELEMENT(coll1, "coll1: ");

   // insert 4 again and process return value 
   auto status = coll1.insert(4); 
   if (status.second) {
      cout << "4 inserted as element "
           << distance(coll1.begin(), status.first) + 1 << endl;
   }  
   else {
      cout << "4 already exists" << endl;
   }
   // assign elements to another set with ascending order
   set<int> coll2(coll1.cbegin(),coll1.cend());

   PRINT_ELEMENT(coll2, "coll2: ");

   // remove all elements up to element with value 3 coll2.erase (coll2.begin(), coll2.find(3));
   // remove all elements with value 5
   int num;
   num = coll2.erase (5);
   cout << num << " element(s) removed" << endl;

   copy (coll2.cbegin(), coll2.cend(),
         ostream_iterator<int>(cout," "));
   cout << endl;

}

/*
 ---- Special Search Operations
 c.count(val)        Returns the number of elements with value val
 c.find(val)         Returns the position of the first element with value val (or end() if none found)
 c.lower_bound(val)  Returns the first position, where val would get inserted
                     (the first element >= val)
 c.upper_bound(val)  Returns the last position, where val would get inserted
                     (the first element > val)
 c.equal_range(val)  Returns a range with all elements with a value equal to val 
                     (i.e., the first and last position, where val would get inserted)
 */
void SpecialSearchOperationsDemo()
{
   set<int> c;
   c.insert(1);
   c.insert(2);
   c.insert(4);
   //c.insert(4);
   c.insert(5);
   c.insert(6);

   cout << "count(1) = " << c.count(1) << endl;
   cout << "lower_bound(3) : " << *c.lower_bound(3) << endl;
   cout << "upper_bound(3) : " << *c.upper_bound(3) << endl;
   cout << "equal_range(3) : " << *c.equal_range(3).first << " "
                               << *c.equal_range(3).second << endl;
   cout << "lower_bound(5) : " << *c.lower_bound(5) << endl;
   cout << "upper_bound(5) : " << *c.upper_bound(5) << endl;
   cout << "equal_range(5) : " << *c.equal_range(5).first << " "
                               << *c.equal_range(5).second << endl;

}

}
}