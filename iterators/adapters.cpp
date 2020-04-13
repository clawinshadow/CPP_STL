#include "adapters.h"
#include "helper.h"

#include <iterator>
#include <iostream>
#include <set>
#include <list>
#include <deque>
#include <algorithm>

using namespace std;

namespace iterators {
namespace adapters {

void reverse_demo_1()
{
    /*
     * Reverse iterators redefine increment and decrement operators so that they behave in reverse.
     * Thus, if you use these iterators instead of ordinary iterators, algorithms process elements in reverse order.
     * Most container classes — all except forward lists and unordered containers — as well as strings
     *provide the ability to use reverse iterators to iterate over their elements
     */
    list<int> coll = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    for_each(coll.begin(), coll.end(), [](int elem){ cout << elem << " "; });

    cout << endl;

    for_each(coll.rbegin(), coll.rend(), [](int elem){ cout << elem << " "; });
    cout << endl;
}

void reverse_demo_2()
{
    /*
     * You can convert normal iterators into reverse iterators.
     * Naturally, the iterators must be bidirectional iterators,
     * but note that the logical position of an iterator is moved during the conversion
     */
    vector<int> coll = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    // find position of element with value 5
    vector<int>::const_iterator pos;
    pos = find (coll.cbegin(), coll.cend(),5);

    cout << "pos: " << *pos << endl;

    // convert iterator to reverse iterator rpos
    vector<int>::const_reverse_iterator rpos(pos);
    cout << "rpos: " << *rpos << endl;

    /*
     * 可以看到rpos对应的值不再是5了，而是前一个值：4，为什么会这样呢？
     * 这要从 iterator 的半开闭原则说起
     * 比如 pos 对应的是第五个位置，那么假如我们要遍历 coll.begin() 到 pos,
     * 遍历过程中所取到的值实际上是 [*coll.begin, *pos), 最后第五个位置的值实际上没取到，是个闭区间
     * 那么我们反向遍历的时候，从逻辑上来说，他们遍历过程中所取到的值应该是一样的，那么这样就会造成：
     * pos 对应的 rpos 指向的位置应该是第四个位置，而 coll.begin() 对应的 coll.rbegin() 应该指向第一个位置之前的一个虚拟位置
     * 即 [*rpos, *coll.rbegin())
     * 所以我们将 pos 转化为 rpos时，rpos指向的逻辑位置要前移一位
     * 看下面的例子
     */

    deque<int> que = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    deque<int>::const_iterator pos1;
    pos1 = find(que.cbegin(), que.cend(), 2);

    deque<int>::const_iterator pos2;
    pos2 = find(que.cbegin(), que.cend(), 7);

    // print all elements in range [pos1, pos2)
    for_each(pos1, pos2, [](int elem){ cout << elem << " "; });
    cout << endl;

    // convert iterators to reverse iterators
    deque<int>::const_reverse_iterator rpos1(pos1);
    deque<int>::const_reverse_iterator rpos2(pos2);

    // print all elements in range [pos1,pos2) in reverse order
    for_each(rpos2, rpos1, [](int elem){ cout << elem << " "; }); //这样一来，他们遍历的元素就是一样的，只是顺序刚好颠倒
    cout <<endl;
}

void reverse_demo_3()
{
    /*
     * You can convert reverse iterators back into normal iterators.
     * To do this, reverse iterators provide the base() member function:
     */
    list<int> coll = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    list<int>::iterator pos = find(coll.begin(), coll.end(), 5);

    cout << "pos: " << *pos << endl;

    list<int>::reverse_iterator  rpos(pos);
    cout << "rpos: " << *rpos << endl;

    list<int>::iterator rrpos = rpos.base();
    cout << "rrpos: " << *rrpos << endl;
}

void Reverse_Iterators()
{
    reverse_demo_1();
    reverse_demo_2();
    reverse_demo_3();
}

void back_inserter_demo()
{
    /*
     * A back inserter, or back insert iterator,
     * appends a value at the end of a container by calling the push_back() member function
       push_back() is available only for vectors, deques, lists, and strings,
     */
    vector<int> coll;

    // create back inserter for coll
    // - inconvenient way
    back_insert_iterator<vector<int> > inserter1(coll);

    *inserter1 = 1;
    ++inserter1;
    inserter1 = 2;  //有没有星号都一样
    ++inserter1;
    inserter1 = 3;
    ++inserter1;
    helper::PRINT_ELEMENT(coll);

    // create back inserter and insert elements
    // - convenient way
    back_inserter(coll) = 44; // 将上面的两步合为一步
    back_inserter(coll) = 55;
    helper::PRINT_ELEMENT(coll);

    coll.reserve(2 * coll.size());
    copy(coll.begin(), coll.end(), back_inserter(coll));
    helper::PRINT_ELEMENT(coll);
}

void front_inserter_demo()
{
    /*
     * A front inserter, or front insert iterator, inserts a value at the beginning of a container by calling the
       push_front() member function.

       push_front() is available only for deques, lists, and forward lists
     */
    list<int> coll;

    // create front inserter for coll
    // - inconvenient way
    front_insert_iterator<list<int> > iter(coll);

    *iter = 1;
    iter++;
    iter = 2;
    iter++;
    *iter = 3;
    helper::PRINT_ELEMENT(coll);

    // create front inserter and insert elements
    // - convenient way
    front_inserter(coll) = 44;
    front_inserter(coll) = 55;
    helper::PRINT_ELEMENT(coll);

    // use front inserter to insert all elements again
    copy(coll.begin(), coll.end(), front_inserter(coll));
    helper::PRINT_ELEMENT(coll);
}

void general_inserter_demo()
{
    /*
     * A general inserter, or general insert iterator,  is initialized with two values: the container and the
       position that is used for the insertions.
       Using both, a general inserter calls the insert() member function with the specified position as argument

       A general inserter is available for all standard containers except arrays and forward lists,
       because these containers provide the needed insert() member function
       However, for associative and unordered containers, the position is used only as a hint, because the value
       of the element defines the correct position
     */
    set<int> coll;

    // create insert iterator for coll
    // - inconvenient way
    insert_iterator<set<int> > iter(coll,coll.begin());

    *iter = 1;
    iter++;
    iter = 2;
    iter++;
    *iter = 3;
    helper::PRINT_ELEMENT(coll,"set: ");

    // create inserter and insert elements
    // - convenient way
    inserter(coll,coll.end()) = 44;
    inserter(coll,coll.end()) = 55;
    helper::PRINT_ELEMENT(coll,"set: ");

    // use inserter to insert all elements into a list
    list<int> coll2;
    copy (coll.begin(), coll.end(), inserter(coll2,coll2.begin()));
    helper::PRINT_ELEMENT(coll2,"list: ");

    // use inserter to reinsert all elements into the list before the second element
    copy (coll.begin(), coll.end(), inserter(coll2,++coll2.begin()));
    helper::PRINT_ELEMENT(coll2,"list: ");
}

void Insert_Iterators()
{
    /*
     * Insert iterators, also called inserters, are iterator adapters that transform an assignment of a new
       value into an insertion of that new value.
       By using insert iterators, algorithms can insert rather than overwrite.
       They provide only the ability to assign new values

       Expression           Effect
        *iter            No-op (returns iter)
        iter = value     Inserts value
        ++iter           No-op (returns iter)
        iter++           No-op (returns iter)

       共有三类 inserters: back_inserter, front_inserter, general inserter. 本质上是分别调用容器的 push_back(),
       push_front(), 和 insert() 方法。所以这三种inserter只能给支持对应的成员函数的容器使用

     */

    back_inserter_demo();
    front_inserter_demo();
    general_inserter_demo();
}

void ostream_iterator_demo()
{
    /*
     * Ostream iterators write assigned values to an output stream.
     * By using ostream iterators, algorithms can write directly to streams.
     * The implementation of an ostream iterator uses the same concept as the implementation of insert iterators.
     * The only difference is that they transform the assignment of a new value into an output operation by using operator <<
     *
     *  Expression                              Effect
        ostream_iterator<T>(ostream)            Creates an ostream iterator for ostream
        ostream_iterator<T>(ostream,delim)      Creates an ostream iterator for ostream, with the
                                                string delim as the delimiter between the values,
                                                (note that delim has type const char*)
        *iter                                   No-op (returns iter)
        iter = value                            Writes value to ostream: ostream<<value (followed by delim, if set)
        ++iter                                  No-op (returns iter)
        iter++                                  No-op (returns iter)
     */
    ostream_iterator<int> os(cout, "\n");

    // native way
    *os = 42;
    ++os;
    *os = 77;
    ++os;
    os = -5;
    ++os;

    // convenient way
    vector<int> coll = {1, 2, 3, 4, 5, 6};
    copy(coll.begin(), coll.end(), ostream_iterator<int>(cout));

    cout << endl;

    copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, "<"));
    cout <<endl;
}

void istream_iterator_demo()
{
    /*
     *  Expression                      Effect
        istream_iterator<T>()           Creates an end-of-stream iterator
        istream_iterator<T>(istream)    Creates an istream iterator for istream (and might read the first value)
        *iter                           Returns the value, read before (reads first value if not done by the constructor)
        iter->member                    Returns a member, if any, of the actual value, read before
        ++iter                          Reads next value and returns its position
        iter++                          Reads next value but returns an iterator for the previous value
        iter1== iter2                   Tests iter1 and iter2 for equality
        iter1!= iter2                   Tests iter1 and iter2 for inequality

        就是要注意下默认的构造函数是创建一个end-of-stream iterator
     */

    // create istream iterator that reads integers from cin
    istream_iterator<int> intReader(cin);

    // create end-of-stream iterator
    istream_iterator<int> intReaderEOF;

    // while able to read tokens with istream iterator
    // - write them twice
    while (intReader != intReaderEOF) {
        cout << "once: " << *intReader << endl;
        cout << "once again: " << *intReader << endl;
        ++intReader;
    }

    //比如输入 1,2,3,f,4 输入到f时因为不再是int类型的输入，就会结束循环
}

void Stream_Iterators()
{
    /*
     * A stream iterator is an iterator adapter that allows you to use a stream as a source or destination of
       algorithms.
       In particular, an istream iterator can be used to read elements from an input stream, and
       an ostream iterator can be used to write values to an output stream.
     */
    ostream_iterator_demo();
    //istream_iterator_demo();
}

void Demos()
{
    Reverse_Iterators();
    Insert_Iterators();
    Stream_Iterators();

    /*
     * Move Iterators:
     *  std::list<std::string> s;
        ...
        std::vector<string> v1(s.begin(), s.end());            // copy strings into v1
        std::vector<string> v2( make_move_iterator(s.begin()),
                                make_move_iterator(s.end()) ); // move strings into v2
        不是很实用
     */
}

}
}