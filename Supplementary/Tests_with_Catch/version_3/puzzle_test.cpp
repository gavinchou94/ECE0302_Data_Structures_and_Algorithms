/** @file puzzle_test.cpp */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "puzzle.hpp"

TEST_CASE("test constructor", "[puzzle]")
{
    Puzzle p;
    REQUIRE(p.get(0,0) == Puzzle::A); 
    // REQUIRE(p.get(0,1) == Puzzle::B);
    // REQUIRE(p.get(0,2) == Puzzle::C);
    // REQUIRE(p.get(1,0) == Puzzle::D);
    // REQUIRE(p.get(1,1) == Puzzle::E);
    // REQUIRE(p.get(1,2) == Puzzle::F);
    // REQUIRE(p.get(2,0) == Puzzle::G);
    // REQUIRE(p.get(2,1) == Puzzle::H);
    // REQUIRE(p.get(2,2) == Puzzle::EMPTY);
}

TEST_CASE("test move", "[puzzle]")
{
    Puzzle p; 
    p.move(2,1,2,2);
    REQUIRE(p.get(2,1) == Puzzle::EMPTY); 
    REQUIRE(p.get(2,2) == Puzzle::H);
}
