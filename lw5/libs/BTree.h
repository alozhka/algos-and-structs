//
// Created by sergey on 12/11/24.
//

#ifndef BTREE_H
#define BTREE_H
#include <map>
#include <string>
#include <vector>

class Leaf
{
  size_t index; // 0, 1, 2, 3, ...
  long key; // 25, 61, 99 - по ним идёт балансировка
  std::string value; // само значение
};

class Page
{
  size_t index; // 0, 1, 2, 3, ...
  std::map<long, size_t> keyIndexes; // пара ключ и его индекс в файле data.bin
  std::vector<size_t> childrenIndexes; // индексы детей
};


class BTree
{
  std::fstream
  Page head;
};


#endif //BTREE_H
