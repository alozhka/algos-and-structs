//
// Created by sergey on 12/11/24.
//

#include "BTree.h"

#include <iostream>

constexpr int PageSize = sizeof(Page);

/*
 * Initialize
 */

void BTree::InitializeOnce() {
  _rootIndex = 0;
  Page page{0};

  _pages.seekg(0);
  _pages.write(reinterpret_cast<char *>(&page), PageSize);
}

/*
 * Read
 */

Page BTree::ReadPage(const size_t pageIndex) {
  Page page{0};
  _pages.seekg(pageIndex * PageSize);
  _pages.read(reinterpret_cast<char *>(&page), PageSize);
  return page;
}


/*
 * Write
 */

void BTree::Insert(const std::string &value) {
  // пропустили характеристики дерева + количество по индексу после него до нужного узла
  Page page = ReadPage(_rootIndex);
  if (page.numKeys == BTREE_ORDER) {
    Page newPage(0);
    newPage.childrenIndexes[0] = page.index;
  }
}
