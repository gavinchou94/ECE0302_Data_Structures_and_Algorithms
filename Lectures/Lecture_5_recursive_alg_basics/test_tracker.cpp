/** @file test_tracker.cpp
 * @author ChatGPT, GitHub Copilot
 * @version 2.0, modified in 2025 by G. Zhou for ECE0302
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

   REQUIRE(gcd.gcd(2025, 302) == 1);
   std::cout << "Calling gcd(2025, 302): " << std::endl;
   displayResults(gcd);
   gcd.reset();

   REQUIRE(gcd.gcd(302, 2025) == 1);
   std::cout << "Calling gcd(302, 2025): " << std::endl;
   displayResults(gcd);
   gcd.reset();
}

TEST_CASE("Tower of Hanoi", "[hanoi]")
{
   TowerOfHanoiTracker hanoi;
   std::cout << "Calling hanoi(3, 'A', 'C', 'B'): " << std::endl;
   hanoi.hanoi(3, 'A', 'C', 'B');
   displayResults(hanoi);
   hanoi.reset();

   std::cout << "Calling hanoi(3, 'A', 'C', 'B'): " << std::endl;
   hanoi.hanoi(3, 'A', 'C', 'B', false);
   displayResults(hanoi); // Analyze the result here, and compare with Line 117
                          // Explain why you cannot use Line 117's statistics compare with the next test cases with 7/10/15 disks
                          // what does it tell you about designing the benchmark?
   hanoi.reset();
}

TEST_CASE("Tower of Hanoi with 7/10/15 disks", "[hanoi]")
{
   TowerOfHanoiTracker hanoi;
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

   // base case for FALSE
   int uni_arr[] = {1};
   REQUIRE(binary_search.binary_search(uni_arr, 5, 0, 1) == false); // one-element array
   std::cout << "Calling binary_search(uni_arr, 5, 0, 1): " << std::endl;
   displayResults(binary_search);
   binary_search.reset();

   // base case for TRUE
   int arr[] = {1, 2, 3, 4, 5, 101, 202, 303, 404, 505, 1001, 2002, 3003, 4004, 5005};
   REQUIRE(binary_search.binary_search(arr, 303, 0, 15) == true);
   std::cout << "Calling binary_search(arr, 303, 0, 15): " << std::endl;
   displayResults(binary_search);
   binary_search.reset();
}

TEST_CASE("Binary Search Recursive Case", "[binary_search]")
{
   BinarySearchTracker binary_search;

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

   // Study the above size-15 array and these search cases with their tracking data
   // 1. what difference do you observe? 2. which edge case is not tested yet?
}
