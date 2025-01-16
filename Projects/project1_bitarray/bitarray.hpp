#ifndef BITARRAY_HPP
#define BITARRAY_HPP
#include <stdint.h>
#include <string>

#include "bitset.hpp"

class BitArray : public Bitset
{
public:
  BitArray();

  BitArray(intmax_t size);

  BitArray(const std::string &value);

  ~BitArray();

  BitArray(const BitArray &) = delete;
  BitArray &operator=(const BitArray &) = delete;

  intmax_t size() const;

  bool good() const;

  void set(intmax_t index);

  void reset(intmax_t index);

  void toggle(intmax_t index);

  bool test(intmax_t index);

  std::string asString() const;

private:
  // TODO
};

#endif