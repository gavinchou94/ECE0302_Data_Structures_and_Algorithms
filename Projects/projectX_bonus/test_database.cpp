#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "Database.hpp"
#include "list.hpp"
#include <cstdlib>

/* All test cases used on Gradescope will be provided here later

You don't need to write any test cases for submission purposes.

But your submission to gradescope is conditional on passing at least 14 unit test cases locally
 and upon a clear understanding of all the code you write via OHs meeting, during which
 we not only verify the integrity of your code, but also help you!

After that, you will have the access to Gradescope submission link (by the due date) to earn points.
Up to 50 pts, that is 2% of your final grade. (50/1000 in project category) * 40%

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

TEST_CASE("DB: Test Add and Contains", "[add]")
{
    Database<std::string> testdb;
    std::string e1 = "entry";

    REQUIRE(testdb.isEmpty());
    REQUIRE(testdb.add("key1", "key2", e1));
    REQUIRE_FALSE(testdb.isEmpty());
    REQUIRE(testdb.contains("key1"));
    REQUIRE(testdb.contains("key2"));
}

TEST_CASE("DB: Test getValue", "[retrieve]")
{
    Database<std::string> testdb;
    std::string e1 = "entry";

    testdb.add("key1", "key2", e1);

    REQUIRE(testdb.getValue("key1") == e1);
    REQUIRE(testdb.getValue("key2") == e1);
}

TEST_CASE("DB: Test Remove", "[remove]")
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

TEST_CASE("DB: Test Copy", "[copy]")
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

TEST_CASE("DB: TestEntryBook Type", "[entry type]")
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
}

/* Solution test cases */
TEST_CASE("DB: Test add/getValue 2", "[add/getValue]")
{
    Database<std::string> testdb;
    std::string e1 = "entry1";
    std::string e2 = "entry2";

    testdb.add("key1a", "key1b", e1);
    testdb.add("key2a", "key2b", e2);

    REQUIRE(testdb.getValue("key1a") == e1);
    REQUIRE(testdb.getValue("key1b") == e1);
    REQUIRE(testdb.getValue("key2a") == e2);
    REQUIRE(testdb.getValue("key2b") == e2);
}

TEST_CASE("DB: Test Duplicate Add", "[duplicate add]")
{
    Database<std::string> testdb;
    std::string e1 = "entry";

    REQUIRE(testdb.add("key1", "key2", e1));
    REQUIRE(testdb.contains("key1"));
    REQUIRE(testdb.contains("key2"));
    REQUIRE(testdb.getNumberOfEntries() == 1);

    REQUIRE_FALSE(testdb.add("key1", "key2", e1));
    REQUIRE(testdb.contains("key1"));
    REQUIRE(testdb.contains("key2"));
    REQUIRE(testdb.getNumberOfEntries() == 1);
}

TEST_CASE("DB: Test getNumEntries", "[getNumEntries]")
{
    Database<std::string> testdb;

    testdb.add("key1a", "key2a", "entry1");
    REQUIRE(testdb.getNumberOfEntries() == 1);

    testdb.add("key1b", "key2b", "entry2");
    REQUIRE(testdb.getNumberOfEntries() == 2);
}

// expanded from starter code
TEST_CASE("DB: TestEntryBook Type 2", "[entry type]")
{
    Database<TestEntryBook> testdb;

    TestEntryBook e1;
    std::string isbn1 = "000-0-00-000000-1";
    std::string catalog_id1 = "0000001";
    e1.title = "The Winds of Winter";
    e1.author = "George R. R. Martin";
    e1.pubYear = 2031;

    testdb.add(isbn1, catalog_id1, e1);

    TestEntryBook e2;
    std::string isbn2 = "000-0-00-000000-2";
    std::string catalog_id2 = "0000002";
    e2.title = "A Dream of Spring";
    e2.author = "George R. R. Martin";
    e2.pubYear = 2032;

    testdb.add(isbn2, catalog_id2, e2);

    REQUIRE(testdb.getValue(isbn1) == e1);
    REQUIRE(testdb.getValue(catalog_id1) == e1);
    REQUIRE(testdb.getValue(isbn2) == e2);
    REQUIRE(testdb.getValue(catalog_id2) == e2);

    REQUIRE(testdb.remove(isbn1));
    REQUIRE(!testdb.contains(catalog_id1));

    REQUIRE(testdb.remove(catalog_id2));
    REQUIRE(!testdb.contains(isbn2));

    REQUIRE(testdb.getNumberOfEntries() == 0);
}

TEST_CASE("DB: Test Clear", "[clear]")
{
    Database<std::string> testdb;

    testdb.add("key1a", "key2a", "entry1");
    testdb.add("key1b", "key2b", "entry2");
    REQUIRE_FALSE(testdb.isEmpty());
    REQUIRE(testdb.getNumberOfEntries() == 2);
    REQUIRE(testdb.contains("key1a"));
    REQUIRE(testdb.contains("key2a"));
    REQUIRE(testdb.contains("key1b"));
    REQUIRE(testdb.contains("key2b"));

    testdb.clear();

    REQUIRE(testdb.isEmpty());
    REQUIRE(testdb.getNumberOfEntries() == 0);
    REQUIRE_FALSE(testdb.contains("key1a"));
    REQUIRE_FALSE(testdb.contains("key2a"));
    REQUIRE_FALSE(testdb.contains("key1b"));
    REQUIRE_FALSE(testdb.contains("key2b"));
}

TEST_CASE("DB: Test Special Character Keys", "[special keys]")
{
    Database<std::string> testdb;

    // Add entries with special character keys
    REQUIRE(testdb.add("key@123", "key#456", "entry1"));
    REQUIRE(testdb.add("key$789", "key%000", "entry2"));

    // Ensure the entries are present
    REQUIRE(testdb.contains("key@123"));
    REQUIRE(testdb.contains("key#456"));
    REQUIRE(testdb.contains("key$789"));
    REQUIRE(testdb.contains("key%000"));

    // Retrieve the values
    REQUIRE(testdb.getValue("key@123") == "entry1");
    REQUIRE(testdb.getValue("key#456") == "entry1");
    REQUIRE(testdb.getValue("key$789") == "entry2");
    REQUIRE(testdb.getValue("key%000") == "entry2");

    // Remove an entry and ensure the other remains
    REQUIRE(testdb.remove("key@123"));
    REQUIRE_FALSE(testdb.contains("key@123"));
    REQUIRE_FALSE(testdb.contains("key#456"));
    REQUIRE(testdb.contains("key$789"));
    REQUIRE(testdb.contains("key%000"));
}

TEST_CASE("DB: Test Add Many", "[add many]")
{
    Database<int> testdb;

    for (int i = 0; i < 50; i++)
    {
        testdb.add("key" + std::to_string(i) + "a", "key" + std::to_string(i) + "b", i);
    }

    REQUIRE(testdb.getNumberOfEntries() == 50);

    REQUIRE(testdb.getValue("key21a") == 21);
    REQUIRE(testdb.getValue("key40b") == 40);

    REQUIRE(testdb.remove("key10a"));
    REQUIRE(testdb.remove("key35b"));

    REQUIRE(!testdb.remove("key10a"));
    REQUIRE(!testdb.remove("key35b"));

    REQUIRE(!testdb.contains("key10a"));
    REQUIRE(!testdb.contains("key10b"));

    REQUIRE(testdb.getNumberOfEntries() == 48);

    REQUIRE(testdb.getValue("key37a") == 37);
    REQUIRE(testdb.getValue("key2b") == 2);

    REQUIRE(testdb.add("key50a", "key50b", 50));
    REQUIRE(testdb.getValue("key50a") == 50);
    REQUIRE(testdb.getValue("key50b") == 50);

    REQUIRE(testdb.getNumberOfEntries() == 49);
}

TEST_CASE("DB: TestEntryStudent Type", "[entry type]")
{
    Database<TestEntryStudent> testdb;

    TestEntryStudent e1;
    std::string psid1 = "429001";
    std::string login1 = "abc123";
    e1.peopleSoftID = psid1;
    e1.login_username = login1;
    e1.gpa = 3.5;

    testdb.add(psid1, login1, e1);

    TestEntryStudent e2;
    std::string psid2 = "429002";
    std::string login2 = "acd134";
    e2.peopleSoftID = psid2;
    e2.login_username = login2;
    e2.gpa = 3.8;

    testdb.add(psid2, login2, e2);

    REQUIRE(testdb.getValue(psid1) == e1);
    REQUIRE(testdb.getValue(login1) == e1);
    REQUIRE(testdb.getValue(psid2) == e2);
    REQUIRE(testdb.getValue(login2) == e2);

    REQUIRE(testdb.remove(psid1));
    REQUIRE(!testdb.contains(login1));

    REQUIRE(testdb.remove(login2));
    REQUIRE(!testdb.contains(psid2));

    REQUIRE(testdb.getNumberOfEntries() == 0);
}

TEST_CASE("DB: Test on Empty Database", "[empty database]")
{
    Database<std::string> testdb;

    // Attempt to remove a key from an empty database
    REQUIRE_FALSE(testdb.remove("nonexistentKey"));

    // Attempt to retrieve a value from an empty database
    REQUIRE(testdb.getValue("nonexistentKey") == "");

    // Ensure the database is empty
    REQUIRE(testdb.isEmpty());
    REQUIRE(testdb.getNumberOfEntries() == 0);
}

TEST_CASE("DB: Test Adding Many Similar Keys", "[many similar keys]")
{
    Database<int> testdb;

    // Add entries with similar keys
    for (int i = 0; i < 100; i++)
    {
        REQUIRE(testdb.add("key" + std::to_string(i), "altKey" + std::to_string(i), i));
    }

    // Ensure all entries are present
    for (int i = 0; i < 100; i++)
    {
        REQUIRE(testdb.contains("key" + std::to_string(i)));
        REQUIRE(testdb.contains("altKey" + std::to_string(i)));
        REQUIRE(testdb.getValue("key" + std::to_string(i)) == i);
        REQUIRE(testdb.getValue("altKey" + std::to_string(i)) == i);
    }

    // Ensure the number of entries is correct
    REQUIRE(testdb.getNumberOfEntries() == 100);
}

TEST_CASE("DB: Test Sorted Entries", "[sorted entries]")
{
    Database<TestEntryBook> testdb;

    TestEntryBook e1;
    std::string isbn1 = "000-0-00-000000-1";
    std::string catalog_id1 = "0000100";
    e1.title = "The Winds of Winter";
    e1.author = "George R. R. Martin";
    e1.pubYear = 2031;

    testdb.add(isbn1, catalog_id1, e1);

    TestEntryBook e2;
    std::string isbn2 = "000-0-00-000000-2";
    std::string catalog_id2 = "0000099";
    e2.title = "A Dream of Spring";
    e2.author = "George R. R. Martin";
    e2.pubYear = 2032;

    testdb.add(isbn2, catalog_id2, e2);

    TestEntryBook e3;
    std::string isbn3 = "000-0-00-000000-3";
    std::string catalog_id3 = "0000098";
    e3.title = "A Game of Thrones";
    e3.author = "George R. R. Martin";
    e3.pubYear = 1996;

    testdb.add(isbn3, catalog_id3, e3);

    // Get sorted entries by key1
    auto sortedEntriesKey1Asc = testdb.getSortedEntries("k1", true);
    REQUIRE(sortedEntriesKey1Asc.size() == 3);
    REQUIRE(sortedEntriesKey1Asc[0].title == "The Winds of Winter");
    REQUIRE(sortedEntriesKey1Asc[1].title == "A Dream of Spring");
    REQUIRE(sortedEntriesKey1Asc[2].title == "A Game of Thrones");
    // Get sorted entries by key1 in descending order
    auto sortedEntriesKey1Desc = testdb.getSortedEntries("k1", false);
    REQUIRE(sortedEntriesKey1Desc.size() == 3);
    REQUIRE(sortedEntriesKey1Desc[0].title == "A Game of Thrones");
    REQUIRE(sortedEntriesKey1Desc[1].title == "A Dream of Spring");
    REQUIRE(sortedEntriesKey1Desc[2].title == "The Winds of Winter");
    // Get sorted entries by key2
    auto sortedEntriesKey2Asc = testdb.getSortedEntries("k2", true);
    REQUIRE(sortedEntriesKey2Asc.size() == 3);
    REQUIRE(sortedEntriesKey2Asc[0].title == "A Game of Thrones");
    REQUIRE(sortedEntriesKey2Asc[1].title == "A Dream of Spring");
    REQUIRE(sortedEntriesKey2Asc[2].title == "The Winds of Winter");
    // Get sorted entries by key2 in descending order
    auto sortedEntriesKey2Desc = testdb.getSortedEntries("k2", false);
    REQUIRE(sortedEntriesKey2Desc.size() == 3);
    REQUIRE(sortedEntriesKey2Desc[0].title == "The Winds of Winter");
    REQUIRE(sortedEntriesKey2Desc[1].title == "A Dream of Spring");
    REQUIRE(sortedEntriesKey2Desc[2].title == "A Game of Thrones");
}

TEST_CASE("DB: Test Sorted Student Entries", "[sorted student entries]")
{
    Database<TestEntryStudent> testdb;

    TestEntryStudent e1;
    std::string psid1 = "429001";
    std::string login1 = "abc123";
    e1.peopleSoftID = psid1;
    e1.login_username = login1;
    e1.gpa = 3.5;

    testdb.add(psid1, login1, e1);

    TestEntryStudent e2;
    std::string psid2 = "429002";
    std::string login2 = "acd134";
    e2.peopleSoftID = psid2;
    e2.login_username = login2;
    e2.gpa = 4.0;

    testdb.add(psid2, login2, e2);

    TestEntryStudent e3;
    std::string psid3 = "429003";
    std::string login3 = "xyz789";
    e3.peopleSoftID = psid3;
    e3.login_username = login3;
    e3.gpa = 3.9;

    testdb.add(psid3, login3, e3);

    TestEntryStudent e4;
    std::string psid4 = "429004";
    std::string login4 = "def456";
    e4.peopleSoftID = psid4;
    e4.login_username = login4;
    e4.gpa = 2.8;
    testdb.add(psid4, login4, e4);

    // Get sorted entries by key1
    auto sortedEntriesKey1Asc = testdb.getSortedEntries("k1", true);
    REQUIRE(sortedEntriesKey1Asc.size() == 4);
    REQUIRE(sortedEntriesKey1Asc[0].gpa == 3.5);
    REQUIRE(sortedEntriesKey1Asc[1].gpa == 4.0);
    REQUIRE(sortedEntriesKey1Asc[2].gpa == 3.9);
    REQUIRE(sortedEntriesKey1Asc[3].gpa == 2.8);

    // Get sorted entries by key1 in descending order
    auto sortedEntriesKey1Desc = testdb.getSortedEntries("k1", false);
    REQUIRE(sortedEntriesKey1Desc.size() == 4);
    REQUIRE(sortedEntriesKey1Desc[0].gpa == 2.8);
    REQUIRE(sortedEntriesKey1Desc[1].gpa == 3.9);
    REQUIRE(sortedEntriesKey1Desc[2].gpa == 4.0);
    REQUIRE(sortedEntriesKey1Desc[3].gpa == 3.5);

    // Get sorted entries by key2
    auto sortedEntriesKey2Asc = testdb.getSortedEntries("k2", true);
    REQUIRE(sortedEntriesKey2Asc.size() == 4);
    REQUIRE(sortedEntriesKey2Asc[0].gpa == 3.5);
    REQUIRE(sortedEntriesKey2Asc[1].gpa == 4.0);
    REQUIRE(sortedEntriesKey2Asc[2].gpa == 2.8);
    REQUIRE(sortedEntriesKey2Asc[3].gpa == 3.9);

    // Get sorted entries by key2 in descending order
    auto sortedEntriesKey2Desc = testdb.getSortedEntries("k2", false);
    REQUIRE(sortedEntriesKey2Desc.size() == 4);
    REQUIRE(sortedEntriesKey2Desc[0].gpa == 3.9);
    REQUIRE(sortedEntriesKey2Desc[1].gpa == 2.8);
    REQUIRE(sortedEntriesKey2Desc[2].gpa == 4.0);
    REQUIRE(sortedEntriesKey2Desc[3].gpa == 3.5);
}

TEST_CASE("DB: Test Sorted Student Entries with Add and Remove", "[sorted add remove]")
{
    Database<TestEntryStudent> testdb;

    TestEntryStudent e1;
    std::string psid1 = "429001";
    std::string login1 = "abc123";
    e1.peopleSoftID = psid1;
    e1.login_username = login1;
    e1.gpa = 3.5;

    testdb.add(psid1, login1, e1);

    TestEntryStudent e2;
    std::string psid2 = "429002";
    std::string login2 = "acd134";
    e2.peopleSoftID = psid2;
    e2.login_username = login2;
    e2.gpa = 4.0;

    testdb.add(psid2, login2, e2);

    TestEntryStudent e3;
    std::string psid3 = "429003";
    std::string login3 = "xyz789";
    e3.peopleSoftID = psid3;
    e3.login_username = login3;
    e3.gpa = 3.9;
    testdb.add(psid3, login3, e3);

    TestEntryStudent e4;
    std::string psid4 = "429004";
    std::string login4 = "def456";
    e4.peopleSoftID = psid4;
    e4.login_username = login4;
    e4.gpa = 2.8;
    testdb.add(psid4, login4, e4);

    TestEntryStudent e5;
    std::string psid5 = "429005";
    std::string login5 = "aaa111";
    e5.peopleSoftID = psid5;
    e5.login_username = login5;
    e5.gpa = 3.2;
    testdb.add(psid5, login5, e5);

    TestEntryStudent e6;
    std::string psid6 = "429006";
    std::string login6 = "bbb222";
    e6.peopleSoftID = psid6;
    e6.login_username = login6;
    e6.gpa = 3.7;
    testdb.add(psid6, login6, e6);

    // Get sorted entries by key1, ascending order
    auto sortedEntriesKey1Asc = testdb.getSortedEntries("k1", true);
    REQUIRE(sortedEntriesKey1Asc.size() == 6);
    REQUIRE(sortedEntriesKey1Asc[0].gpa == 3.5); // test first
    REQUIRE(sortedEntriesKey1Asc[5].gpa == 3.7); // test last

    testdb.remove(psid1);
    sortedEntriesKey1Asc = testdb.getSortedEntries("k1", true);
    REQUIRE(sortedEntriesKey1Asc.size() == 5);
    REQUIRE(sortedEntriesKey1Asc[0].gpa == 4.0); // test first, 429002 is now first in k1 sort
    REQUIRE(sortedEntriesKey1Asc[4].gpa == 3.7); // test last, 429006 is still the last in k1 sort

    testdb.remove(psid4);
    sortedEntriesKey1Asc = testdb.getSortedEntries("k1", true);
    REQUIRE(sortedEntriesKey1Asc.size() == 4);
    REQUIRE(sortedEntriesKey1Asc[0].gpa == 4.0); // test first, 429002 is still first in k1 sort
    REQUIRE(sortedEntriesKey1Asc[3].gpa == 3.7); // test last, 429006 is still the last in k1 sort

    auto sortedEntriesKey2Asc = testdb.getSortedEntries("k2", true);
    REQUIRE(sortedEntriesKey2Asc.size() == 4);
    REQUIRE(sortedEntriesKey2Asc[0].gpa == 3.2); // test first, aaa111 is first in k2 sort
    REQUIRE(sortedEntriesKey2Asc[3].gpa == 3.9); // test last, xyz789 is last in k2 sort

    testdb.remove(login5);
    sortedEntriesKey2Asc = testdb.getSortedEntries("k2", true);
    REQUIRE(sortedEntriesKey2Asc.size() == 3);
    REQUIRE(sortedEntriesKey2Asc[0].gpa == 4.0); // test first, acd134 is now first in k2 sort
    REQUIRE(sortedEntriesKey2Asc[2].gpa == 3.9); // test last, xyz789 is still the last in k2 sort
}

TEST_CASE("DB: Test Adding and Removing Students with Duplicate Items", "[duplicate items]")
{
    Database<TestEntryStudent> testdb;

    // Add students with duplicate GPAs
    TestEntryStudent e1 = {"429001", "abc123", 3.5};
    TestEntryStudent e2 = {"429002", "acd134", 3.5};
    TestEntryStudent e3 = {"429003", "xyz789", 3.9};
    TestEntryStudent e4 = {"429004", "def456", 3.5};
    TestEntryStudent e5 = {"429005", "aaa111", 4.0};

    testdb.add(e1.peopleSoftID, e1.login_username, e1);
    testdb.add(e2.peopleSoftID, e2.login_username, e2);
    testdb.add(e3.peopleSoftID, e3.login_username, e3);
    testdb.add(e4.peopleSoftID, e4.login_username, e4);
    testdb.add(e5.peopleSoftID, e5.login_username, e5);

    // Get sorted entries by GPA (ascending)
    auto sortedByk2Asc = testdb.getSortedEntries("k2", true);
    REQUIRE(sortedByk2Asc.size() == 5);
    REQUIRE(sortedByk2Asc[0].gpa == 4.0);
    REQUIRE(sortedByk2Asc[1].gpa == 3.5); // duplicate GPA
    REQUIRE(sortedByk2Asc[2].gpa == 3.5); // duplicate GPA
    REQUIRE(sortedByk2Asc[3].gpa == 3.5); // duplicate GPA
    REQUIRE(sortedByk2Asc[4].gpa == 3.9);

    // Remove one student with duplicate GPA and check sorting
    testdb.remove(e2.peopleSoftID);
    sortedByk2Asc = testdb.getSortedEntries("k2", true);
    REQUIRE(sortedByk2Asc.size() == 4);
    REQUIRE(sortedByk2Asc[0].gpa == 4.0);
    REQUIRE(sortedByk2Asc[1].gpa == 3.5); // duplicate GPA
    REQUIRE(sortedByk2Asc[2].gpa == 3.5); // duplicate GPA
    REQUIRE(sortedByk2Asc[3].gpa == 3.9);
}

TEST_CASE("DB: Test Frequent Add and Remove", "[frequent add remove]")
{
    Database<TestEntryStudent> testdb;

    // Add and remove entries frequently
    for (int i = 0; i < 100; i++)
    {
        TestEntryStudent e;
        e.peopleSoftID = "42900" + std::to_string(i);
        e.login_username = "user" + std::to_string(i);
        e.gpa = 3.0 + (i % 4) * 0.1; // GPA between 3.0 and 3.4

        testdb.add(e.peopleSoftID, e.login_username, e);
    }

    REQUIRE(testdb.getNumberOfEntries() == 100);

    for (int i = 0; i < 50; i++)
    {
        TestEntryStudent e;
        e.peopleSoftID = "42900" + std::to_string(i);
        testdb.remove(e.peopleSoftID);
    }

    REQUIRE(testdb.getNumberOfEntries() == 50);

    auto sortedEntriesKey1Asc = testdb.getSortedEntries("k1", true);
    REQUIRE(sortedEntriesKey1Asc.size() == 50);
    REQUIRE(sortedEntriesKey1Asc[0].peopleSoftID == "4290050");
    REQUIRE(sortedEntriesKey1Asc[49].peopleSoftID == "4290099");

    auto sortedEntriesKey2Asc = testdb.getSortedEntries("k2", true);
    REQUIRE(sortedEntriesKey2Asc.size() == 50);
    REQUIRE(sortedEntriesKey2Asc[0].login_username == "user50");
    REQUIRE(sortedEntriesKey2Asc[49].login_username == "user99");

    TestEntryStudent e21 = {"4290121", "user21", 2.8};
    testdb.add(e21.peopleSoftID, e21.login_username, e21);
    TestEntryStudent e22 = {"4290122", "zzz736", 3.9};
    testdb.add(e22.peopleSoftID, e22.login_username, e22);

    sortedEntriesKey1Asc = testdb.getSortedEntries("k1", true);
    REQUIRE(sortedEntriesKey1Asc.size() == 52);

    REQUIRE(sortedEntriesKey1Asc[50].peopleSoftID == "4290121");

    sortedEntriesKey2Asc = testdb.getSortedEntries("k2", true);
    REQUIRE(sortedEntriesKey2Asc.size() == 52);
    REQUIRE(sortedEntriesKey2Asc[51].login_username == "zzz736");
}