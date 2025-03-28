// This is the test_templates1.cpp
// changes from test_templates.cpp:
// 1. adding more testing cases for SafeArray
// 2. copying from previous project testing cases for inheritance and redefine/override

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "SafeArray.hpp"
#include "SearchableArray1.hpp"
#include "UniqueArray1.hpp"

TEST_CASE("Test default construction of SafeArray", "[template]") {
    SafeArray<int> arr;
    REQUIRE(arr.get_size() == 0);
}

TEST_CASE("Test SafeArray size construction and access using get/set", "[template]") {
    int size = 5;
    SafeArray<int> arr(size);

    REQUIRE(arr.get_size() == size);
    for (int i=0; i<size; i++) {
        arr.set(i, i);
        REQUIRE(arr.get(i) == i);
    }

    REQUIRE_THROWS_AS(arr.get(size), std::out_of_range);
    REQUIRE_THROWS_AS(arr.set(size,0), std::out_of_range);
}

TEST_CASE("Test inheritance and search", "[template]") {
    int size = 5;
    SearchableArray arr(size);

    REQUIRE(arr.get_size()==5);

    for (int i=0; i<size; i++){
        arr.set(i,i);                  // inherited from base class 
        REQUIRE(arr.get(i)==i);        // inherited from base class
        REQUIRE(arr.search(i));        // derived class method
    }

    REQUIRE_FALSE(arr.search(-2));     // derived class method
    REQUIRE_THROWS_AS(arr.set(10, 10), std::out_of_range); // inherited from base class
}

TEST_CASE("Test inheritance and redefine/override", "[template]") {
    int size = 5;
    UniqueArray uarr(size);

    REQUIRE(uarr.get_size()==5);

    for (int i=0; i<size; i++){
        // set uarr to be [1,2,3,4,5]
        uarr.set(i,i+1);                // overridden set functions
        REQUIRE(uarr.get(i)==i+1);      // test success of overriding
    }

    //arr[0]=5 would trigger exception since arr[4]=5
    REQUIRE_THROWS_AS(uarr.set(0, 5), std::logic_error);
    REQUIRE_NOTHROW(uarr.set(0, -2));   //arr[0]=-2 is okay
    REQUIRE(uarr.get(0)==-2);

    // these following 3 lines demonstrates dynamic binding
    // delete "virtual" at Line 27 of SafeArray3.hpp and try it again
    SafeArray<int> *sa_ptr = new UniqueArray(2);
    sa_ptr->set(0, 100);
    //REQUIRE_THROWS_AS(sa_ptr->set(1, 100), std::logic_error);
}