#ifndef _ABSTRACT_OPERATOR_HPP
#define _ABSTRACT_OPERATOR_HPP

// AbstractOperator is an interface.
template <typename T>
class AbstractOperator
{
public:
  virtual T call(T arg1, T arg2) const = 0; // pure virtual
  virtual ~AbstractOperator() {};
};

#endif