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
    const std::string value = str.substr(depth + 2, str.length() - depth - 3); // парсим значение
    return new Node(value, type);
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
    std::vector<Node *> nodes;

    while (std::getline(stream, line))
    {
      Node *parsedNode = ParseToNode(line, depth);

      if (depth == 0)
      {
        nodes.push_back(parsedNode);
      }
      else
      {
        while (nodes.size() > depth)
        {
          nodes.pop_back();
        }
        nodes.back()->AppendChild(parsedNode);
        nodes.push_back(parsedNode);
      }
    }

    _node = nodes.empty() ? nullptr : nodes.front();
  }

  std::string ReturnDepth(const size_t depth)
  {
    std::string returnStr;
    for (size_t i = 0; i < depth; i++)
    {
      returnStr += ".";
    }

    return returnStr;
  }


  std::vector<std::string> GenerateCombinations(std::vector<std::vector<std::string>> &arrays,
                                                const std::string &prefix = "")
  {
    std::vector combinations = {prefix};

    for (const auto &array: arrays)
    {
      std::vector<std::string> newCombinations;

      for (const std::string &combination: combinations)
      {
        for (const auto &element: array)
        {
          newCombinations.push_back(combination + "\n" + element);
        }
      }

      combinations = newCombinations;
    }

    return combinations;
  }


  std::vector<std::string> GetSubtrees(const Node *node, const size_t depth = 0)
  {
    if (node->type == Default)
    {
      return std::vector{std::string(depth, '.') + node->value};
    }

    std::vector<std::string> childrenSubtrees;
    std::vector<std::vector<std::string>> childrenSubtreesEntries; // список списков вариантов поддерева текущего узла

    if (node->type == Or)
    {
      for (const Node *child: node->children)
      {
        auto result = GetSubtrees(child, depth + 1);
        childrenSubtreesEntries.push_back(result);
      }
      for (const auto &child: childrenSubtreesEntries)
      {
        for (const auto &subEntry: child)
        {
          childrenSubtrees.push_back(std::string(depth, '.') + node->value + "\n" + subEntry);
        }
      }
    }

    if (node->type == And)
    {
      for (const Node *child: node->children)
      {
        auto result = GetSubtrees(child, depth + 1);
        childrenSubtreesEntries.push_back(result);
      }
      childrenSubtrees = GenerateCombinations(childrenSubtreesEntries, std::string(depth, '.') + node->value);
    }

    return childrenSubtrees;
  }

  void TreeViewer::Show() const
  {
    const std::vector<std::string> subtrees = GetSubtrees(_node);
    for (int i = 0; i < subtrees.size(); i++)
    {
      std::cout << "Number " << i + 1 << std::endl << subtrees[i] << std::endl;
    }
  }

} // namespace Tree::Viewer
