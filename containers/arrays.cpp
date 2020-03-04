/*
 * It wraps an ordinary static C-style array providing the interface of an STL container
 * Conceptionally, an array is a sequence of elements with constant size.
 * Thus, you can neither add nor remove elements to change the size.
 * Only a replacement of element values is possible.
 *
 * If you need a sequence with a fixed number of elements, class array<> has the best performance
   because memory is allocated on the stack (if possible), reallocation never happens, and you have
   random access.
 */

#include "arrays.h"
#include "helper.h"

#include <cstring>
#include <array>
#include <iostream>
#include <type_traits>

using namespace std;
using namespace helper;

namespace containers {
namespace arrays {

void Run()
{
    // ---- Initialization
    // array<>的初始化有几个特殊的地方
    // 1. 必须使用第二个参数来指定数组的大小
    // 2. array<> is the only container whose elements are default initialized when nothing is
    //    passed to initialize the elements. This means that for fundamental types, the initial value might be
    //    undefined rather than zero

    //std::array<int> arr;     // Compile error
    std::array<int, 5> arr1;
    cout << arr1[0] << endl;  // elements of arr1 have undefined value, 不一定是 0
    std::array<int, 5> arr2 = {}; // OK: all elements of arr2 have value 0 (int())
    //一般都是用initializer list来初始化数组
    std::array<int, 5> arr3 = { 42, 377, 611, 21, 44 };
    std::array<int, 5> arr4 = { 42 }; // initializer list里面的个数可以比数组长度少，后面的自动补零
    cout << arr4[0] << ", " << arr4[1] << endl;
    //std::array<int, 2> arr5 = { 1, 2, 3 }; // 但是不能多，compile error
    //std::array<int,5> arr6({ 1, 2, 3, 4, 5, 6 }) //compile error, 没有提供基于initializer list的constructor或者assignment operator

    // ---- Swap 的特殊地方
    // swap() 应用于数组的时候，性能不好，linear complexity, 因为它的swap()并不是简单的交换内部指针
    // 估计还是需要挨个copy元素。另外，swap完了后，之前的iterators和references不会跟着变过去，还是指向
    // 旧的位置

    // 可以对数组使用move
    std::array<string, 2> strArr1 = {"Hello", "World"};
    std::array<string, 2> strArr2 = std::move(strArr1);
    std::cout << strArr2[0] << endl;
    std::cout << strArr1[0] << endl;

    AssignmentDemo();

    // ---- Using array<> as C-Style Arrays
    //STL保证数组的地址空间是连续的，和vector一样，这意味着我们可以像使用c style数组那样使用标准库的array<>
    std::array<char, 41> a;
    strcpy(&a[0], "Hello, World");
    printf("a: %s\n", &a[0]);
    //不必使用 &a[0] 这种方式，使用data()成员函数
    strcpy(a.data(), "Hello, World too");
    printf("a: %s\n", a.data());

    // 这种写法要警惕，是很可能出错的
    // printf("a: %s\n", a.begin()); // ERROR (might work, but not portable)

    // ---- Tuple Interface
    typedef std::array<std::string, 5> FiveStrings;
    FiveStrings fv = { "hello", "nico", "how", "are", "you" };
    cout << "FiveStrings size: " << std::tuple_size<FiveStrings>::value << endl;
    cout << "FiveStrings type is string: " << boolalpha
         << std::is_same<std::tuple_element<1, FiveStrings>::type, string>::value << endl;
    cout << "1st value: " << std::get<1>(fv) << endl;
}

void AssignmentDemo()
{
    // 使用 = 操作符 或者 swap() 来给数组赋值的时候，两个数组的类型必须相等
    // 即不止是元素类型，而且数组长度也必须一致
    std::array<int, 3> arr1 = {1, 2, 3};
    std::array<int, 3> arr2 = {4, 5, 6};
    std::array<int, 5> arr3 = {1, 2, 3, 4, 5};

    arr1.swap(arr2);
    PRINT_ELEMENT(arr1, "arr1 after swap: ");
    std::swap(arr1, arr2);  //swap的不同写法
    PRINT_ELEMENT(arr1, "arr1 after swap again: ");

    //std::swap(arr2, arr3); //compile error, 因为两个数组的长度不一样
    arr3.fill(9);
    PRINT_ELEMENT(arr3, "arr3 filled with 9: ");

    std::array<int, 5> arr4 = arr3;
    PRINT_ELEMENT(arr4, "arr4 = arr3: "); // 使用 = 操作符来赋值

    // -- Element Access
    //    at(), [], front(), back()
    //    at 在数组越界时能抛出out_of_range异常, [] 越界时 undefined behavior
    try {
        std::cout << arr4.at(6) <<  std::endl;  //报一个确定的错
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        std::cout << arr4[6] <<  std::endl;  // 可能会输出一个随机值，可能会crash掉，但不会报错
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    // 支持所有的 iterator functions 接口，比如 begin(), end(), cbegin(), cend(), rbegin()...等等
}

}
}