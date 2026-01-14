#ifndef _ADD_HPP
#define _ADD_HPP

#include "abstract_operator.hpp"

// Add is an derived template class that implements the AbstractOperator interface.
template <typename T>
class Add : public AbstractOperator<T>
{
public:
  Add(); // constructor
  T call(T arg1, T arg2) const;
  ~Add(); // destructor
};

#include "add.tpp"

#endif