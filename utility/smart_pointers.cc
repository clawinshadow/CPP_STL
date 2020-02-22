/*
为什么我们需要 smart pointers?
    之前我们使用指针时，因为指针指向的资源一般都不在当前的scope里面，所以对它和它所指向的资源的管理
一般都很复杂，并且很容易出错，一般而言我们要避免以下几种情况的发生

假设有多个指针指向同一个object
1. dangling pointers: there should be no problems when one of the pointers gets destroyed
2. resource leaks： 当最后一个指向该object的指针被销毁时，也没有任何异常发生，资源得以被释放

C++11之后，smarter pointers 解决了这几个痛点，主要包含以下两类
1. shared_ptr： shared ownership, Multiple smart pointers can refer to the same object 
so that the object and its associated resources get released whenever the last reference to it gets destroyed
还有几个helper class: weak_ptr, bad_weak_ptr, and enable_shared_from_this

2. unique_ptr: exclusive ownership or strict ownership. 
    This pointer ensures that only one smart pointer can refer to this object at a time
    especially useful for avoiding resource leaks, 
    such as missing calls of delete after or while an object gets created with new and an exception occurred.

之前98里面有个 auto_ptr<> 有类似于 unique_ptr的功能，现在已经正式deprecated
所有的smart pointers都定义在 <memory> 头文件里
*/

#include "smart_pointers.h"

#include <iostream>
#include <memory>
#include <vector>
#include <string>

namespace utility {
namespace smart_pointers {

using namespace std;

void shared_ptr_demo()
{
    //construct a shared ptr with a normal pointer
    //注意以下几种不同的初始化方式，以pNico为例
    // 1. most trivial
    std::shared_ptr<std::string> pNico(new std::string("nico"));
    // 2. use initializer list
    std::shared_ptr<std::string> pNico2{new std::string("nico")};
    // 3. make_shared()，这是性能最好的方法，因为前面两种方法实际上有两次操作
    //    一次是new object，一次是new share_ptr
    std::shared_ptr<std::string> pNico3 = std::make_shared<std::string>("Nico");
    // 下面的方式会报错
    // the constructor taking a pointer as single argument is explicit, 
    // you can’t use the assignment notation here because that is considered to be an implicit conversion
    // std::shared_ptr<std::string> pNico_Fail = new std::string("Nico"); //ERROR

    std::shared_ptr<std::string> pJutta(new std::string("jutta"));

    //use shared ptr as normal pointer: ->, *
    (*pNico)[0] = 'N';
    pJutta->replace(0, 1, "J");

    //retrieve the internal pointer of string
    std::string *pStr = pJutta.get();
    std::cout << "pStr: " << *pStr << std::endl;

    //put them in different places
    std::vector<std::shared_ptr<std::string>> persons;
    persons.push_back(pNico);
    persons.push_back(pNico);
    persons.push_back(pJutta);
    persons.push_back(pNico);
    persons.push_back(pJutta);

    for (auto ptr: persons)
    {
        std::cout << *ptr << std::endl;
    }

    *pNico = "Huang Fan";

    std::cout << "-------------" << std::endl;

    // all pNico change to new value
    for (auto ptr: persons)
    {
        std::cout << *ptr << std::endl;
    }

    //print reference count, a member function, operator: . not ->
    std::cout << "use count of pNico: " << persons[0].use_count() << std::endl;

    // use reset() to assign a new pointer to shared_ptr
    pNico.reset(new std::string("Nico Again"));
    std::cout << "pNico: " << *pNico << std::endl;

    // define our own deleter, which will be called when the use_count become zero
    std::shared_ptr<std::string> pNico5(new std::string("Nico 5"),
        [](std::string *p) {
            std::cout << "delete " << *p << std::endl;
            delete p;
        });

    pNico5 = nullptr; // pNico5 does not refer to the string any longer

    // dealing with arrays
    // Note that the default deleter provided by shared_ptr calls delete, not delete[]
    // 所以shared_ptr理论上来说是不适用于数组的，因为它不能合理释放数组的资源
    // 注意下面的定义中，shared_ptr<int> 不是 shared_ptr<int[]>
    std::shared_ptr<int> p(new int[10]); // ERROR, but compiles

    std::unique_ptr<int[]> p2(new int[10]); // OK for unique_ptr
    //std::shared_ptr<int[]> p3(new int[10]); // ERROR: does not compile

    // 但我们可以自定义一个deleter来避免错误的释放数组资源
    std::shared_ptr<int> p4(new int[10],
        [](int* p) {
            delete[] p;
        }); // that's correct

}

class Person {
public:
    string name;
    shared_ptr<Person> mother;
    shared_ptr<Person> father;
    vector<shared_ptr<Person>> kids;

    Person (const string& n,
            shared_ptr<Person> m = nullptr,
            shared_ptr<Person> f = nullptr)
            : name(n), mother(m), father(f) {
    }
    ~Person() {
        cout << "delete " << name << endl;
    }
};

shared_ptr<Person> initFamily (const string& name)
{
    shared_ptr<Person> mom(new Person(name+"’s mom"));
    shared_ptr<Person> dad(new Person(name+"’s dad"));
    shared_ptr<Person> kid(new Person(name,mom,dad));
    mom->kids.push_back(kid);
    dad->kids.push_back(kid);
    return kid;
}

class PersonEx {
public:
    string name;
    shared_ptr<PersonEx> mother;
    shared_ptr<PersonEx> father;
    vector<weak_ptr<PersonEx>> kids;

    PersonEx (const string& n,
              shared_ptr<PersonEx> m = nullptr,
              shared_ptr<PersonEx> f = nullptr)
              : name(n), mother(m), father(f) {
    }
    ~PersonEx() {
        cout << "delete " << name << endl;
    }
};

shared_ptr<PersonEx> initFamilyEx (const string& name)
{
    shared_ptr<PersonEx> mom(new PersonEx(name+"’s mom"));
    shared_ptr<PersonEx> dad(new PersonEx(name+"’s dad"));
    shared_ptr<PersonEx> kid(new PersonEx(name, mom, dad));
    mom->kids.push_back(kid);
    dad->kids.push_back(kid);
    return kid;
}

/*
why do we need weak_ptr?
我们使用shared_ptr最主要的一个原因是引用计数为零时，它可以自动释放资源。
但有些时候它并不能完成这个工作，比如以下这种情况：
cyclic references: If two objects refer to each other using shared_ptrs, and you
want to release the objects and their associated resource if no other references to these objects
exist, shared_ptr won’t release the data, because the use_count() of each object is still 1

weak_ptr 用来解决这种问题，which allows sharing but not owning an object
它只能使用一个shared_ptr来初始化，当该shared_ptr的引用计数为零时，所有由它初始化过的weak_ptr自动清空

*/
void weak_ptr_demo()
{
    shared_ptr<Person> p = initFamily("nico");
    cout << "nico’s family exists" << endl;
    cout << "- nico is shared " << p.use_count() << " times" << endl;
    cout << "- name of 1st kid of nico’s mom: "
         << p->mother->kids[0]->name << endl;
    
    // 并没有释放上面的"nico"
    p = initFamily("jim");
    cout << "jim’s family exists" << endl;

    std::cout << "---------- seperate line ------------" << std::endl;

    shared_ptr<PersonEx> p2 = initFamilyEx("nico");
    cout << "nico’s family exists" << endl;
    cout << "- nico is shared " << p2.use_count() << " times" << endl;
    cout << "- name of 1st kid of nico’s mom: "
         << p2->mother->kids[0].lock()->name << endl;
    
    // 成功释放上面的"nico"
    p2 = initFamilyEx("jim");
    cout << "jim’s family exists" << endl;

    // 如何去判断一个weak_ptr指向的object是否还存在
    // 1. call expired(), true 表示已经没了
    // 2. call use_count(), 0 表示已经没了
    // 3. 显示转换成一个shared_ptr, 如果报错 std::bad_weak_ptr()，表示没了
    try 
    {
        shared_ptr<string> sp(new string("hi")); // create shared pointer
        weak_ptr<string> wp = sp; // create weak pointer out of it
        sp.reset(); // release object of shared pointer

        cout << wp.use_count() << endl; // prints: 0
        cout << boolalpha << wp.expired() << endl; // prints: true
        shared_ptr<string> p(wp);// throws std::bad_weak_ptr
    }
    catch (const std::exception& e) {
        cerr << "exception: " << e.what() << endl; // prints: bad_weak_ptr
    }
}

}
}