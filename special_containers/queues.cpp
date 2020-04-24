#include "queues.h"

#include <iostream>
#include <queue>
#include <string>

using namespace std;

namespace special_containers {
namespace queues {

void Run()
{
    /*
     * The class queue<> implements a queue (also known as FIFO)
     * 与Stack类似，You can use any sequence container class that provides the member
       functions front(), back(), push_back(), and pop_front()

       The core interface of queues is provided by the member functions push(), front(), back() and pop():
        • push() inserts an element into the queue.
        • front() returns the next element in the queue (the element that was inserted first).
        • back() returns the last element in the queue (the element that was inserted last).
        • pop() removes an element from the queue.
     */
    queue<string> q;

    // insert three elements into the queue
    q.push("These ");
    q.push("are ");
    q.push("more than ");

    // read and print two elements from the queue
    cout << q.front();
    q.pop();
    cout << q.front();
    q.pop();

    // insert two new elements
    q.push("four ");
    q.push("words!");

    // skip one element
    q.pop();

    // read and print two elements
    cout << q.front();
    q.pop();
    cout << q.front() << endl;
    q.pop();

    // print number of elements in the queue
    cout << "number of elements in the queue: " << q.size()
         << endl;
}

}
}