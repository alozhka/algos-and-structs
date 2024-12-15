//
// Created by sergey on 12/11/24.
//

#ifndef BTREE_H
#define BTREE_H
#include <fstream>
#include <string>
#include <vector>

struct BTreeSpecs;

class KeyValue
{
  size_t index; // 0, 1, 2, 3, ...
  long key; // 25, 61, 99 - по ним идёт балансировка
  std::string value; // само значение
public:
  explicit KeyValue(const long index) : index(index), key({}), value({}) {}
};

class Page
{
  size_t index; // 0, 1, 2, 3, ...
  std::vector<size_t> indexes; // индексы ключей в файле data.bin
  std::vector<long> keys; // ключи в файле data.bin
  std::vector<size_t> childrenIndexes; // индексы детей
public:
  explicit Page(const long index, const size_t size) : index(index), keys(size), childrenIndexes(size) {}
};


class BTree
{
  std::fstream _pages, _valuesBin, _valuesTxt;
  size_t _degree;

  void ParseSpecs();
public:
  explicit BTree()
  {
    _pages.open("data/pages.bin", std::ios::in | std::ios::out | std::ios::binary);
    if (!_pages.is_open())
    {
      throw std::invalid_argument("Could not open pages file");
    }

    _valuesBin.open("data/values.bin", std::ios::in | std::ios::out | std::ios::binary);
    if (!_valuesBin.is_open())
    {
      throw std::invalid_argument("Could not open data file");
    }

    _valuesTxt.open("data/values.txt", std::ios::in | std::ios::out);
    if (!_valuesTxt.is_open())
    {
      throw std::invalid_argument("Could not open data file");
    }
  }

  void Contains(const std::string& value);

  void Insert(const std::string& value);

  void Erase(const std::string& value);

  ~BTree()
  {
    _pages.close();
    _valuesBin.close();
    _valuesTxt.close();
  }
};

struct BTreeSpecs
{
  size_t size;
  Page *root;
};

#endif //BTREE_H
