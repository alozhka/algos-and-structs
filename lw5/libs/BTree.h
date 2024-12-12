//
// Created by sergey on 12/11/24.
//

#ifndef BTREE_H
#define BTREE_H
#include <fstream>
#include <string>
#include <vector>

class Leaf
{
  size_t index; // 0, 1, 2, 3, ...
  long key; // 25, 61, 99 - по ним идёт балансировка
  std::string value; // само значение
public:
  explicit Leaf(const long index) : index(index), key({}), value({}) {}
};

class Page
{
  size_t index; // 0, 1, 2, 3, ...
  std::vector<long> keys; // ключи в файле data.bin
  std::vector<size_t> indexes; // индексы ключей в файле data.bin
  std::vector<size_t> childrenIndexes; // индексы детей
public:
  explicit Page(const long index, const size_t size) : index(index), keys(size), childrenIndexes(size) {}
};


class BTree
{
  std::fstream pages, values;

public:
  explicit BTree()
  {
    pages.open("data/pages.bin", std::ios::in | std::ios::out | std::ios::binary);
    if (!pages.is_open())
    {
      throw std::invalid_argument("Could not open pages file");
    }

    values.open("data/values.bin", std::ios::in | std::ios::out | std::ios::binary);
    if (!values.is_open())
    {
      throw std::invalid_argument("Could not open data file");
    }
  }
};


#endif //BTREE_H
