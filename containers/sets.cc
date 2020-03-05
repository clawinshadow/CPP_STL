#include "sets.h"
#include "helper.h"

#include <set>
#include <iostream>

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
 */
void Run()
{

}

}
}