#include "priority_queues.h"

#include <iostream>
#include <queue>

using namespace std;

namespace special_containers {
namespace priority_queues {

void Run()
{
    /*
     *  The class priority_queue<> implements a queue from which elements are read according to their
        priority. The interface is similar to queues. That is, push() inserts an element into the queue,
        whereas top() and pop() access and remove the next element .

        HOWEVER~, the next element is not the first inserted element.

        Rather, it is the element that has the highest priority. Thus, elements are partially sorted according to their value.
        As usual, you can provide the sorting criterion as a template parameter.
        By default, the elements are sorted by using operator < in descending order.
        Thus, the next element is always the “highest” element. If more than one “highest” element exists,
        which element comes next is undefined

        与普通queue唯一不同的是它不是根据FIFO的规则来决定下一个元素是什么，而是根据排序规则pop出最大值的那个元素
        所以下面的定义中，我们可以自定义一个sorting criterion
        namespace std {
            template <typename T,
                      typename Container = vector<T>,
                      typename Compare = less<typename Container::value_type>>
            class priority_queue;
        }
        The core interface of priority queues is provided by the member functions push(), top(), and pop():
        • push() inserts an element into the priority queue.
        • top() returns the next element in the priority queue.
        • pop() removes an element from the priority queue.
     */
    priority_queue<float> q;

    // insert three elements into the priority queue
    q.push(66.6);
    q.push(22.2);
    q.push(44.4);

    // read and print two elements
    cout << q.top() << " ";
    q.pop();
    cout << q.top() << endl;
    q.pop();

    // insert three more elements
    q.push(11.1);
    q.push(55.5);
    q.push(33.3);

    // skip one element
    q.pop();

    // pop and print remaining elements
    while (!q.empty()) {
        cout << q.top() << ' ';
        q.pop();
    }
    cout << endl;
}

}
}