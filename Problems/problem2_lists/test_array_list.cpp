#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "array_list.hpp"

// force class expansion
template class ArrayList<int>;

// try this to get indexing instruction clarified
TEST_CASE("Lists: Test 1-indexing Corner Cases", "[ArrayList]")
{
  ArrayList<int> list;
  REQUIRE(list.isEmpty());

  REQUIRE_FALSE(list.insert(0, 0)); // invalid
  REQUIRE(list.isEmpty());          // still empty

  REQUIRE(list.insert(1, 1));     // valid
  REQUIRE(list.getLength() == 1); // length is 1

  REQUIRE_FALSE(list.remove(0));  // invalid
  REQUIRE(list.getLength() == 1); // length is still 1

  REQUIRE(list.remove(1)); // valid
  REQUIRE(list.isEmpty()); // now empty

  list.insert(1, 301);
  list.insert(2, 302);

  REQUIRE(list.getEntry(1) == 301);
  REQUIRE(list.getEntry(2) == 302);

  REQUIRE_THROWS_AS(list.getEntry(0), std::out_of_range);
  REQUIRE_THROWS_AS(list.setEntry(0, 300), std::out_of_range);

  // pos = 1 is the first item, that also indicates pos = n is the last item
  // your insertion at pos=n is valid, and your insertion at pos=n+1 is also valid
  // your removal at pos=1 is valid, but your removal at pos=n+1 is invalid
}