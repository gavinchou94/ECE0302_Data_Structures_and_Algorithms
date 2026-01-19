#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include <iostream>
#include "bitarray.hpp"

// Given test cases for BitArray class
TEST_CASE("Bitarray: Test default construction and asString", "[bitarray]")
{
    BitArray b;
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
    // std::string class has compare() member function that returns 0 if the strings are equal
    // research online for more details
    REQUIRE(b.asString().compare("00000000") == 0);
}

TEST_CASE("Bitarray: Test construction with asString", "[bitarray]")
{
    BitArray b;
    REQUIRE(b.asString().compare("00000000") == 0);
}

TEST_CASE("Bitarray: Test construction size and asString", "[bitarray]")
{
    // You can construct a string s of as s(n, c)
    // where n is the number of characters and c is the character
    std::string s(64, '0');
    BitArray b(64);
    REQUIRE(b.size() == 64);
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE("Bitarray: Test many given methods combined", "[bitarray]")
{
    // << is the left shift operator for integers
    // e.g., 1 << 8 is 2^8=256, 1<<15 is 2^15=32768
    std::string s((1 << 15), '0'); // string of many-many zeros
    BitArray b(s);
    REQUIRE(b.size() == s.size());
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);

    // Test a very long BitArray by setting, resetting, toggling, and testing bits
    for (int i = 1; i < (1 << 10); i++)
    {
        REQUIRE(b.good());

        b.set(i);                // set first 1..1023 bits to 1
        b.reset(i + (1 << 10));  // reset bits 1025..2047 to 0
        b.toggle(i + (1 << 11)); // toggle bits 2049..3071

        REQUIRE(b.test(i));
        REQUIRE_FALSE(b.test(i + (1 << 10)));
        REQUIRE((
            (b.test(i + (1 << 11)) == true && s.at(i + (1 << 11)) == '0') || // either this is true
            (b.test(i + (1 << 11)) == false && s.at(i + (1 << 11)) == '1')   // or this is true
            ));
    }
}

// Write your own test cases below