//
// Created by sergey on 12/11/24.
//

#include "BTree.h"

#include <iostream>

constexpr int PageSize = sizeof(Page);
constexpr int DataSize = sizeof(Data);

/*
 * Initialize
 */

void BTree::InitializeOnce()
{
  _rootIndex = 0;
  Page page{0};

  _pages.seekg(0);
  _pages.write(reinterpret_cast<char *>(&page), PageSize);
}

/*
 * Read
 */

Page BTree::ReadPage(const size_t pageIndex)
{
  Page page{0};
  _pages.seekg(pageIndex * PageSize);
  _pages.read(reinterpret_cast<char *>(&page), PageSize);
  return page;
}

Data BTree::ReadData(const size_t dataIndex)
{
  Data data{0};
  _valuesBin.seekg(dataIndex * DataSize);
  _valuesBin.read(reinterpret_cast<char *>(&data), DataSize);
  return data;
}


/*
 * Write
 */

void BTree::Insert(const std::string &value)
{
  const Page page = ReadPage(_rootIndex);
  page.keys[0] = 24;
  page.indexes[0] = 1;

}
