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
    
}

}
}