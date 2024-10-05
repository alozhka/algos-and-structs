//
// Created by sergey on 9/30/24.
//

#include "TreeViewer.h"

#include <fstream>
#include <iostream>

namespace Tree::Viewer
{
  Node *ParseToNode(const std::string &str, size_t &depth)
  {
    depth = 0;
    while (str[depth] == '.')
      depth++; // берем глубину

    NodeType type;
    switch (str.at(depth))
    {
      case 'A':
        type = And;
        break;
      case 'O':
        type = Or;
        break;
      case 'D':
        type = Default;
        break;
      default:
        throw std::runtime_error("Неизвестный тип узла");
    }
    std::string value = str.substr(depth + 2, str.length() - depth - 3); // парсим значение
    return new Node(value, type);
  }
  void ComputeDepth(std::vector<size_t> &currentChildIndexes, const size_t depth)
  {
    if (currentChildIndexes.empty())
      currentChildIndexes = {0};
    else if (currentChildIndexes.size() - 1 == depth)
      currentChildIndexes.back()++;
    else if (currentChildIndexes.size() - 1 < depth)
      currentChildIndexes.push_back(0); // зашли глубже
    else // выходим из глубин и удаляем данные
    {
      while (currentChildIndexes.size() + 1 != depth)
      {
        currentChildIndexes.pop_back();
      }
    }
  }

  Node *FindCurrectNode(Node *&node, const std::vector<size_t> &indexes, const size_t depth)
  {
    Node *temp = node;
    for (size_t i = 0; i < depth - 1; i++)
    {
      temp = temp->children.at(indexes.at(i));
    }
    return temp;
  }

  void InsertNode(Node *parent, Node *newNode)
  {
    if (parent == nullptr)
    {
      parent = newNode;
    }
    else
    {
      parent->children.push_back(newNode);
    }
  }

  void TreeViewer::LoadFromFile(const std::string &filename)
  {
    std::ifstream stream(filename);

    if (!stream.is_open())
    {
      throw std::runtime_error("Ошибка при открытии файла");
    }

    std::string line;
    size_t depth = 0;
    std::vector<size_t> currentChildIndexes;

    while (std::getline(stream, line))
    {
      Node *parsedNode = ParseToNode(line, depth);
      ComputeDepth(currentChildIndexes, depth);

      if (_node == nullptr)
      {
        _node = parsedNode;
        continue;
      }

      Node *parent = FindCurrectNode(_node, currentChildIndexes, depth);
      InsertNode(parent, parsedNode);
    }
  }

  void TreeViewer::Show() const
  {
  }

} // namespace Tree::Viewer
