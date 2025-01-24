/** @file test_bag.cpp
 * @author Frank M. Carrano, Tim Henry
 * @copyright 2017 Pearson Education
 * @version 2.0, modified in 2025 by G. Zhou for ECE0302
 */

#define CATCH_CONFIG_MAIN

#include <string>
#include "ArrayBag.hpp"
#include "catch.hpp"

TEST_CASE("Test initial bag is empty", "[ArrayBag]")
{
    ArrayBag<std::string> bag;
    REQUIRE(bag.isEmpty() == true);
    REQUIRE(bag.getCurrentSize() == 0);
}

TEST_CASE("Test getCurrentSize method", "[ArrayBag]")
{
    ArrayBag<std::string> bag;
    REQUIRE(bag.getCurrentSize() == 0);
    bag.add("milk");
    REQUIRE(bag.getCurrentSize() == 1);
}

TEST_CASE("Test add method", "[ArrayBag]")
{
    ArrayBag<std::string> bag;
    REQUIRE(bag.add("milk") == true);
    REQUIRE(bag.add("bread") == true);
    REQUIRE(bag.getCurrentSize() == 2);
}

TEST_CASE("Test add method more", "[ArrayBag]")
{
    // something related to add method is not tested, what's it?
}

// Comment since remove() is a stub
// TEST_CASE("Test remove method", "[ArrayBag]") {
//     ArrayBag<std::string> bag;
//     bag.add("milk");
//     bag.add("bread");
//     REQUIRE(bag.remove("milk"));
//     REQUIRE(bag.getCurrentSize() == 1);
//     REQUIRE_FALSE(bag.remove("eggs"));
//     REQUIRE_FALSE(bag.contains("milk"));
//     REQUIRE(bag.contains("bread"));
// }

TEST_CASE("Test clear method", "[ArrayBag]")
{
    ArrayBag<std::string> bag;
    bag.add("milk");
    bag.add("bread");
    bag.clear();
    // clear() is now still a stub
    // but what one REQUIRE statement can you write to test it if clear() is completed?
}

TEST_CASE("Test getFrequencyOf method", "[ArrayBag]")
{
    ArrayBag<std::string> bag;
    bag.add("milk");
    bag.add("bread");
    bag.add("milk");
    for (int i = 0; i < 10; i++)
    {
        bag.add("orange");
    }
    bag.add("apple");
    REQUIRE(bag.getFrequencyOf("milk") == 2);
    REQUIRE(bag.getFrequencyOf("bread") == 1);
    // REQUIRE(bag.getFrequencyOf("orange") == ?); // TODO
}

TEST_CASE("Test getFrequencyOf method failed", "[ArrayBag]")
{
    ArrayBag<std::string> bag;
    bag.add("ice cream");
    // REQUIRE_NOTHROW(??); // TODO
    // REQUIRE_THROWS_AS(??); // TODO
}

// Buy more items as per discount (0-1)
// if discount is greater than 0.5, buy 2 more items
// if discount is less than 0.5, buy 1 more item
void buy_more_on_discount(ArrayBag<std::string> &bag, std::string item, double discount)
{

    if (discount > 1 || discount < 0)
    {
        throw std::logic_error("Discount must be between 0 and 1");
    }
    if (!bag.contains(item))
    {
        throw std::invalid_argument("Item not found in bag");
    }
    if (discount > 0.5)
    {
        bag.add(item);
        bag.add(item);
    }
    else
    {
        bag.add(item);
    }
}

TEST_CASE("Test buy_more_on_discount method", "[ArrayBag]")
{
    ArrayBag<std::string> bag;
    bag.add("milk");
    bag.add("bread");
    buy_more_on_discount(bag, "milk", 0.6);
    REQUIRE(bag.getFrequencyOf("milk") == 3);
    buy_more_on_discount(bag, "bread", 0.4);
    REQUIRE(bag.getFrequencyOf("bread") == 2);

    // REQUIRE_THROWS_AS(buy_more_on_discount(bag, "eggs", 0.5), ?); // TODO
    // REQUIRE_THROWS_AS(buy_more_on_discount(bag, "milk", -1), ?); // TODO
}

TEST_CASE("Test contains method", "[ArrayBag]")
{
    ArrayBag<std::string> bag;
    bag.add("milk");
    bag.add("bread");
    REQUIRE(bag.contains("milk"));
    REQUIRE_FALSE(bag.contains("eggs"));
}

TEST_CASE("Test replace method", "[ArrayBag]")
{
    ArrayBag<std::string> bag;
    bag.add("milk");
    bag.add("bread");
    REQUIRE(bag.replace("milk", "eggs"));
    REQUIRE_FALSE(bag.contains("milk"));
    REQUIRE(bag.contains("eggs"));
    REQUIRE_FALSE(bag.replace("apple", "banana"));
}

bool external_replace(ArrayBag<std::string> &bag, std::string oldEntry, std::string newEntry)
{
    // implement a non-member function to replace oldEntry with newEntry in bag
    return false;
}

TEST_CASE("Test toVector method", "[ArrayBag]")
{
    ArrayBag<std::string> bag;
    bag.add("milk");
    bag.add("bread");
    std::vector<std::string> vec = bag.toVector();
    REQUIRE(vec.size() == 2);
    REQUIRE(vec[0] == "milk");
    REQUIRE(vec[1] == "bread");
    bag.add("eggs");
    vec = bag.toVector();
    REQUIRE(vec.size() == 3);
    REQUIRE(vec[2] == "eggs");
}