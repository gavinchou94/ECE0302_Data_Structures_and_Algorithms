#include "Database.hpp"

template <typename T>
Database<T>::Database()
{
    // TODO
}

template <typename T>
bool Database<T>::isEmpty() const
{
    // TODO
    return false;
}

template <typename T>
std::size_t Database<T>::getNumberOfEntries() const
{
    // TODO
    return 0;
}

template <typename T>
bool Database<T>::add(std::string key1, std::string key2, T item)
{
    // TODO
    return false;
}

template <typename T>
bool Database<T>::remove(const std::string &key)
{
    // TODO
    return false;
}

template <typename T>
void Database<T>::clear()
{
    // TODO
}

template <typename T>
T Database<T>::getValue(const std::string &key) const
{
    // TODO
    return T();
}

template <typename T>
bool Database<T>::contains(const std::string &key) const
{
    // TODO
    return false;
}

template <typename T>
std::vector<T> Database<T>::getSortedEntries(std::string choice, bool ascending) const
{
    // TODO
    return std::vector<T>();
}
