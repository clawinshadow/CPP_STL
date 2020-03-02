/*
 * 在这里简单讲一下STL中的 Errors and exception handling
 * 首先我们要明确STL的设计目的就是以性能为主要考量的，而不是使用的安全性
 * The design goal of the STL was the best performance rather than the highest security. Error checking
   wastes time, so almost none is done
   1. Error checking reduces performance, and speed is still a general goal of programs. As mentioned,
      good performance was one of the design goals of the STL.
   2. If you prefer safety over speed, you can still get it, either by adding wrappers or by using special
      versions of the STL. But when error checking is built into all basic operations, you can’t program
      to avoid error checking to get better performance
 * 那么如果我们没有按正常的方式去使用STL，它一般不会报错，造成的结果通常都是 undefined behavior
 * The C++ standard library states that any STL use that violates preconditions results in undefined
   behavior. Thus, if indexes, iterators, or ranges are not valid, the result is undefined
   那么需要怎么使用STL才能尽量保证安全呢：
   1. Iterators must be valid:
      -- 使用之前初始化
      -- for vectors and deques, if elements are inserted or deleted or reallocation takes place, iterator失效
      -- for unordered containers, if rehashing takes place, iterator失效
   2. Iterators that refer to the past-the-end position have no element to which to refer.
      Thus, calling operator * or operator -> is not allowed
   3. Ranges must be valid:
        – Both iterators that specify a range must refer to the same container.
        – The second iterator must be reachable from the first iterator.
   4. If more than one source range is used, the second and later ranges usually must have at least as
      many elements as the first one.
   5. Destination ranges must have enough elements that can be overwritten;
      otherwise, insert iterators must be used
 * 关于 Exception handling
 * 一般情况下STL只保证最基本的异常处理：The C++ standard library will not leak resources
 *     or violate container invariants in the face of exceptions.
 * 有些地方我们可以期待一些更强力的保证，类似于数据库的transaction-safe, commit or rollback 行为
 * 1. In general, no erase(), clear(), pop_back(), pop_front(), or swap() function throws an
      exception. Also, no copy constructor or assignment operator of a returned iterator throws an
      exception.
   2. For all node-based containers (lists, forward lists, sets, multisets, maps, and multimaps), in-
      cluding the unordered containers, any failure to construct a node simply leaves the container as
      it was. 意思就是 removing a node can’t fail, provided that destructors don’t throw
   3. All array-based containers (arrays, vectors, and deques) do not fully recover when an element
      gets inserted. 因为插入一个元素之前要移动后面的所有元素，一旦抛出异常了不保证之前移动的所有元素都回滚
 */

#include "stl_basics.h"
#include "containers.h"
#include "iterators.h"
#include "algorithms.h"
#include "func_arguments.h"

namespace stl_basics {

// standard  template library (STL): three components
//     1. Containers
//     2. Iterators
//     3. Algorithms
void Run()
{
    //containers::SequenceContainersDemo();
    //containers::AssociateContainersDemo();
    //containers::UnorderedContainersDemo();
    //iterators::Demo();
    //iterators::IteratorAdaptersDemo();
    //algorithms::Demo();
    //algorithms::RangeDemo();
    //algorithms::RemovingDemo();
    func_arguments::Demo();
    func_arguments::PredicatesDemo();
}

}