#ifndef BITSET_HPP
#define BITSET_HPP
#include <stdint.h> // support for intmax_t
#include <string>

class Bitset
{
public:
  virtual ~Bitset() {}; // virtual destructor, no need to comment

  // TODO COMMENT
  virtual intmax_t size() const = 0;

  // TODO COMMENT
  virtual bool good() const = 0;

  // TODO COMMENT
  virtual void set(intmax_t index) = 0;

  // TODO COMMENT
  virtual void reset(intmax_t index) = 0;

  // TODO COMMENT
  virtual void toggle(intmax_t index) = 0;

  // TODO COMMENT
  virtual bool test(intmax_t index) = 0;

  // TODO COMMENT
  virtual std::string asString() const = 0;
};

#endif
