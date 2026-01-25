/** @file test_tracker.cpp
 * @author GenAI tools such as ChatGPT, GitHub Copilot
 * @version 2.0, modified in 2026 by G. Zhou for ECE0302
 */

#define CATCH_CONFIG_MAIN

#include "OperationTracker.hpp"
#include "FactorialTracker.hpp"
#include "GCDTracker.hpp"
#include "TowerOfHanoiTracker.hpp"
#include "BinarySearchTracker.hpp"
#include "catch.hpp"
#include <iostream>
#include <string>

void displayResults(const OperationTracker &op)
{
   std::cout << "Tracking Stats: ";
   std::cout << op.getOperationCount() << " operations, " << op.getMaxRecursionDepth() << " max recursion depth, "
             << op.getExecutionTime() << " nanoseconds" << std::endl
             << std::endl;
}

TEST_CASE("Factorial Base Case", "[factorial]")
{
   FactorialTracker fact;
   fact.factorial(4); // warm-up call to account for timing overhead
   fact.reset();

   REQUIRE(fact.factorial(0) == 1);
   std::cout << "Calling factorial(0): " << std::endl;
   displayResults(fact);
   fact.reset();

   REQUIRE(fact.factorial(1) == 1);
   std::cout << "Calling factorial(1): " << std::endl;
   displayResults(fact);
   fact.reset();
}

TEST_CASE("Factorial Recursive Case with small/middle/large numbers", "[factorial]")
{
   FactorialTracker fact;
   fact.factorial(4); // warm-up call to account for timing overhead
   fact.reset();

   REQUIRE(fact.factorial(5) == 120);
   std::cout << "Calling factorial(5): " << std::endl;
   displayResults(fact);
   fact.reset();

   REQUIRE(fact.factorial(20) == 2432902008176640000);
   std::cout << "Calling factorial(20): " << std::endl;
   displayResults(fact);
   fact.reset();

   fact.factorial(1000);
   std::cout << "Calling factorial(1000): " << std::endl;
   displayResults(fact);
   fact.reset();
}

TEST_CASE("GCD Base Case", "[gcd]")
{
   GCDTracker gcd;
   gcd.gcd(18, 6); // warm-up call to account for timing overhead
   gcd.reset();

   REQUIRE(gcd.gcd(0, 0) == 0);
   std::cout << "Calling gcd(0, 0): " << std::endl;
   displayResults(gcd);
   gcd.reset();

   REQUIRE(gcd.gcd(0, 5) == 5);
   std::cout << "Calling gcd(0, 5): " << std::endl;
   displayResults(gcd);
   gcd.reset();

   REQUIRE(gcd.gcd(5, 0) == 5);
   std::cout << "Calling gcd(5, 0): " << std::endl;
   displayResults(gcd);
   gcd.reset();
}

TEST_CASE("GCD Recursive Case with small/middle/large numbers", "[gcd]")
{
   GCDTracker gcd;
   gcd.gcd(18, 6); // warm-up call to account for timing overhead
   gcd.reset();

   REQUIRE(gcd.gcd(75, 45) == 15);
   std::cout << "Calling gcd(75, 45): " << std::endl;
   displayResults(gcd);
   gcd.reset();

   REQUIRE(gcd.gcd(45, 75) == 15);
   std::cout << "Calling gcd(45, 75): " << std::endl;
   displayResults(gcd);
   gcd.reset();

   REQUIRE(gcd.gcd(484, 99) == 11);
   std::cout << "Calling gcd(484, 99): " << std::endl;
   displayResults(gcd);
   gcd.reset();

   REQUIRE(gcd.gcd(99, 484) == 11);
   std::cout << "Calling gcd(99, 484): " << std::endl;
   displayResults(gcd);
   gcd.reset();

   REQUIRE(gcd.gcd(2026, 302) == 2);
   std::cout << "Calling gcd(2026, 302): " << std::endl;
   displayResults(gcd);
   gcd.reset();

   REQUIRE(gcd.gcd(302, 2026) == 2);
   std::cout << "Calling gcd(302, 2026): " << std::endl;
   displayResults(gcd);
   gcd.reset();
}

TEST_CASE("Tower of Hanoi", "[hanoi]")
{
   TowerOfHanoiTracker hanoi;
   hanoi.hanoi(1, 'A', 'C', 'B', false); // warm-up call to account for timing overhead
   hanoi.reset();

   std::cout << "Calling hanoi(3, 'A', 'C', 'B'): " << std::endl;
   hanoi.hanoi(3, 'A', 'C', 'B');
   displayResults(hanoi);
   hanoi.reset();

   std::cout << "Calling hanoi(3, 'A', 'C', 'B'): " << std::endl;
   hanoi.hanoi(3, 'A', 'C', 'B', false);
   displayResults(hanoi); // TODO: Analyze the tracking statistics here, and compare with Line 131 above;
                          // explain why you cannot use Line 131's statistics compare with the next test cases with 7/10/15 disks
                          // What does it tell you about designing the benchmark to compare recursive algorithms?
   hanoi.reset();
}

TEST_CASE("Tower of Hanoi with 7/10/15 disks", "[hanoi]")
{
   TowerOfHanoiTracker hanoi;
   hanoi.hanoi(1, 'A', 'C', 'B', false); // warm-up call to account for timing overhead
   hanoi.reset();

   std::cout << "Calling hanoi(7, 'A', 'C', 'B'): " << std::endl;
   hanoi.hanoi(7, 'A', 'C', 'B', false);
   displayResults(hanoi);
   hanoi.reset();

   std::cout << "Calling hanoi(10, 'A', 'C', 'B'): " << std::endl;
   hanoi.hanoi(10, 'A', 'C', 'B', false);
   displayResults(hanoi);
   hanoi.reset();

   std::cout << "Calling hanoi(15, 'A', 'C', 'B'): " << std::endl;
   hanoi.hanoi(15, 'A', 'C', 'B', false);
   displayResults(hanoi);
   hanoi.reset();
}

TEST_CASE("Binary Search Base Case", "[binary_search]")
{
   BinarySearchTracker binary_search;
   int uni_arr[] = {0, 1, 2};
   binary_search.binary_search(uni_arr, 2, 0, 3); // warm-up call to account for timing overhead
   binary_search.reset();

   // base case for FALSE
   REQUIRE(binary_search.binary_search(uni_arr, 5, 0, 3) == false);
   std::cout << "Calling binary_search(uni_arr, 5, 0, 3): " << std::endl;
   displayResults(binary_search);
   binary_search.reset();

   // base case for TRUE
   REQUIRE(binary_search.binary_search(uni_arr, 1, 0, 3) == true);
   std::cout << "Calling binary_search(uni_arr, 1, 0, 3): " << std::endl;
   displayResults(binary_search);
   binary_search.reset();
}

TEST_CASE("Binary Search Recursive Case", "[binary_search]")
{
   BinarySearchTracker binary_search;
   int uni_arr[] = {0, 1, 2};
   binary_search.binary_search(uni_arr, 2, 0, 3); // warm-up call to account for timing overhead
   binary_search.reset();

   int arr[] = {1, 2, 3, 4, 5, 101, 202, 303, 404, 505, 1001, 2002, 3003, 4004, 5005};

   REQUIRE(binary_search.binary_search(arr, 7, 0, 15) == false);
   std::cout << "Calling binary_search(arr, 7, 0, 15): " << std::endl;
   displayResults(binary_search);
   binary_search.reset();

   REQUIRE(binary_search.binary_search(arr, 202, 0, 15) == true);
   std::cout << "Calling binary_search(arr, 202, 0, 15): " << std::endl;
   displayResults(binary_search);
   binary_search.reset();

   REQUIRE(binary_search.binary_search(arr, 221, 0, 15) == false);
   std::cout << "Calling binary_search(arr, 221, 0, 15): " << std::endl;
   displayResults(binary_search);
   binary_search.reset();

   REQUIRE(binary_search.binary_search(arr, 4004, 0, 15) == true);
   std::cout << "Calling binary_search(arr, 4004, 0, 15): " << std::endl;
   displayResults(binary_search);
   binary_search.reset();

   REQUIRE(binary_search.binary_search(arr, 9999, 0, 15) == false);
   std::cout << "Calling binary_search(arr, 9999, 0, 15): " << std::endl;
   displayResults(binary_search);
   binary_search.reset();

   // Study the above length-15 array and the binary search cases with the tracking statistics.
   // 1. what differences do you observe regarding various search values?
   // 2. which edge case is not tested yet that you can add to further study the binary search performance?
}