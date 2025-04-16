#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "Database.hpp"

/* All test cases used on Gradescope will be provided here later

You don't need to write any test cases for submission purposes.

But your submission to gradescope is conditional on passing majority unit test cases locally
 and upon a clear understanding of all the code you write via OHs meeting, during which
 we not only verify the integrity of your code, but also help you!

After that, you will have the access to Gradescope submission link (by the due date) to earn points.

*/

// struct used just for testing
struct TestEntryBook
{
    std::string title;
    std::string author;
    int pubYear;
    bool operator==(const TestEntryBook &e) const
    {
        return (title == e.title) && (author == e.author) && (pubYear == e.pubYear);
    };
};

// struct used just for testing
struct TestEntryStudent
{
    std::string peopleSoftID;
    std::string login_username;
    double gpa;
    bool operator==(const TestEntryStudent &e) const
    {
        return (peopleSoftID == e.peopleSoftID) && (login_username == e.login_username) && (gpa == e.gpa);
    };
};

/* Initial provided test cases */
TEST_CASE("Test Add and Contains", "[add]")
{
    Database<std::string> testdb;
    std::string e1 = "entry";

    REQUIRE(testdb.isEmpty());
    REQUIRE(testdb.add("key1", "key2", e1));
    REQUIRE_FALSE(testdb.isEmpty());
    REQUIRE(testdb.contains("key1"));
    REQUIRE(testdb.contains("key2"));
}

TEST_CASE("Test getValue", "[retrieve]")
{
    Database<std::string> testdb;
    std::string e1 = "entry";

    testdb.add("key1", "key2", e1);

    REQUIRE(testdb.getValue("key1") == e1);
    REQUIRE(testdb.getValue("key2") == e1);
}

TEST_CASE("Test Remove", "[remove]")
{
    Database<std::string> testdb;
    std::string e1 = "entry";

    testdb.add("key1", "key2", e1);

    testdb.remove("key1");
    REQUIRE(!testdb.contains("key1"));
    REQUIRE(!testdb.contains("key2"));

    testdb.add("key1", "key2", e1);

    testdb.remove("key2");
    REQUIRE(!testdb.contains("key1"));
    REQUIRE(!testdb.contains("key2"));

    REQUIRE(testdb.isEmpty());
}

TEST_CASE("Test Copy", "[copy]")
{
    Database<std::string> testdb;
    std::string e1 = "entry";

    testdb.add("key1", "key2", e1);

    Database<std::string> testdb_copy(testdb);

    testdb.clear();

    REQUIRE(testdb_copy.getValue("key1") == e1);
    REQUIRE(testdb_copy.getValue("key2") == e1);

    Database<std::string> testdb2;

    testdb2.add("key1", "key2", e1);

    Database<std::string> testdb2_copy;

    testdb2_copy = testdb2;

    testdb2.clear();

    REQUIRE(testdb2_copy.getValue("key1") == e1);
    REQUIRE(testdb2_copy.getValue("key2") == e1);
}

TEST_CASE("TestEntryBook Type", "[entry type]")
{
    Database<TestEntryBook> testdb;

    TestEntryBook e1;
    std::string isbn1 = "000-0-00-000000-1";
    std::string catalog_id1 = "0000001";
    e1.title = "The Winds of Winter";
    e1.author = "George R. R. Martin";
    e1.pubYear = 2051;

    testdb.add(isbn1, catalog_id1, e1);

    TestEntryBook e2;

    std::string isbn2 = "000-0-00-000000-2";
    std::string catalog_id2 = "0000002";
    e2.title = "A Dream of Spring";
    e2.author = "George R. R. Martin";
    e2.pubYear = 2052;

    testdb.add(isbn2, catalog_id2, e2);

    // TODO
}
