#include "details.h"

#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

namespace strings {
namespace details {

void create_and_copy()
{
    /*
     *  Expression                          Effect
        string s                            Creates the empty string s
        string s(str)                       Copy constructor; creates a string as a copy of the existing string str
        string s(rvStr)                     Move constructor; creates a string and moves the contents of rvStr to it
        string s(str,stridx)                Creates a string s that is initialized by the characters of
                                            string str starting with index stridx
        string s(str,stridx,strlen)         Creates a string s that is initialized by, at most, strlen
                                            characters of string str starting with index stridx
        string s(cstr)                      Creates a string s that is initialized by the C-string cstr
        string s(chars,charslen)            Creates a string s that is initialized by charslen
                                            characters of the character array charsith index stridx
        string s(num,c)                     Creates a string that has num occurrences of character c
        string s(beg,end)                   Creates a string that is initialized by all characters of the range [beg,end)
        string s(initlist)                  Creates a string that is initialized by all characters in initlist (since C++11)
     */
    string eptStr;
    cout << "empty string: " << eptStr << endl;

    string s("init with copy constructor");
    string s1(s); //copy constructor
    cout << "init s1 copy from s: " << s1 << endl;

    string s2(std::move(s1));
    cout << "init s2 move from s1: " << s2 << endl;

    string s3(s2, 4);
    cout << "init s3 from the 4th character in s2: " << s3 << endl;

    string s4(s2, 4, 3);
    cout << "init s4 from the 4th character in s2, length 3: " << s4 << endl;

    string s5("Huang Fan");
    cout << "init s5 directly from C-String: " << s5 << endl;

    string s6("Huang Fan", 5);
    cout << "init s6 with the first 5 characters in s5: " << s6 << endl;

    string s7(6, 'c');
    cout << "init s7 with 6 \'c\': " << s7 << endl;

    string s8(s7.begin(), s7.begin() + 3);
    cout << "init s8 with the first 3 characters in s7: " << s8 << endl;

    string s9("Fan");
    cout << "init s9 with initializer list: " << s9 << endl;
}

void size_and_capacity()
{
    /*
     * -- size operations --
     * bool string::empty () const
     * • Returns whether the string is empty (contains no characters).
     *
     * size_type string::size () const
     * size_type string::length () const
       • Both functions return the current number of characters. They are equivalent

       size_type string::max_size () const
       • Returns the maximum number of characters a string could contain.
       • Whenever an operation results in a string that has a length greater than max_size(), the class
         throws length_error

       -- capacity operations --
       size_type string::capacity () const
       • Returns the number of characters the string could contain without reallocation.

       void string::reserve ()
       void string::reserve (size_type num)
       • The first form is a nonbinding shrink-to-fit request.
       • The second form reserves internal memory for at least num characters.
       • If num is less than the current capacity, the call is taken as a nonbinding request to shrink the capacity.
       • If num is less than the current number of characters, the call is taken as a nonbinding request to
         shrink the capacity to fit the current number of characters (equivalent to the first form).
       • The capacity is never reduced below the current number of characters

        void string::shrink_to_fit ()
        • Reduces the internal memory to fit the current numbers of characters.
        • It has the same effect as reserve(0).
        • The call is taken as a nonbinding request to allow latitude for implementation-specific optimizations.
     */
    string s("Huang Fan");
    cout << "s: " << s << endl;
    cout << "s.length(): " << s.length() << endl;
    cout << "s.size(): " << s.size() << endl;
    cout << boolalpha << "s.empty() : " << s.empty() << endl;
    cout << "s.max_size(): " << s.max_size() << endl;

    cout << "s.capacity(): " << s.capacity() << endl;
    s.reserve(100);
    cout << "s.capacity() after reserve(100): " << s.capacity() << endl;
    s.shrink_to_fit();
    cout << "s.capacity() after shrint_to_fit(): " << s.capacity() << endl; //go back to 15
}

void comparisons()
{
    /*
     * 字符串的比较主要有两种方式：
     * 1. 采用 <, <=, >, >=, .. 等运算符，这时候是比较整个字符串，their characters are compared lexicographically according
          to the current character traits， 即逐个字符的比较，其次是字符的个数
       2. By using the compare() member functions, you can compare substrings.
          The compare() member functions can process more than one argument for each string,
          so you can specify a substring by its index and its length.

          Note that compare() returns an integral value rather than a Boolean value.
          This return value has the following meaning: 0 means equal, a value less than 0 means less than,
          and a value greater than 0 means greater than
     */
    cout << boolalpha << "aaaa < bbbb: " << ("aaaa" < "bbbb") << endl;
    cout << boolalpha << "aaaa < abb: " << ("aaaa" < "abb") << endl;
    cout << boolalpha << "aaaa < aaaaaa: " << ("aaaa" < "aaaaaa") << endl;

    /*
     * int string::compare (const string& str) const
     * int string::compare (const char* cstr) const
     *
     * int string::compare (size_type idx, size_type len, const string& str) const
     * int string::compare (size_type idx, size_type len, const char* cstr) const
     * • Compares at most len characters of string *this, starting with index idx with the string str.
     *
     * int string::compare (size_type idx, size_type len,
                            const string& str, size_type str_idx,
                            size_type str_len) const
       int string::compare (size_type idx, size_type len,
                            const char* chars, size_type chars_len) const
       • Compares at most len characters of string *this, starting with index idx with at most str_len
         characters of string str, starting with index str_idx
     */

    string s = "aabb";
    string b = "aabbb";
    cout << "s: " << s << endl;
    cout << boolalpha << "s.compare(aabbb): " << s.compare(b) << endl;   //-1 means less than, boolalpha也没用, 不会显示true
    cout << "s.compare(\"aabbb\")" << s.compare("aabbb") << endl;
    cout << s.compare(3, 2, b) << endl; // bb > aabbb
    cout << s.compare(0, 2, b, 0, 1) << endl; // aa > a
    cout << s.compare(0, 2, "acbbb", 1) << endl; // aa > a

}

void element_access()
{
    /*
     *  char& string::operator [ ] (size_type idx)
        const char& string::operator [ ] (size_type idx) const
        • Both forms return the character with the index idx (the first character has index 0).
        • length() or size() is a valid index, and the operator returns the value generated by the default
          constructor of the character type (for string: ’\0’). Before C++11, length() or size() was
          an invalid index value for nonconstant strings.
        • Passing an invalid index results in undefined behavior.

        char& string::at (size_type idx)
        const char& string::at (size_type idx) const
        • Both forms return the character that has the index idx (the first character has index 0).
        • For all strings, an index with length() as value is invalid.
        • Passing an invalid index — less than 0 or greater than or equal to length() or size() — throws
          an out_of_range exception.

        char& string::front ()
        const char& string::front () const
        • Both forms return the first character.
        • Calling front() for an empty string returns the value generated by the default constructor of the
          character type (for string: ’\0’).

        char& string::back ()
        const char& string::back () const
        • Both forms return the last character.
        • Calling back() for an empty string results in undefined behavior.
     */
    string s("Huang Fan");
    cout << "s: " << s << endl;
    cout << "s[s.length()] = " << s[s.length()] << endl; //'\0'
    cout << "s[0] = " << s[0] << endl;
    cout << "s.front() = " << s.front() << endl;
    cout << "s.back() = " << s.back() << endl;

    cout << "s[18] is undefined behavior: " << s[18] << endl;
    try
    {
        cout << s.at(18) << endl;
    }
    catch (std::out_of_range const &e) {
        cout << "s.at(18) throws: " << e.what() << endl;
    }
}

void convert_c_strings()
{
    /*
     *  const char* string::c_str () const
        const char* string::data () const
        • Returns the contents of the string as a character array, including a trailing end-of-string character
          ’\0’. Thus, this is a valid C-string for strings.
        • The return value is owned by the string. Thus, the caller must neither modify nor free or delete
          the return value.
        • The return value is valid only as long as the string exists and as long as only constant functions
          are called for it.
        • Before C++11, the return value of data() was guaranteed to contain all characters of the string
          without any trailing ’\0’ character. Thus, the return value of data() was not a valid C-string.

        size_type string::copy (char* buf, size_type buf_size) const
        size_type string::copy (char* buf, size_type buf_size, size_type idx) const
        • Both forms copy at most buf_size characters of the string (beginning with index idx, if passed)
          into the character array buf.
        • They return the number of characters copied.
        • No null character is appended. Thus, the contents of buf might not be a valid C-string after the call.
     */
    string s("Huang Fan");
    printf("s: %s\n", s.c_str());

    char buffer[9];
    s.copy(buffer, 8);
    buffer[8] = '\0'; //make it a valid C-string
    printf("buffer: %s\n", buffer);
}

void modify_operations()
{
    /*
     * -- Assignments --
     *  string& string::operator = (const string& str)
        string& string::assign (const string& str)
        • Copy assignment operator.

        string& string::operator = (string&& str)
        string& string::assign (string&& str)
        • Move assignment operator.

        string& string::assign (const string& str, size_type str_idx, size_type str_num)
        • Assigns at most str_num characters of str, starting with index str_idx.

        string& string::assign (const char* cstr)
        string& string::assign (const char* chars, size_type chars_len)
        string& string::assign (size_type num, char c)
        string::assign (InputIterator beg, InputIterator end)

        string& string::operator = (initializer-list)
        string& string::assign (initializer-list)

        void string::swap (string& str)
        void swap (string& str1, string& str2)
     */
    string s = "Huang Fan";
    string s2 = s;

    string s3;
    s3.assign(s);

    string s4;
    s4.assign(s, 2, 3);
    cout << "s4: " << s4 << endl;

    string s5;
    s5.assign(s2.cbegin(), s2.cbegin() + 5);
    cout << "s5: " << s5 << endl;

    /*
     * -- Appending characters --
     *  string& string::operator += (const string& str)
        string& string::append (const string& str)

        string& string::append (const string& str, size_type str_idx, size_type str_num)
        string& string::operator += (const char* cstr)
        string& string::append (const char* cstr)
        string& string::append (const char* chars, size_type chars_len)
        string& string::append (size_type num, char c)

        string& string::operator += (char c)
        void string::push_back (char c)

        string& string::append (InputIterator beg, InputIterator end)

        string& string::operator += (initializer-list)
        void string::append (initializer-list)

        -- Inserting characters --
        string& string::insert (size_type idx, const string& str)
        string& string::insert (size_type idx, const string& str,
            size_type str_idx, size_type str_num)
        string& string::insert (size_type idx, const char* cstr)
        string& string::insert (size_type idx, const char* chars, size_type chars_len)
        string& string::insert (size_type idx, size_type num, char c)

        iterator string::insert (const_iterator pos, size_type num, char c)
        - Note that the overloading of these two functions results in a possible ambiguity. If you pass 0 as
          the first argument, it can be interpreted as an index, which is typically a conversion to unsigned,
          or as an iterator, which is often a conversion to char*. In this case, you should pass an index
          with its the exact type. For example:
            std::string s;
            ...
            s.insert(0,1,’ ’);  // ERROR: ambiguous
            s.insert((std::string::size_type)0,1,’ ’); // OK

        iterator string::insert (const_iterator pos, char c)
        iterator string::insert (const_iterator pos,
            InputIterator beg, InputIterator end)
        iterator string::insert (const_iterator pos, initializer-list)

        -- Erasing characters --
        void string::clear ()
        string& string::erase ()
        • Both functions delete all characters of the string. Thus, the string is empty after the call.

        string& string::erase (size_type idx)
        string& string::erase (size_type idx, size_type len)
        iterator string::erase (const_iterator pos)
        iterator string::erase (const_iterator beg, const_iterator end)
        void string::pop_back ()
     */

    /*
     *  void string::resize (size_type num)
        void string::resize (size_type num, char c)
        • Both forms change the number of characters of *this to num. Thus, if num is not equal to
          size(), they append or remove characters at the end according to the new size.
        • If the number of characters increases, the new characters are initialized by c. If c is missing, the
          characters are initialized by the default constructor of the character type (for string: ’\0’).
        • Both forms throw length_error if num is equal to string::npos.
     */
    string str("Huang Fan");
    cout << "original str: " << str << endl;
    str.resize(5);
    cout << "resize to 5: " << str <<endl;

    str.resize(15);
    cout << "resize to 15 with empty chars append: " << str << endl;

    str.resize(20, 'L');
    cout << "resize again to 20 with \'L\' filled: " << str << endl;
    cout << str.length() << endl;

    /*
     *  string& string::replace (size_type idx, size_type len, const string& str)
        string& string::replace (begin_iterator beg, begin_iterator end, const string& str)
        • The first form replaces at most len characters of *this, starting with index idx, with all characters of str.

        string& string::replace (size_type idx, size_type len, const string& str, size_type str_idx, size_type str_num)
        string& string::replace (size_type idx, size_type len, const char* cstr)
        string& string::replace (const_iterator beg, const_iterator end, const char* cstr)

        ...略过 replace的重载函数的签名与append和assign基本上一样
     */
}

void searching_and_finding()
{
    /*
     *  size_type string::find (char c) const
        size_type string::find (char c, size_type idx) const
        size_type string::rfind (char c) const
        size_type string::rfind (char c, size_type idx) const
        • These functions search for the first/last character c (starting at index idx).
        • The find() functions search forward and return the first substring.
        • The rfind() functions search backward and return the last substring.
        • These functions return the index of the character when successful or string::npos if they fail.

        Find a Substring
        size_type string::find (const string& str) const
        size_type string::find (const string& str, size_type idx) const
        size_type string::rfind (const string& str) const
        size_type string::rfind (const string& str, size_type idx) const

        size_type string::find (const char* cstr) const
        ...

        Find First of Different Characters
        size_type string::find_first_of (const string& str)
        size_type string::find_first_of (const string& str, size_type idx) const
        size_type string::find_first_not_of (const string& str) const
        size_type string::find_first_not_of (const string& str, size_type idx) const
        • These functions search for the first character that is or is not also an element of the string str
          (starting at index idx).
        • These functions return the index of that character or substring when successful or string::npos
          if they fail

        size_type string::find_first_of (const char* cstr) const
        ...
        size_type string::find_first_of (char c) const
        ...

        Find Last of Different Characters
        size_type string::find_last_of (const string& str) const
        size_type string::find_last_of (const string& str, size_type idx) const
        size_type string::find_last_not_of (const string& str) const
        size_type string::find_last_not_of (const string& str, size_type idx) const

        ...
     */

    string s("Huang Fan");
    cout << "first n in pos: " << s.find('n') << endl;
    cout << "last n in pos: " << s.rfind('n') << endl;
    cout << "first n starting from 5 in pos: " << s.find('n', 5) << endl;

    cout << "first \"an\" in pos: " << s.find("an") << endl;

    cout << "first char in \"uvw\" is pos: " << s.find_first_of("uvw") << endl;

    /*
     *  string string::substr () const
        string string::substr (size_type idx) const
        string string::substr (size_type idx, size_type len) const
     */
    cout << "s.substr(5): " << s.substr(5) << endl;
    cout << "s.substr(0, 5): " << s.substr(0, 5) << endl;
}

void numeric_conversions()
{
    /*
     *  int stoi (const string& str, size_t* idxRet = nullptr, int base = 10)
        long stol (const string& str, size_t* idxRet = nullptr, int base = 10)
        unsigned long stoul (const string& str, size_t* idxRet = nullptr, int base = 10)
        long long stoll (const string& str, size_t* idxRet = nullptr, int base = 10)
        unsigned long long stoull (const string& str, size_t* idxRet = nullptr, int base = 10)
        float stof (const string& str, size_t* idxRet = nullptr, int base = 10)
        double stod (const string& str, size_t* idxRet = nullptr, int base = 10)
        long double stold (const string& str, size_t* idxRet = nullptr, int base = 10)
        • Convert str to the corresponding return type.
        • str might be a string of type string or wstring.
        • Skip leading whitespace.
        • If idxRet!=nullptr, it returns the index of the first character not processed for the conversion.
        • base allows you to specify a base number.
        • Might throw std::invalid_argument if no conversion is possible and std::out_of_range
          if the converted value is outside the range of representable values for the return type.

        string to_string (Type val)
        wstring to_wstring (Type val)
        • Converts val to a string or wstring.
        • Valid types for val are int, unsigned int, long, unsigned long, long long, unsigned
          long long, float, double, or long double
     */
    double d = stod("6.789");
    cout << "d = " << d << endl;

    size_t idxRet;
    double d2 = stod("6.789SSS", &idxRet);
    cout << "d2 = " << d2 << endl;
    cout << "idxRet: " << idxRet << endl; //从第五个位置开始字符变为S，不能转化为double数值

    try {
        cout << stod("SSSS") << endl;
    }
    catch (std::invalid_argument const &e) {
        cout << "stod(\"SSSS\") fail: " << e.what() << endl;
    }

    try {
        int a = stoi("1234567899999");
    }
    catch (std::out_of_range const &e) {
        cout << "stoi(\"1234567899999\") fail: " << e.what() << endl;
    }
}

void Run()
{
    create_and_copy();
    size_and_capacity();
    comparisons();
    element_access();
    convert_c_strings();
    modify_operations();
    searching_and_finding();
    numeric_conversions();
}

}
}