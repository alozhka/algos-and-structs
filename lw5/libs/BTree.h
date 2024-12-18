//
// Created by sergey on 12/11/24.
//

#ifndef BTREE_H
#define BTREE_H
#include <cstring>
#include <fstream>
#include <string>


constexpr ulong BTREE_ORDER = 4;

struct BTreeSpecs;

class Data
{
  size_t index; // 0, 1, 2, 3, ...
  long key; // 25, 61, 99 - по ним идёт балансировка
  std::string value; // само значение
public:
  explicit Data(const long index) : index(index), key({}), value(50, ' ') {}
};

struct Page
{
  // 0, 1, 2, 3, ...
  size_t index;

  // индексы ключей в файле data.bin
  size_t indexes[BTREE_ORDER];

  // количество значений
  size_t numKeys;

  // ключи в файле data.bin
  long keys[BTREE_ORDER];

  // индексы детей
  size_t childrenIndexes[BTREE_ORDER];

  explicit Page(const long pageIndex)
  {
    index = pageIndex;
    numKeys = 0;
    std::memset(keys, 0, sizeof(keys));
    std::memset(indexes, -1, sizeof(indexes));
    std::memset(childrenIndexes, -1, sizeof(childrenIndexes));
  }
};


class BTree
{
  std::fstream _pages, _valuesBin, _valuesTxt;
  size_t _rootIndex;

  void InitializeOnce();
  Page ReadPage(const size_t pageIndex);
  void WritePage();

  Data ReadData(size_t dataIndex);
  void WriteData(const std::string &value);

public:
  explicit BTree()
  {
    _pages.open("../data/pages.bin", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    if (!_pages.is_open())
    {
      throw std::invalid_argument("Could not open pages file");
    }
    _pages.seekg(0, std::ios::end);
    if (!_pages.tellg() == 0)
    {
      InitializeOnce();
    }

    _valuesBin.open("../data/values.bin", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    if (!_valuesBin.is_open())
    {
      throw std::invalid_argument("Could not open data file");
    }

    _valuesTxt.open("../data/values.txt", std::ios::in | std::ios::out | std::ios::app);
    if (!_valuesTxt.is_open())
    {
      throw std::invalid_argument("Could not open data file");
    }
  }

  void Contains(const std::string &value);

  void Insert(const std::string &value);

  void Erase(const std::string &value);

  ~BTree()
  {
    _pages.close();
    _valuesBin.close();
    _valuesTxt.close();
  }
};

#endif //BTREE_H
