#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <cstdlib>
#include <string>

template <typename T>
class Database
{
public:
  Database();

  // determine if the database is empty
  bool isEmpty() const;

  // return current number of entries
  std::size_t getNumberOfEntries() const;

  // insert entry
  bool add(std::string key1, std::string key2, T item);

  // remove entry
  bool remove(const std::string &key);

  // remove all entries
  void clear();

  // retrieve the value mapped to the input key
  T getValue(const std::string &key) const;

  // return true if an entry exists with the input key
  bool contains(const std::string &key) const;

  // return a vector of entries in the database in sorted order by choice = "k1" or "k2"
  std::vector<T> getSortedEntries(std::string choice, bool ascending = true) const;

private:
  // TODO:
};

#include "Database.tpp"

#endif
