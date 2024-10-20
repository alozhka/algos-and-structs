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


  std::vector<std::string> GetSubtrees(const Node *node, const size_t depth = 0)
  {
    if (node->type == Default)
    {
      return std::vector{std::string(depth, '.') + node->value};
    }

    std::vector<std::string> childrenSubtrees;
    for (const Node *child: node->children)
    {
      auto result = GetSubtrees(child, depth + 1);
      std::string returnstr;
      for (const std::string &str: result)
      {
        returnstr += str + "\n";
      }
      childrenSubtrees.push_back(returnstr);
    }

    return childrenSubtrees;
  }

  void TreeViewer::Show() const
  {
    const std::vector<std::string> subtrees = GetSubtrees(_node);
    for (int i = 0; i < subtrees.size() - 1; i++)
    {
      std::cout << "Number " << i + 1 << std::endl << subtrees[i] << std::endl;
    }
  }

} // namespace Tree::Viewer
