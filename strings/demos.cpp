#include "demos.h"
#include "details.h"

#include <iostream>

using namespace std;

namespace strings {

void Demos()
{
    /*
     * I use the term string for objects of one of the string types in the C++ standard library:
       string, wstring, u16string, or u32string.
       For “ordinary strings” of type char* or const char*, I use the term C-string.

       C++11中给string提供的新特性：
        • Strings now provide front() and back() to access the first or last element
          and shrink_to_fit() to shrink capacity.
        • Strings now provide convenience functions to convert strings to numeric values and vice versa
        • data() and c_str() no longer invalidate references, iterators, and pointers to strings
        • Strings now support move semantics and initializer lists
        • Besides string and wstring, the basic_string<> specializations u16string and u32string
          are predefined now
        • Strings are now indirectly required to provide an end-of-string character (’\0’ for string)
          because for a string s, s[s.length()] is always valid and s.data() returns the characters
          including a trailing end-of-string character
     */
    cout << "demos of string" << endl;

    details::Run();
}

}