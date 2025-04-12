#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "TreeMinHeap.hpp"

TEST_CASE("Heap: test construct", "[construct]")
{
  TreeMinHeap<int> heap;
  REQUIRE(heap.getNumberOfNodes() == 0);
  REQUIRE(heap.isEmpty() == true);
}

TEST_CASE("Heap: test add and maintain heap property", "[add]")
{
  TreeMinHeap<int> heap;
  heap.add(10);
  REQUIRE(heap.peekTop() == 10);
  REQUIRE(heap.getNumberOfNodes() == 1);
  heap.add(20);
  REQUIRE(heap.peekTop() == 10);
  REQUIRE(heap.getNumberOfNodes() == 2);
  heap.add(5);
  REQUIRE(heap.peekTop() == 5);
  REQUIRE(heap.getNumberOfNodes() == 3);
  heap.add(12);
  REQUIRE(heap.peekTop() == 5);
  REQUIRE(heap.getNumberOfNodes() == 4);
  heap.add(30);
  REQUIRE(heap.peekTop() == 5);
  REQUIRE(heap.getNumberOfNodes() == 5);
  heap.add(25);
  REQUIRE(heap.peekTop() == 5);
  REQUIRE(heap.getNumberOfNodes() == 6);
  heap.add(35);
  REQUIRE(heap.peekTop() == 5);
  REQUIRE(heap.getNumberOfNodes() == 7);
  REQUIRE(heap.getHeight() == 3);
  heap.add(40);
  REQUIRE(heap.peekTop() == 5);
  REQUIRE(heap.getNumberOfNodes() == 8);
  REQUIRE(heap.getHeight() == 4);
}

TEST_CASE("Heap: test add duplicate", "[add]")
{
  TreeMinHeap<int> heap;
  REQUIRE(heap.add(10) == true);
  REQUIRE(heap.add(20) == true);
  REQUIRE(heap.add(5) == true);
  REQUIRE(heap.peekTop() == 5);
  REQUIRE(heap.getNumberOfNodes() == 3);

  heap.add(20);
  REQUIRE(heap.add(20) == false); // TreeMinHeap does not allow duplicates
  REQUIRE(heap.peekTop() == 5);
  REQUIRE(heap.getNumberOfNodes() == 3);

  REQUIRE(heap.add(-5) == true);
  REQUIRE(heap.peekTop() == -5);
  REQUIRE(heap.getNumberOfNodes() == 4);

  REQUIRE(heap.add(30) == true);
  REQUIRE(heap.peekTop() == -5);
  REQUIRE(heap.getNumberOfNodes() == 5);

  REQUIRE(heap.add(20) == false);
  REQUIRE(heap.peekTop() == -5);
  REQUIRE(heap.getNumberOfNodes() == 5);
}

TEST_CASE("Heap: test remove and maintain heap property, and remove empty", "[remove]")
{
  TreeMinHeap<int> heap;
  REQUIRE(heap.isEmpty() == true);
  REQUIRE(heap.remove() == false);

  REQUIRE(heap.add(10) == true);
  REQUIRE(heap.peekTop() == 10);
  REQUIRE(heap.getNumberOfNodes() == 1);
  REQUIRE(heap.remove() == true);
  REQUIRE(heap.getNumberOfNodes() == 0);
  REQUIRE(heap.isEmpty() == true);

  heap.add(20);
  heap.add(10);
  heap.add(30);
  heap.add(25);
  heap.add(5);

  REQUIRE(heap.remove() == true);
  REQUIRE(heap.peekTop() == 10);
  REQUIRE(heap.getNumberOfNodes() == 4);

  REQUIRE(heap.remove() == true);
  REQUIRE(heap.peekTop() == 20);
  REQUIRE(heap.getNumberOfNodes() == 3);

  REQUIRE(heap.remove() == true);
  REQUIRE(heap.peekTop() == 25);
  REQUIRE(heap.getNumberOfNodes() == 2);

  REQUIRE(heap.remove() == true);
  REQUIRE(heap.peekTop() == 30);
  REQUIRE(heap.getNumberOfNodes() == 1);

  REQUIRE(heap.remove() == true);
  REQUIRE(heap.getNumberOfNodes() == 0);

  REQUIRE(heap.remove() == false);
  REQUIRE(heap.isEmpty() == true);
}

TEST_CASE("Heap: test frequent add and remove", "[remove]")
{
  TreeMinHeap<int> heap;

  heap.add(10);
  heap.add(20);
  REQUIRE(heap.peekTop() == 10);
  heap.add(30);
  heap.add(25);
  heap.add(5);
  REQUIRE(heap.peekTop() == 5);
  heap.remove();
  REQUIRE(heap.peekTop() == 10);
  heap.remove();
  REQUIRE(heap.add(20) == false);
  REQUIRE(heap.peekTop() == 20);
  heap.remove();
  REQUIRE(heap.add(20) == true);
  REQUIRE(heap.peekTop() == 20);
  heap.remove();

  heap.add(7);
  heap.remove();
  heap.add(8);
  REQUIRE(heap.peekTop() == 8);
  heap.remove();
  REQUIRE(heap.peekTop() == 25);
  heap.remove();
  REQUIRE(heap.peekTop() == 30);
  heap.remove();
  REQUIRE(heap.isEmpty() == true);
}

TEST_CASE("Heap: test sort with large dataset", "[sort]")
{
  double array[] = {15.5, 5.5, 20.5, 10.5, 30.5, 19.5, 19.4, 41.2, 98.3, 0.7, 0.8, 0.9};
  TreeMinHeap<double> heap;
  heap.sort_a(array, 12);

  REQUIRE(array[0] == 0.7);
  REQUIRE(array[1] == 0.8);
  REQUIRE(array[2] == 0.9);
  REQUIRE(array[3] == 5.5);
  REQUIRE(array[4] == 10.5);
  REQUIRE(array[5] == 15.5);
  REQUIRE(array[6] == 19.4);
  REQUIRE(array[7] == 19.5);
  REQUIRE(array[8] == 20.5);
  REQUIRE(array[9] == 30.5);
  REQUIRE(array[10] == 41.2);
  REQUIRE(array[11] == 98.3);
}