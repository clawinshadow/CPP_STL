#include "auxiliary_functions.h"

#include <utility>
#include <iostream>
#include <algorithm>
#include <ratio>

namespace utility {
namespace auxiliary_funcs {

bool int_ptr_less(int *a, int *b)
{
    return *a < *b;
}

void minmax_demo()
{
    // std::min() 有以下四种形式
    // 1. min(a, b): returns the minimum of a and b, comparing with < 
    // 2. min(a, b, cmp): returns the minimum of a and b, comparing with cmp
    // 3. min(initlist): returns the minimum in a initializer list, comparing with <
    // 4. min(initlist, cmp): returns... comparing with cmp
    // std::max(), std::minmax() 都有相同的这四种形式
    std::cout << std::min(3, 4) << std::endl;
    std::cout << std::min({2, 3, 4}) << std::endl;

    // minmax() returns a Pair
    std::pair<double, double> extremes = std::minmax({1.0, -2.3, 5.1, 7.9, 6.0});
    printf("extremes: [%f, %f]\n", extremes.first, extremes.second);

    // use comparer
    int x = 17;
    int y = 32;
    int z = 29;
    int *px = &x;
    int *py = &y;
    int *pz = &z;
    std::pair<int *, int *> ptr_extremes = std::minmax({px, py, pz}, int_ptr_less);
    std::cout << *ptr_extremes.first << ", " << *ptr_extremes.second << std::endl;

    // trick
    int i = 1;
    long j = 23;
    // auto a = std::max(i, j); //Compile error: arguments types don't match
    auto b = std::max<long>(i, j); // OK
    auto c = std::max<int>(i, j);  // OK
}

/*
swap() 内部都是用move或者move assignable来实现的，那么要求传进来的参数类型本身支持这个操作
另外一个，我们书写自己的类的时候，假如是个很复杂的类型，有不少重量级的成员，那么我们最好也实现一个
该类的swap()方法来提升性能
class A {
    private:
        T a;
        T b;
    public:
    ...
        void swap(A& x)
        {
            std::swap(a, x.a);
            std::swap(b, x.b);
        }
}

void swap(A& x, A& y) noexcept(noexcept(x.swap(y)))
{
    x.swap(y)
}
 */
void swap_demo()
{
    int a = 1;
    int b = 2;
    printf("a = %d, b = %d\n", a, b);
    std::swap(a, b);
    printf("a = %d, b = %d\n", a, b);

    // 还可以交换数组
    int x[] = {1, 2, 3};
    int y[] = {4 ,5, 6};
    std::swap(x, y);
    printf("y: [%d, %d, %d]\n", y[0], y[1], y[2]);
}

/*
The ratio utility is a general purpose utility allowing one to easily and safely compute rational values at compile time. 
The ratio class catches all errors (such as divide by zero and overflow) at compile time.

namespace std {
       template <intmax_t N, intmax_t D = 1>
       class ratio {
         public:
           typedef ratio<num,den> type;
           static constexpr intmax_t num;
           static constexpr intmax_t den;
}; }

num 表示 分子 numerator， den 表示 分母 denominator
 */
void ratio_demo()
{
    typedef std::ratio<5,3> FiveThirds;
    std::cout << FiveThirds::num << "/" << FiveThirds::den << std::endl;

    typedef std::ratio<25,15> AlsoFiveThirds;
    std::cout << AlsoFiveThirds::num << "/" << AlsoFiveThirds::den << std::endl;

    std::ratio<42,42> one;
    std::cout << one.num << "/" << one.den << std::endl;
    std::ratio<0> zero;
    std::cout << zero.num << "/" << zero.den << std::endl;
    typedef std::ratio<7,-3> Neg;
    std::cout << Neg::num << "/" << Neg::den << std::endl;

    //ratio的四则运算..是否相等
    typedef std::ratio_add<std::ratio<2, 5>, std::ratio<1, 5>>::type SUM_TYPE;
    std::cout << SUM_TYPE::num << "/" << SUM_TYPE::den << std::endl;

    std::cout << std::boolalpha << std::ratio_equal<FiveThirds, AlsoFiveThirds>::value << std::endl;
}

}
}