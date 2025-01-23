#include "dynamic_bag.hpp"

template <typename T>
DynamicBag<T>::DynamicBag()
{
  // TODO
}

template <typename T>
DynamicBag<T>::DynamicBag(const DynamicBag<T> &x)
{
  // TODO
}

template <typename T>
DynamicBag<T>::~DynamicBag()
{
  // TODO
}

template <typename T>
DynamicBag<T> &DynamicBag<T>::operator=(DynamicBag<T> x)
{
  // TODO, use copy swap idiom
  return *this;
}

template <typename T>
void DynamicBag<T>::swap(DynamicBag<T> &x)
{
  // TODO
}

template <typename T>
bool DynamicBag<T>::add(const T &item)
{
  // TODO
  return false;
}

template <typename T>
bool DynamicBag<T>::remove(const T &item)
{
  // TODO
  return false;
}

template <typename T>
bool DynamicBag<T>::isEmpty() const
{
  // TODO
  return false;
}

template <typename T>
std::size_t DynamicBag<T>::getCurrentSize() const
{
  // TODO
  return 0;
}

template <typename T>
bool DynamicBag<T>::contains(const T &item) const
{
  // TODO
  return false;
}

template <typename T>
void DynamicBag<T>::clear()
{
  // TODO
}

template <typename T>
std::size_t DynamicBag<T>::getFrequencyOf(const T &item) const
{
  // TODO
  return 0;
};

template <typename T>
bool DynamicBag<T>::operator==(const AbstractBag<T> &other) const
{
  // TODO
  return false;
}