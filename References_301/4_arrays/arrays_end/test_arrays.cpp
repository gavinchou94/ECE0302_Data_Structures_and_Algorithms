// This is final version of test_arrays.cpp, clear comments in test_arrays_7.cpp

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "arrays.hpp"
#include "constants.hpp"

TEST_CASE("Test array indexing", "[array-index]")
{
    // int arr[]; // not allowed, size is not specified
    // int arr[] = {0,10,20,30,40}; // Size is inferred
    // int arr[4] = {0,10,20,30,40}; // bad example, mismatched
    // int arr[5]; // valid but uninitialized
    int arr[5] = {0, 10, 20, 30, 40}; // make sure to match size

    // Another way to test indexing using for-loop
    for (int i = 0; i < 5; i++)
    {
        REQUIRE(arr[i]==10*i);
    }

    //int test = arr[5]; // test access out of bounds
}

TEST_CASE("Test array printing", "[array-printing]")
{
    // int dim=5; int arr[dim]={0,10,20,30,40}; //variable-sized object may not be initialized
    const int size = 5; // size has to be a const int
    int arr[size] = {0, 10, 20, 30, 40};

    display(arr, size);

    //std::cout << arr[5] << std::endl; // print out-of-bounds array element
}

TEST_CASE("Test array addressing", "[array-addressing]")
{
    const int size = 5;
    int arr[size] = {0, 10, 20, 30, 40};

    // let's take a look at how arr is stored in memory
    std::cout << arr << std::endl;        // print a hexadecimal addr for first element, supposing X
    std::cout << arr[0] << std::endl;     // print the first element, which is 0
    std::cout << &arr[0] << std::endl;    // print the addr of the first element, '&' is the addr symbol, shall be X
    std::cout << arr[1] << std::endl;     // print the second element, which is 10
    std::cout << &arr[1] << std::endl;    // print the addr of the second element, shall be X+4 (since size(int)=4)

    double arr_d[2] = {10.0, 20.0};
    std::cout << &arr_d[0] << " " << &arr_d[1] << std::endl; // print two address

    // std::cout << arr[8] <<std::endl;   // arr[8] won't give error, but arr[8] accesses data that is illegal
}

TEST_CASE("Test array swap", "[array-swap]")
{
    const int size = 5;
    int arr[size] = {0, 10, 20, 30, 40};

    int index_1 = 2;
    int index_2 = 3;
    int old_value1 = arr[index_1];
    int old_value2 = arr[index_2];

    // a swap function that should exchange two elements in an array
    swap(arr, index_1, index_2);

    // array object, even not pass by reference (with & symbol), is still updated outside function scope
    // since array is stored as an address in memory
    REQUIRE(arr[index_1]==old_value2);
    REQUIRE(arr[index_2]==old_value1);
}

TEST_CASE("Test string swap", "[string-swap]")
{
    std::string my_string = "from";

    int index_1 = 1;
    int index_2 = 2;

    swap(my_string, index_1, index_2);

    REQUIRE(my_string=="form");
}

TEST_CASE("Test array copy", "[array-copy]")
{
    const int size = 5;
    int arr[size] = {0, 10, 20, 30, 40};

    int arrcopy[size]; // valid but uninitialized

    // a copy function that expects to copy arr[] to arrcopy[], with size
    copy(arr, arrcopy, size);

    for (int i = 0; i < size; i++)
    {
        REQUIRE(arrcopy[i]==arr[i]);
    }

    // remember arr[] object itself is an address, the copy's address shall be different
    REQUIRE_FALSE(arrcopy==arr);
}

TEST_CASE("Test array linear search", "[array-search]")
{
    const int size = 5;
    int arr[size] = {0, 10, 20, 30, 40};

    int val = 40;
    int not_found = 80;

    REQUIRE(search(arr, val, size));
    REQUIRE_FALSE(search(arr, not_found, size));
}

TEST_CASE("Test 2d array (mat) linear search", "[2d-array-search]")
{
    const int rows = 2;
    // define a constant COLS for all 2d array, i.e., the maximum number of columns the array can allow
    int mat[rows][COLS] = {{0, 10, 20, 30, 40}, {50, 60, 70, 80, 90}};

    int val = 40;
    int not_found = 110;

    //call a 2d array search, where search is conducted at each element (nested for-loop)
    REQUIRE(search2D(mat, val, rows));
    REQUIRE_FALSE(search2D(mat, not_found, rows));
}

// the test case for binary search looks the same as the one for linear search
// the functionality is the same, but the implementation of binary search is more efficient
// assuming you have sorted data
TEST_CASE("Test binary search", "[bi-search]")
{
    const int size = 10;
    int arr[size];
    for (int i=0; i<size; i++)
    {
        arr[i] = i*10;
    }

    int val = 40;
    int notfound = 110;

    // binary search that needs to specify array, look-up value, and search range
    REQUIRE(binary_search(arr, val, 0, size));
    REQUIRE_FALSE(binary_search(arr, notfound, 0, size));
    // add break point in REQUIRE and in binary_search for call stack times check
}