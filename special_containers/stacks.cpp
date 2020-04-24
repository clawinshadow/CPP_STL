#include "stacks.h"

#include <stack>
#include <string>
#include <iostream>

using namespace std;

namespace special_containers {
namespace stacks {

void Run()
{
    /*
     * The class stack<> implements a stack (also known as LIFO)
     * namespace std {
          template <typename T,
                    typename Container = deque<T>>
          class stack;
       }
       可以看到第二个参数会接受一个标准的container，默认是采用deque，
       You can use any sequence container class that provides the member functions back(), push_back(), and pop_back()
       e.g. std::stack<int,std::vector<int>> st; 这个是ok的

       The core interface of stacks is provided by the member functions push(), top(), and pop():
        • push() inserts an element into the stack.
        • top() returns the next element in the stack.
        • pop() removes an element from the stack.
     */
    stack<int> st;
    // push three elements into the stack
    st.push(1);
    st.push(2);
    st.push(3);

    // pop and print two elements from the stack
    cout << st.top() << " ";
    st.pop();
    cout << st.top() << " ";
    st.pop();

    // modify top element
    st.top() = 77;
    // push two new elements
    st.push(4);
    st.push(5);
    // pop one element without processing it
    st.pop();
    // pop and print remaining elements
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;

    // Note that when using nontrivial element types, you might consider using std::move() to insert
    // elements that are no longer used or emplace() to let the stack internally create the element (both
    // available since C++11):
    stack<pair<string, string>> stp;

    auto p = std::make_pair("Huang", "Fan");
    stp.push(std::move(p));

    stp.emplace("Huang", "Fan");
    while (!stp.empty()) {
        cout << stp.top().first << " "
             << stp.top().second << " " << endl;
        stp.pop();
    }
    cout << endl;
}

}
}