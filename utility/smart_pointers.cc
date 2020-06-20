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
    //pNico.reset(new string("Huang Fan"));

    std::cout << "-------------" << std::endl;

    // all pNico change to new value
    for (auto ptr: persons)
    {
        std::cout << *ptr << std::endl;
    }

    //print reference count, a member function, operator: . not ->
    std::cout << "use count of pNico: " << persons[0].use_count() << std::endl;

    // use reset() to assign a new pointer to shared_ptr
    // 注意这里pNico reset了之后，不影响前面persons中已经添加了的pNico，它们还是指向旧的字符串"Huang Fan"
    // "Huang Fan"的引用计数也还是3，所以 pNico.reset() 不更改内部指针指向的对象的值，它跟 *pNico = xxx 是不一样的
    pNico.reset(new std::string("Nico Again"));
    std::cout << "pNico: " << *pNico << std::endl;
    persons.push_back(pNico);
    persons.push_back(pNico);

    for (auto ptr: persons)
    {
        std::cout << *ptr << std::endl;
    }
    std::cout << "use count of old pNico: " << persons[0].use_count() << std::endl;
    std::cout << "use count of new pNico: " << persons.back().use_count() << std::endl;

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

    // move semantics in constructor
    shared_ptr<string> sp_str_1(new string("HF"));
    // the ownership of sp_str_1 move to sp_str_2, sp_str_1 will be empty
    shared_ptr<string> sp_str_2(move(sp_str_1));
    cout << "sp_str_2 use count: " << sp_str_2.use_count() << endl;
    cout << boolalpha << "sp_str_1 == nullptr: " << (sp_str_1.get() == nullptr) << endl;

    /*
    还有几个典型的操作：
    sp1 = sp2  //Assignment, sp1 lose its previous ownership, and share sp2's same ownership
    sp1 = move(sp2) //Move assignment, sp2 transfer its ownership to sp1
    sp1.swap(sp2)   //Swap pointers and deleters bwteen sp1 and sp2
    swap(sp1, sp2)  // the same
    sp.reset()      //lose ownership, empty sp
    sp.reset(ptr)   //lose ownership, then reinitialize with the ownership of *ptr
    sp.unique()     //equals to sp.use_count() == 1, but might be faster
    static_pointer_cast(sp) // static_cast<> semantic for sp
    dynamic_pointer_cast(sp) .. const_pointer_cast(sp).. // 都一样

    get_deleter(sp):
    e.g. 
        auto del = [] (int* p) {
        delete p;
        };
        std::shared_ptr<int> p(new int, del);
        decltype(del)* pd = std::get_deleter<decltype(del)>(p);

    shared pointers are not thread-safe, but use_count() 一般都可以用，只是
    返回结果可能不是最新的
    标准库也提供了一下方法来保证shared pointers的原子操作特性
    atomic_is_lock_free(&sp)  - Returns true if the atomic interface to sp is lock free
    atomic_load(&sp)  - Returns sp
    atomic_store(&sp,sp2) - Assigns sp2 to sp
    atomic_exchange(&sp,sp2) - Exchange values of sp and sp2
    */
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
template <typename T>
shared_ptr<T> InitFamily(const string& name)
{
    shared_ptr<T> mom(new T(name+"’s mom"));
    shared_ptr<T> dad(new T(name+"’s dad"));
    shared_ptr<T> kid(new T(name, mom, dad));
    mom->kids.push_back(kid);
    dad->kids.push_back(kid);
    return kid;
}

void weak_ptr_demo()
{
    // Find initFamily() in smart_pointers.h
    shared_ptr<Person> p = InitFamily<Person>("nico");
    cout << "nico’s family exists" << endl;
    cout << "- nico is shared " << p.use_count() << " times" << endl;
    cout << "- name of 1st kid of nico’s mom: "
         << p->mother->kids[0]->name << endl;
    
    // 并没有释放上面的"nico"
    p = InitFamily<Person>("jim");
    cout << "jim’s family exists" << endl;

    std::cout << "---------- seperate line ------------" << std::endl;

    shared_ptr<PersonEx> p2 = InitFamily<PersonEx>("nico");
    cout << "nico’s family exists" << endl;
    cout << "- nico is shared " << p2.use_count() << " times" << endl;
    cout << "- name of 1st kid of nico’s mom: "
         << p2->mother->kids[0].lock()->name << endl;
    
    // 成功释放上面的"nico"
    p2 = InitFamily<PersonEx>("jim");
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

/*
shared_ptr最常见的错误用法，是同一个object被多个不同的shared_ptr所拥有，
那么当其中一个的引用计数为零时，它就会释放这个共有的object，而当别的shared_ptr
也需要释放的时候，很可能就会报double free的错误，即便不报错，同样的object被释放
两次也会有不可预测的行为

假如我们想为一个类提供一个实例方法，返回一个shared_ptr拥有该实例，那么在外部每调用一次
这个方法，都有一个不同的shared_ptr获取了同样的类实例, 这种运用显然也是错误的

这个时候我们就需要让这个类继承自 std::enable_shared_from_this<T>  
官方解释：this allows an object t that is currently managed by a std::shared_ptr named pt to 
    safely generate additional std::shared_ptr instances pt1, pt2, ... that all share ownership of t with pt.
意思是说：声明了这个之后，假如这个object t，现在已经被一个shared_ptr pt所拥有了，
        那么再有不同的shared_ptr来管理这个t时，它们都和原pt拥有同样的ownership
*/
void shared_ptr_missuse_demo()
{
    // missuse for fundamental data types
    int *p = new int(42);
    shared_ptr<int> sp1(p);
    shared_ptr<int> sp2(p); //Missuse，*p has more than one ownerships of shared_ptr
    printf("sp1 use count: %ld, sp2 use count: %ld\n", sp1.use_count(), sp2.use_count());

    int *p2 = new int(43);
    shared_ptr<int> sp3(p2);
    shared_ptr<int> sp4 = sp3; // that's ok
    shared_ptr<int> sp5(sp3);  // OK
    printf("sp3 use count: %ld, sp4 use count: %ld\n", sp3.use_count(), sp4.use_count());

    // missuse for classes
    shared_ptr<Good> spg1 = make_shared<Good>();
    shared_ptr<Good> spg2 = spg1->GetPtr();
    cout << "spg1.use_count = " << spg1.use_count() << endl; //should be 2

    try
    {
        // Bad: shared_from_this is called without having std::shared_ptr owning the caller 
        // shared_from_this() 这个方法被调用时，caller必须是由shared_ptr所管理的
        Good not_so_good;
        shared_ptr<Good> spg3 = not_so_good.GetPtr();
    }
    catch (const std::exception& e)
    {
        cout << e.what() << endl; //std::bad_weak_ptr
    }

    shared_ptr<Bad> spb1 = make_shared<Bad>();
    shared_ptr<Bad> spb2 = spb1->GetPtr();
    cout << "spb1.use_count = " << spb1.use_count() << endl; //should be 1

    //deconstruct: should be crashed. double free or corruption
}

/*
unique_ptr 几个关键点：
1. exclusive ownership: 对某个object的独占性
2. 主要是为了防止忘记释放某个资源，或者因为中途发生异常退出了，执行不到尾部delete的地方
   当拥有这个资源的unique_ptr被回收时，它所拥有的object也会被释放掉
   unique_ptr作为函数内的本地变量，或者是类的成员，都可以避免资源泄漏
   我们要知道，一个类的destructor只有当constructor()执行完毕后才会被调用，那么就是说如果
   在类创建的时候抛出异常了，destructor是不会被执行的，这样已经初始化了的指针就不会被释放了
   除非我们用unique_ptr来初始化资源
3. 替换以前的 auto_ptr
4. unique_ptr的memory overhead可以跟native pointer完全一样，性能上比 shared_ptr 要好
   当然，如果自己定义了deleter的话可能要多一点overhead

trick: source and sink
1. A function can behave as a sink of data. 
   This happens if a unique_ptr is passed as an argument to the function by rvalue reference created with std::move(). 
   In this case, the parameter of the called function gets ownership of the unique_ptr. 
   Thus, if the function does not transfer it again, the object gets deleted on function exit:
    
    void sink(std::unique_ptr<ClassA> up)    // sink() gets ownership 不用&&符号
    {
        ...
    }

    std::unique_ptr<ClassA> up(new ClassA);
    ...
    sink(std::move(up)); // up loses ownership，ClassA这个数据会在sink()方法里被沉没掉
    ...
2. source of data:
   A function can behave as a source of data. 
   When a unique_ptr is returned, ownership of the returned value gets transferred to the calling context.
    std::unique_ptr<ClassA> source()
    {
        std::unique_ptr<ClassA> ptr(new ClassA); // ptr owns the new object
        ...
        return ptr; // transfer ownership to calling function
    }
    为什么我们在return的时候不用std::move(ptr), 因为在C++11后，编译器会自动尝试加上move
*/

void unique_ptr_demo()
{
    // 初始化这些和 shared_ptr 是差不多的
    unique_ptr<string> pHF(new string("huang Fan"));
    (*pHF)[0] = 'H';
    cout << "*pHF = " << *pHF << endl;
    // 也是不能用assignment一个原始指针来初始化
    // std::unique_ptr<int> up = new int; // ERROR
    unique_ptr<int> up(new int);// OK
    // 它还可以是个空的
    std::unique_ptr<std::string> up2; //OK
    // release() 方法释放掉ownership，将资源还给一个原始指针
    string *pStr = pHF.release();
    cout << "*pSt = " << *pStr << endl; 
    //cout << *pHF << endl; // runtime error, 释放后不能再解引用该unique_ptr
    // 判断unique_ptr是否为空
    if (!pHF)
        cout << "pHF is empty" << endl;
    cout << boolalpha 
         << (pHF == nullptr) << " | " 
         << (pHF.get() == nullptr) << endl; 

    // transfer of ownership by unique_ptr
    // copy and assignment constructor都不行，只能用move
    std::string *p_str = new std::string("test string");
    std::unique_ptr<std::string> up_str_1(p_str);    //OK
    // std::unique_ptr<std::string> up_str_2(up_str_1); //Error
    std::unique_ptr<std::string> up_str_2(std::move(up_str_1)); //OK
    std::cout << boolalpha << (up_str_1 == nullptr) << std::endl;

    //std::unique_ptr<std::string> up_str_3 = up_str_2; //Error
    std::unique_ptr<std::string> up_str_3 = std::move(up_str_2);
    std::cout << boolalpha << (up_str_2 == nullptr) << std::endl;

    // dealing with array
    // 和shared_ptr一样，直接初始化一个数组是有问题的，因为delete的关系
    // std::unique_ptr<std::string> up_str_arr(new std::string[10]); //runtime error
    // 但我们不用像shared_ptr那样额外声明一个deleter来释放数组，unique_ptr有自己的实现
    std::unique_ptr<std::string[]> up_str_array(new std::string[10]); // OK
    // 但这时我们用的时候就不能使用 * and ->这几个操作符了，只能用[]
    up_str_array[3] = "Third";
    std::cout << up_str_array[3] << std::endl;

    /*
    自定义 deleters 
    unique_ptr的自定义deleter和shared_ptr有点不一样
    shared_ptr:  std::shared_ptr<int> sp(new int[10], [](int *p) { delete[] p; })
    unique_ptr: std::unique_ptr<int, void(*)(int *)> sp....
    必须在unique_ptr的<>里面以第二参数显示的声明deleter的类型才可以
    
    这个 deleter 有以下几种声明方式
    1. function object, 用个类包装一下，然后重载 "function call operator", shared_ptr里面也可以这么用
    class ClassADeleter
    {
    public:
        void operator () (ClassA* p) {
            std::cout << "call delete for ClassA object" << std::endl;
            delete p;
        }
    };
    用起来：std::unique_ptr<ClassA, ClassADeleter> up(new ClassA());
           std::shared_ptr<ClassA> up(new ClassA(), ClassADeleter());
    
    2. lambda 表达式
    std::unique_ptr<int,void(*)(int*)> up(new int[10],
        [](int* p) {
            ...
            delete[] p;
        });

    3. std::function 
    std::unique_ptr<int,std::function<void(int*)>> up(new int[10],
        [](int* p) {
            ...
            delete[] p;
        });
        
    4. decltype
        auto l = [](int* p) {
                ...
                delete[] p;
            };
        std::unique_ptr<int, decltype(l)>> up(new int[10], l);
    */
}

} //namespace smart_pointers
} //namespace utility