//
// Created by sergey on 12/11/24.
//

#include "BTree.h"

constexpr int PageSize = sizeof(Page);
constexpr int BTreeSpecsSize = sizeof(BTreeSpecs);

void BTree::ParseSpecs()
{
  _valuesBin.seekg(0);
  BTreeSpecs specs;
  specs <<  _valuesBin;
  _degree = specs.size;
}

void BTree::Insert(const std::string &value)
{

}
