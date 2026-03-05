#ifndef MIDTERM_HPP
#define MIDTERM_HPP

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <memory>
#include "ExamInterface.hpp"

template <typename T>
class Midterm : public ExamInterface<T>
{
public:
    T getScore() const;
    void other_func();
};
#include "Midterm.tpp"

#endif