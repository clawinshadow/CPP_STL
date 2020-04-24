#include "bitsets_.h"

#include <bitset>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

namespace special_containers {
namespace bitsets_ {

void sets_of_flags()
{
    /*
     * -- Using Bitsets as Sets of Flags --
     */

    // enumeration type for the bits
    // - each bit represents a color
    enum Color { red, yellow, green, blue, white, black, numColors };

    bitset<numColors> usedColors;
    // set bits for two colors
    usedColors.set(red);
    usedColors.set(green);

    // print some bitset data
    // 注意打印出来的是 000101， 这个要从右往左看，red在枚举中的第一位，那么最右边一个bit就是1
    // 同理green在第三位，那么从右往左第三位就是1
    cout << "bitfield of used colors: " << usedColors << endl;
    cout << "number of used colors: " << usedColors.count() << endl;
    cout << "bitfield of unused colors: " << ~usedColors << endl;

    // if any color is used
    if (usedColors.any()) {
        // loop over all colors
        for (int c = 0; c < numColors; ++c) {
            // if the actual color is used
            if (usedColors[(Color)c]) {
                cout << "color " << c << " is used."<< endl;
            }
        }
    }
}

void binary_conversion()
{
    /*
     * -- Using Bitsets for I/O with Binary Representation --
     */
    cout << "267 as binary short: "
         << bitset<numeric_limits<unsigned short>::digits>(267) << endl;

    cout << "267 as binary long: "
         << bitset<numeric_limits<unsigned long>::digits>(267) << endl;

    cout << "10,000,000 with 24 bits: "
         << bitset<24>(1e7) << endl;

    // write binary representation into string
    string s = bitset<42>(12345678).to_string();
    cout << "12,345,678 with 42 bits: " << s << endl;

    // transform binary representation into integral number
    cout << "\"1000101011\" as number: "
         << bitset<100>("1000101011").to_ullong() << endl;
}

void Run()
{
    /*
     * Bitsets model fixed-sized arrays of bits or Boolean values. They are useful to manage sets of flags,
       where variables may represent any combination of flags
       Note that you can’t change the number of bits in a bitset. The number of bits is the template
       parameter. If you need a container for a variable number of bits or Boolean values, you can use the
       class vector<bool>

     */
    sets_of_flags();
    binary_conversion();
}

}
}
