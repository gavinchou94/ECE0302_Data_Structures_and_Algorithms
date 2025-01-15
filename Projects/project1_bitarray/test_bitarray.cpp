#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include <iostream>
#include "bitarray.hpp"

TEST_CASE( "Bitarray: Test default construction", "[bitarray]" ) {

    BitArray b;  
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
}

TEST_CASE( "Bitarray: Test construction with asString", "[bitarray]" ) {
    BitArray b;
    REQUIRE(b.asString().compare("00000000") == 0);
}

TEST_CASE( "Bitarray: Test construction size", "[bitarray]" ) {
    BitArray b(64);
    std::string s(64, '0');
    REQUIRE(b.size() == 64);
    REQUIRE(b.good());
}

TEST_CASE( "Bitarray: Test construction string", "[bitarray]" ) {
    std::string s("00101110000011000001101000001");
    BitArray b(s);
    REQUIRE(b.size() == s.size());
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE( "Bitarray: Test construction invalid string", "[bitarray]" ) {
    std::string s("00101110000011002001101000001");
    BitArray b(s);
    REQUIRE_FALSE(b.good());
}

TEST_CASE( "Bitarray: Test set", "[bitarray]" ) {
    std::string s("00010001");
    BitArray b;
    b.set(3);
    b.set(7);
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE( "Bitarray: Test set with size init", "[bitarray]" ) {
    std::string s("00010");
    BitArray b(5);
    b.set(3);
    REQUIRE(b.size() == 5);
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE( "Bitarray: Test combined", "[bitarray]" ) {
    std::string s((1<<15) + 3, '0');
    BitArray b(s);
    REQUIRE(b.size() == s.size());
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);

    for (int i = 1; i < (1<<10); i++) {
        b.set(i);
        b.reset(i + (1<<10));
        b.toggle(i + (1<<11));
        REQUIRE(b.good());
        REQUIRE(b.test(i));
        REQUIRE_FALSE(b.test(i + (1<<10)));
        REQUIRE(((b.test(i + (1<<11)) == true && s.at(i + (1<<11)) == '0') || (b.test(i + (1<<11)) == false && s.at(i + (1<<11)) == '1')));
    }
}
