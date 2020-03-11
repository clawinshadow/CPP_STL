#include "maps.h"
#include "helper.h"

#include <iostream>
#include <map>
#include <string>
#include <complex>
#include <iomanip>
#include <algorithm>

using namespace std;
using namespace helper;

namespace containers {
namespace maps {

/*
 * Requirements of the type arguments:
 *   1. Both key and value must be copyable or movable.
     2. The key must be comparable with the sorting criterion.
     3. The optional third template parameter defines the sorting criterion
   Abilities of maps and multimaps:
     Sets 和 multisets 有的，这两个基本都有，底层实现几乎一样，只不过 maps 的每一个元素都是一个key/value pairs.
     检索key值会很快，但是检索value就很慢
 */
void Run()
{
    map<string, int> s_i = {
            {"First", 1},
            {"Second", 2},
            {"Third", 3}
    };

    //两种遍历方式
    // 这个auto实际上也可以写成 std::pair<const string, int>
    for (auto &elem: s_i) {
        printf("[%s, %d]\n", elem.first.c_str(), elem.second);
        //elem.first = "hello"; // 不能使用迭代器修改key值 ERROR at compile time
    }

    for (auto it = s_i.cbegin(); it != s_i.cend(); ++it)
        printf("[%s, %d]\n", it->first.c_str(), it->second);

    // To change the key of an element, you have only one choice: You must replace the old element
    // with a new element that has the same value。
    // 将 insert() 和 erase() 组合使用
    s_i.insert(std::pair<string, int>("Second_2", 2));
    auto old_key_pos = s_i.find("Second");
    if (old_key_pos != s_i.end())
        s_i.erase(old_key_pos);
    for (auto it = s_i.cbegin(); it != s_i.cend(); ++it)
        printf("[%s, %d]\n", it->first.c_str(), it->second);

    // insert方法里面有一个重载是 c.insert(pos,val)
    // 我们知道在map里面插入一个元素，具体的位置不是我们自己能指定的，
    // 那么这个pos参数只是一个hint，提示一下search的初始位置而已
    // val 参数的几种形式
    s_i.insert({"Fourth", 4});
    s_i.insert(std::map<string, int>::value_type("Fifth", 5));
    // 要注意key值是带const的，这个才是原生的element type，不需要任何的隐式转换
    s_i.insert(std::pair<const string, int>("Sixth", 6));  //no implicit conversion
    s_i.insert(std::pair<string, int>("Seven", 7));
    s_i.insert(std::make_pair("Otto", 123));
    for (auto it = s_i.cbegin(); it != s_i.cend(); ++it)
        printf("[%s, %d]\n", it->first.c_str(), it->second);

    // When using emplace() to insert a new element by passing the values for its construction,
    // you have to pass two lists of arguments: one for the key and one for the element.
    std::map<std::string, std::complex<float>> m;
    m.emplace(std::piecewise_construct,
              std::make_tuple("hello"),                 // elements for the key
              std::make_tuple(3.4,7.8)); // elements for the value

    // danger: 當erase掉一個元素之后，指向这个元素的iterator随即失效，不能再做其他操作
    //    std::map<std::string,float> coll;
    //    ...
    //    for (auto pos = coll.begin(); pos != coll.end(); ++pos) {
    //        if (pos->second == value) {
    //            coll.erase(pos); // RUNTIME ERROR !!!
    //        }
    //    }

    // C++11 后，应该使用下面这种方式来替代
    //    std::map<std::string,float> coll;
    //    ...
    //    for (auto pos = coll.begin(); pos != coll.end(); ) {
    //        if (pos->second == value) {
    //            pos = coll.erase(pos); // possible only since C++11
    //        }
    //        else {
    //            ++pos;
    //        }
    //    }

    // operator [] and at()
    //      c[key]  -- Inserts an element with key, if it does not yet exist, and returns a reference to
    //                 the value of the element with key (only for nonconstant maps)
    //      c.at(key) -- Returns a reference to the value of the element with key (since C++11)
    map<string, float> stocks;
    // insert some elements
    stocks["BASF"] = 369.50;
    stocks["VW"] = 413.50;
    stocks["Daimler"] = 819.00;
    stocks["BMW"] = 834.00;
    stocks["Siemens"] = 842.20;

    // print all elements
    map<string, float>::iterator pos;
    cout << left; // left-adjust values
    for (pos = stocks.begin(); pos != stocks.end(); ++pos) {
        cout << "stock: " << setw(12) << pos->first
             << "price: " << pos->second << endl;   // setw() 设置宽度
    }
    cout << endl;
}

class RuntimeStrCmp {
public:
    enum cmp_mode {normal, no_case};
private:
    const cmp_mode mode;
    static bool nocase_compare (char c1, char c2) {
        return toupper(c1) < toupper(c2);
    }
public:
    RuntimeStrCmp(cmp_mode m=normal): mode(m) {

    }

    bool operator() (const string &s1, const string &s2) const {
        if (mode == normal) {
            return s1 < s2;
        }
        else {
            return lexicographical_compare (s1.begin(), s1.end(),
                                            s2.begin(), s2.end(),
                                            nocase_compare);
        }
    }
};

void fillAndPrint(map<string, string, RuntimeStrCmp> &coll) {
    // insert elements in random order
    coll["Deutschland"] = "Germany";
    coll["deutsch"] = "German";
    coll["Haken"] = "snag";
    coll["arbeiten"] = "work";
    coll["Hund"] = "dog";
    coll["gehen"] = "go";
    coll["Unternehmen"] = "enterprise";
    coll["unternehmen"] = "undertake";
    coll["gehen"] = "walk";
    coll["Bestatter"] = "undertaker";
    // print elements
    cout.setf(ios::left, ios::adjustfield);
    for (const auto &elem : coll) {
        cout << setw(15) << elem.first << " "
             << elem.second << endl;
    }
    cout << endl;
}

void RunEx()
{
    // create a container with the default comparison criterion
    map<string, string, RuntimeStrCmp> coll1;
    fillAndPrint(coll1);

    // create an object for case-insensitive comparisons
    RuntimeStrCmp ignorecase(RuntimeStrCmp::no_case);

    // create a container with the case-insensitive comparisons criterion
    map<string, string, RuntimeStrCmp> coll2(ignorecase);
    fillAndPrint(coll2);
}

}
}