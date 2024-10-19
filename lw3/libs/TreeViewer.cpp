//
// Created by sergey on 9/30/24.
//

#include "TreeViewer.h"

#include <fstream>
#include <iostream>
#include <ranges>
#include <stack>

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

  bool NotAllCompleted(std::vector<std::tuple<Node *, size_t>> &vector)
  {
    for (auto el: vector)
    {
      auto [node, current] = el;
      if (node->children.size() > 0)
      {
        return true;
      }
    }

    return false;
  }

  void TreeViewer::Show() const
  {
    std::stack<std::tuple<Node *, size_t>> nodes;
    std::vector<std::tuple<Node *, size_t>> orNodes;
    nodes.emplace(_node, _node->children.size() - 1);

    do
    {
      while (!nodes.empty())
      {
        auto [node, depth] = nodes.top();
        nodes.pop();

        std::cout << ReturnDepth(depth) << node->value << std::endl;

        for (int i = node->children.size() - 1; i >= 0; --i)
        {
          nodes.emplace(node->children[i], depth + 1);
        }
      }
    } while (NotAllCompleted(orNodes));
  }

} // namespace Tree::Viewer
