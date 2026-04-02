#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "list.hpp"
#include "queue.hpp"
#include "PathFinder.hpp"
#include <chrono>
#include <iostream>

/* Provided test cases */
TEST_CASE("PathFinder: Test minimum requirements on ADT queue and invalid images")
{
    Queue<int> queue;

    REQUIRE(queue.isEmpty());
    queue.enqueue(12);
    REQUIRE_FALSE(queue.isEmpty());

    queue.enqueue(13);
    queue.enqueue(14);

    REQUIRE(queue.peekFront() == 12);
    queue.dequeue();

    REQUIRE(queue.peekFront() == 13);
    queue.dequeue();

    REQUIRE(queue.peekFront() == 14);
    queue.dequeue();
    REQUIRE(queue.isEmpty());
    REQUIRE_THROWS_AS(queue.peekFront(), std::out_of_range);
    REQUIRE_THROWS_AS(queue.dequeue(), std::out_of_range);

    // A simple 3x3 image with an invalid pixel color (BLUE)
    Image<Pixel> img(3, 3);
    img(0, 0) = WHITE;
    img(0, 1) = WHITE;
    img(0, 2) = WHITE;
    img(1, 0) = WHITE;
    img(1, 1) = BLUE;
    img(1, 2) = WHITE;
    img(2, 0) = WHITE;
    img(2, 1) = WHITE;
    img(2, 2) = WHITE;

    REQUIRE_THROWS_AS(PathFinder myFinder(img), std::invalid_argument);

    img(1, 1) = WHITE; // no RED pixel
    REQUIRE_THROWS_AS(PathFinder myFinder(img), std::invalid_argument);

    img(1, 1) = RED; // one RED pixel
    img(1, 2) = RED; // two RED pixels now
    REQUIRE_THROWS_AS(PathFinder myFinder(img), std::invalid_argument);

    img(1, 2) = BLACK; // one RED pixel, one BLACK pixel — valid
    REQUIRE_NOTHROW(PathFinder myFinder(img));

    Image<Pixel> img2 = readFromFile("../tests/maze00_extra_color.png");
    REQUIRE_THROWS_AS(PathFinder myFinder(img2), std::invalid_argument);

    Image<Pixel> img3 = readFromFile("../tests/maze00_no_start.png");
    REQUIRE_THROWS_AS(PathFinder myFinder(img3), std::invalid_argument);

    Image<Pixel> img4 = readFromFile("../tests/maze00_extra_start.png");
    REQUIRE_THROWS_AS(PathFinder myFinder(img4), std::invalid_argument);
}

TEST_CASE("PathFinder: Test basic getStart and getEnd", "[pathfinder]")
{
    // 3x3 image with one RED pixel at (1,1)
    Image<Pixel> img(3, 3);
    img(0, 0) = WHITE;
    img(0, 1) = WHITE;
    img(0, 2) = WHITE;
    img(1, 0) = WHITE;
    img(1, 1) = RED;
    img(1, 2) = WHITE;
    img(2, 0) = WHITE;
    img(2, 1) = WHITE;
    img(2, 2) = WHITE;

    PathFinder myFinder(img);
    REQUIRE(myFinder.getStart() == Coord(1, 1));
    REQUIRE(myFinder.getEnd() == Coord(-1, -1)); // not yet discovered by BFS
}

TEST_CASE("PathFinder: Test helper functions load, clear and checkImage", "[pathfinder]")
{
    Image<Pixel> img = readFromFile("../tests/maze00.png");

    PathFinder myFinder(img);
    REQUIRE_NOTHROW(myFinder.checkImage(img));
    REQUIRE(myFinder.getStart() == Coord(12, 2));

    myFinder.clear();
    REQUIRE(myFinder.getStart() == Coord(-1, -1));

    img(12, 2) = YELLOW; // invalid color
    REQUIRE_THROWS_AS(myFinder.checkImage(img), std::invalid_argument);

    img(12, 2) = WHITE; // no RED pixel
    REQUIRE_THROWS_AS(myFinder.checkImage(img), std::invalid_argument);

    img(12, 2) = RED; // one RED pixel
    img(12, 3) = RED; // two RED pixels now
    REQUIRE_THROWS_AS(myFinder.checkImage(img), std::invalid_argument);

    img(12, 3) = BLACK; // one RED pixel, one BLACK pixel — valid
    REQUIRE_NOTHROW(myFinder.checkImage(img));
}

/*
// Demo of how long it takes to find a path (not included in grader)
TEST_CASE("Demo Pathfinding Duration Test", "[pathfinder]")
{
    Image<Pixel> img0 = readFromFile("../tests/maze00.png");
    REQUIRE_NOTHROW(PathFinder my_solver0(img0));

    PathFinder my_solver(img0);

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    my_solver.findPath();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Elapsed time for Pathfinding of maze00: " << elapsed_seconds.count() << "s\n";

    my_solver.writeSolutionToFile("../tests/myoutput00_NSWE.png");
    REQUIRE(compareImagesExit("../tests/output00_NSWE.png", "../tests/myoutput00_NSWE.png"));

    // Clear and reinitialize the solver using a different strategy
    my_solver.clear();
    my_solver.load(img0);
    my_solver.findPath("WENS");
    my_solver.writeSolutionToFile("../tests/myoutput00_WENS.png");
    REQUIRE(compareImagesExit("../tests/output00_WENS.png", "../tests/myoutput00_WENS.png"));

    Image<Pixel> img1 = readFromFile("../tests/maze01.png");
    my_solver.clear();
    my_solver.load(img1);
    // maze01 is unsolvable
    REQUIRE_THROWS_AS(my_solver.findPath(), std::runtime_error);
    my_solver.clear();

    Image<Pixel> img2 = readFromFile("../tests/maze02.png");
    my_solver.load(img2);

    start = std::chrono::steady_clock::now();
    my_solver.findPath();
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Elapsed time for Pathfinding of maze02: " << elapsed_seconds.count() << "s\n";

    my_solver.writeSolutionToFile("../tests/myoutput02_NSWE.png");
    REQUIRE(compareImagesExit("../tests/output02_NSWE.png", "../tests/myoutput02_NSWE.png"));
    my_solver.clear();
}

// Demo of findPathWithVisualization (not included in grader)
TEST_CASE("Demo Pathfinding Gif Creation", "[pathfinder]")
{
    Image<Pixel> img0 = readFromFile("../tests/maze00.png");
    PathFinder my_solver(img0);

    // maze00: small maze, record every BFS step (frame_gap=1), 20ms per frame
    // Produces myoutput00.gif and myoutput00_final_visual.png
    my_solver.findPathWithVisualization("../tests/myoutput00", 20, 1);
    my_solver.clear();

    Image<Pixel> img1 = readFromFile("../tests/maze01.png");
    my_solver.load(img1);
    // maze01: unsolvable — throws, but partial search is still recorded in the GIF
    // Record 1 frame every 50 BFS steps, 5ms per frame
    REQUIRE_THROWS(my_solver.findPathWithVisualization("../tests/myoutput01", 5, 50));
    my_solver.clear();

    Image<Pixel> img2 = readFromFile("../tests/maze02.png");
    my_solver.load(img2);
    // maze02: larger but solvable, same frame settings as maze01
    my_solver.findPathWithVisualization("../tests/myoutput02", 5, 50);
    my_solver.clear();
}
*/

/* Write your own unit tests here */