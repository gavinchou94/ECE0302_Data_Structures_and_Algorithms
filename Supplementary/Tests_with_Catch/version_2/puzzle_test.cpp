/** @file puzzle_test.cpp */

#include <cassert>
#include "puzzle.hpp"

void test_constructor()
{
    Puzzle p;
    assert(p.get(0,0) == Puzzle::A); 
    assert(p.get(0,1) == Puzzle::B);
    assert(p.get(0,2) == Puzzle::C);
    assert(p.get(1,0) == Puzzle::D);
    assert(p.get(1,1) == Puzzle::E);
    assert(p.get(1,2) == Puzzle::F);
    assert(p.get(2,0) == Puzzle::G);
    assert(p.get(2,1) == Puzzle::H);
    assert(p.get(2,2) == Puzzle::EMPTY);
}

void test_move()
{
    Puzzle p; 
    p.move(2,1,2,2);
    assert(p.get(2,1) == Puzzle::EMPTY); 
    assert(p.get(2,2) == Puzzle::H);
}

int main()
{
    test_constructor(); 
    test_move();
    return 0;
}
