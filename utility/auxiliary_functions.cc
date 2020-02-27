#include "auxiliary_functions.h"

#include <utility>
#include <iostream>
#include <algorithm>
#include <ratio>
#include <ctime>
#include <chrono>
#include <type_traits>

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

num 表示 分子 numerator, den 表示 分母 denominator
这个类型主要在clocks timers里面用得多
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

/*
 * clocks and timers: 每种语言的时间系统都是个挺精妙的系统, 一般都由以下3个基本概念组成
 * 1. duration: 表示一段持续的时间, 由两个元素组成, 一是 tick, 这个tick表示一个基本单位, 可以是一秒、一分等,
 *              二是 tick前面的倍数, 比如 3个 1秒，那这个duration就是三秒..
 * 2. timepoint: 表示一个时间点，它也是由两个元素组成的，即一个duration加上一个时间的零点时刻(epoch)，比如
 *               1971.1.1零点，那么就是"1970.1.1 之后的一年"，UNIX和POSIX系统的epoch都是起始自1970.1.1
 * 3. clock: defines the epoch of a timepoint, provides a convenient function of now()
 *
 */
void durations_demo()
{
    //constructor: A duration is a combination of a value representing the number of ticks
    //             and a fraction representing the unit in seconds
    //下面初始化的例子中，第一个模板参数表示the type of the number of ticks,
    //第二个模板参数表示unit的类型，是以秒为基本单位的，默认为一秒
    std::chrono::duration<int> seconds(20);  // 20 的类型是int，第二个参数使用默认的一秒，那就是20秒
    std::chrono::duration<double, std::ratio<60>> halfMinute(0.5); //0.5是double类型，第二个参数表示一个unit是60秒
    std::chrono::duration<long, std::ratio<1, 1000>> millisecond(1); // 1毫秒

    //像上面那么定义很麻烦，于是标准库提供几个常用的typedef
    //std::chrono::nanoseconds	duration</*signed integer type of at least 64 bits*/, std::nano>
    //std::chrono::microseconds	duration</*signed integer type of at least 55 bits*/, std::micro>
    //std::chrono::milliseconds	duration</*signed integer type of at least 45 bits*/, std::milli>
    //std::chrono::seconds	duration</*signed integer type of at least 35 bits*/>
    //std::chrono::minutes	duration</*signed integer type of at least 29 bits*/, std::ratio<60>>
    //std::chrono::hours	duration</*signed integer type of at least 23 bits*/, std::ratio<3600>>
    //...
    std::chrono::seconds interval(20); //instead of std::chrono::duration<int> interval(20);

    // duration 常用的几个成员
    // count() 表示ticks的个数，rep 表示 tick type， period表示 unit type
    typedef std::chrono::duration<double, std::ratio<60>> MinType;
    MinType halfMin(0.5);
    std::cout << "halfMin count(): " << halfMinute.count() << std::endl;
    std::cout << "halfMin tick type is double ? " << std::boolalpha << std::is_same<MinType::rep, double>() << std::endl;
    printf("halfMin unit type: [%ld\\%ld] seconds\n", MinType::period::num, MinType::period::den);

    // arithmetic operations
    // 要注意两种不同类型的duration相加的时候，对于运算结果的unit type的推断
    // Due to a provided overloading of common_type<> for durations,
    // the resulting duration will have a unit that is the greatest common divisor of the units of both operands
    std::chrono::duration<int, std::ratio<1, 3>> d1(1);
    std::chrono::duration<int, std::ratio<1, 5>> d2(1);
    auto d3 = d1 + d2;   // 1/3 和 1/5 的最大共因数 为 1/15, 那么结果的unit type就是 1/15, 8个ticks
    std::cout<< "d3.count() : " << d3.count() << std::endl;

    std::chrono::seconds twentySeconds(20); // 20 seconds
    std::chrono::hours aDay(24); // 24 hours
    std::chrono::milliseconds ms(1); // 0 milliseconds
    ms += twentySeconds + aDay; // milliseconds + hours, 结果type是milliseconds, 86,401,000 milliseconds
    --ms;    // 减一个tick: 86,400,000 milliseconds
    ms *= 2; // 172,840,000 milliseconds
    std::cout << ms.count() << " ms" << std::endl;
    std::cout << std::chrono::nanoseconds(ms).count() << " ns" << std::endl;

    // conversions
    // 对不同的unit type, 向更精细的去转化是隐式转换，没问题，比如秒向毫秒转换
    std::chrono::seconds s(62);
    std::chrono::milliseconds millis = s; //OK
    std::cout << "milliseconds: " << millis.count() << std::endl;
    // 但向更粗放的类型去转化，就有问题，需要用到显示转换
    // std::chrono::minutes m = s; //ERROR
    std::chrono::minutes m = std::chrono::duration_cast<std::chrono::minutes>(s);
    std::cout << "m.count() = " << m.count() << std::endl;

    // converting a duration with a floating-point tick type also requires an explicit
    // cast to convert it into an integral duration type
    std::chrono::duration<double, std::ratio<60>> halfMin2(0.5);
    //std::chrono::seconds s1 = halfMin2; // ERROR
    std::chrono::seconds s2 = std::chrono::duration_cast<std::chrono::seconds>(halfMin2); // OK
}

/*
 * A clock defines an epoch and a tick period, C++里面常见的epoch是UNIX系统的1970.1.1, tick的单位是一纳秒
 * clock还有个steady的概念，如果它不是steady的，表示我们可以通过更改系统时间，从而影响这个clock生成出来的time_point
 * 反之如果是steady的，它内部的时间线就是一直稳定的，一直向前走，我们自己改变不了
 * C++标准库里面提供了3种clock
 * 1. system_clock: 最常用的，represents timepoints associated with the usual real-time clock of the current system
 *           provides to_time_t() and from_time_t() to convert between any timepoint and the C system time type time_t
 * 2. steady_clock: gives the guarantee that it never gets adjusted,
 *           timepoint values never decrease as the physical time advances
 * 3. high_resolution_clock: represents a clock with the shortest tick period possible on the current system.
 */

template <typename C>
void printClockData ()
{
    using namespace std;
    cout << "- precision: ";
// if time unit is less or equal one millisecond
    typedef typename C::period P; // type of time unit
    if (ratio_less_equal<P, milli>::value) {
        // convert to and print as milliseconds
        typedef typename ratio_multiply<P, kilo>::type TT;
        cout << fixed << double(TT::num)/TT::den
             << " milliseconds" << endl;
    }
    else {
        // print as seconds
        cout << fixed << double(P::num)/P::den << " seconds" << endl;
    }
    cout << "- is_steady: " << boolalpha << C::is_steady << endl;
}

void clock_demo()
{
    std::cout << "system_clock: " << std::endl;
    printClockData<std::chrono::system_clock>();
    std::cout << "\nhigh_resolution_clock: " << std::endl;
    printClockData<std::chrono::high_resolution_clock>();
    std::cout << "\nsteady_clock: " << std::endl;
    printClockData<std::chrono::steady_clock>();
}

std::string asString(const std::chrono::system_clock::time_point& tp)
{
    // convert to system time:
    std::time_t t = std::chrono::system_clock::to_time_t(tp);

    // 这里会将时间转化成本地时间，附带着时区的，ctime实际上就是std::asctime(localtime(...))的快捷方式
    // std::string ts = std::ctime(&t);

    // 如果想使用UTC时间(universal time)
    std::string ts = std::asctime(gmtime(&t));

    // convert to calendar time
    ts.resize(ts.size() - 1);
    // skip trailing newline
    return ts;
}

void timepoint_demo()
{
    // print the epoch of this system clock:
    std::chrono::system_clock::time_point tp;
    std::cout << "epoch: " << asString(tp) << std::endl;

    // print current time:
    tp = std::chrono::system_clock::now();
    std::cout << "now: " << asString(tp) << std::endl;

    // print minimum time of this system clock:
    tp = std::chrono::system_clock::time_point::min();
    std::cout << "min: " << asString(tp) << std::endl;

    // print maximum time of this system clock:
    tp = std::chrono::system_clock::time_point::max();
    std::cout << "max: " << asString(tp) << std::endl;
}

/*
 * ctime 是以前C里面的时间处理单元，以下几个方法比较常用
 * time_t: Type of numeric values representing timepoints, 可用于和现在chrono里面的time_point互相转化
 * struct tm: Type of “broken down” calendar time, 可以由年月日时分秒来构建
 * mktime()： Converts a struct tm into a time_t
 * time()： Yields the current time as numeric value
 * localtime(), gmtime()： time_t -> struct tm, 区别在于是否使用时区
 * asctime(): struct tm -> calendar string
 */

std::chrono::system_clock::time_point makeTimePoint (int year, int mon, int day,
               int hour, int min, int sec=0)
{
    struct std::tm t;
    t.tm_sec = sec;     // second of minute (0 .. 59 and 60 for leap seconds)
    t.tm_min = min;     // minute of hour (0 .. 59)
    t.tm_hour = hour;   // hour of day (0 .. 23)
    t.tm_mday = day;    // day of month (0 .. 31)
    t.tm_mon = mon - 1; // month of year (0 .. 11)
    t.tm_year = year - 1900; // year since 1900
    t.tm_isdst = -1;    // determine whether daylight saving time
    std::time_t tt = std::mktime(&t);
    if (tt == -1) {
        throw "no valid system time";
    }
    return std::chrono::system_clock::from_time_t(tt);
}

void ctime_demo()
{
    auto tp1 = makeTimePoint(2020,01,27,00,00);
    std::cout << asString(tp1) << std::endl;

    auto tp2 = makeTimePoint(2011,05,23,13,44);
    std::cout << asString(tp2) << std::endl;
}

/*
 * The following header files compatible with C are often used in C++ programs: <cstddef>,
   <cstdlib>, and <cstring>. They are the C++ versions of the C header files <stddef.h>,
   <stdlib.h>, and <string.h>
   1. <cstddef>
        NULL : Pointer value for “not defined” or “no value”, 0 in C++
        nullptr_t : Type of nullptr (since C++11)
        size_t : Unsigned type for size units, such as number of elements
        ptrdiff_t : Signed type for differences of pointer
        max_align_t : Type with maximum alignment in all contexts (since C++11)
        offsetof(type,mem) : Offset of a member mem in a structure or union type
   2. <cstdlib>
        EXIT_SUCCESS : int, Indicates a normal end of the program
        EXIT_FAILURE: int, Indicates an abnormal end of the program
        exit (int status) : Exit program (cleans up static objects)
        quick_exit (int status) : Exit program with cleanup according to at_quick_exit() (since C++11)
        _Exit (int status) : Exit program with no cleanup (since C++11)
        abort() : Abort program (might force a crash on some systems)
        atexit (void (*func)()) : call func on exit

        The exit() and abort() functions are provided to terminate a program in any function without going back to main():
        • exit() destroys all static objects, flushes all buffers, closes all I/O channels, and terminates
                the program, including calling atexit() functions. If functions passed to atexit() throw
                exceptions, terminate() is called.
        • abort() terminates a program immediately with no cleanup.

        Neither of these functions destroys local objects, because no stack unwinding occurs. To ensure
        that the destructors of all local objects are called, you should use exceptions or the ordinary return
        mechanism to return to and exit main().
    3. <cstring>, low-level functions to manipulate memory
        memchr (const void* ptr, int c, size_t len) : Finds character c in first len bytes of ptr
        memcmp (const void* ptr1, const void* ptr2, size_t len)
        memcpy (void* toPtr, const void* fromPtr, size_t len)
        memmove (void* toPtr, const void* fromPtr, size_t len)
        memset (void* ptr, int c, size_t len)

 */

}
}