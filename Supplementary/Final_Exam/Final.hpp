#ifndef FINAL_HPP
#define FINAL_HPP

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>
#include "ExamInterface.hpp"

template <typename T>
class Final : public ExamInterface<T>
{
public:
    T getScore() const;
    void other_func();
};
#include "Final.tpp"

#endif