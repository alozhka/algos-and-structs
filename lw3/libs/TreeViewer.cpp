//
// Created by sergey on 9/30/24.
//

#include "TreeViewer.h"

#include <fstream>
#include <iostream>
#include <map>
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

  bool NotAllCompleted(std::map<Node *, std::pair<size_t, size_t>> &map)
  {
    for (const auto &[current, _]: map | std::views::values)
    {
      if (current > 0)
      {
        return true;
      }
    }

    return false;
  }

  int getIndex(const std::vector<Node *> &v, const Node *node)
  {
    for ( int i = 0; i < v.size(); i++)
    {
      if (v[i] == node)
      {
        return i;
      }
    }

    return -1;
  }

  bool GeneratePermutationWithDependencies(std::map<Node *, std::pair<size_t, size_t>> &map,
                                           std::map<Node *, Node *> &deps)
  {
    for (auto it = map.rbegin(); it != map.rend(); ++it)
    {
      Node *node = it->first;
      auto &[currentIndex, maxIndex] = it->second;

      Node *depParent = deps.contains(node) ? deps[node] : nullptr;
      if (depParent)
      {
        int childIndex = getIndex(depParent->children, node);
        if (childIndex != currentIndex) // или узел не выбран
        {
          continue;
        }
      }

      if (currentIndex > 0)
      {
        currentIndex--;
        return true;
      }
      else
      {
        currentIndex = maxIndex;
      }
    }

    return false;
  }

  std::map<Node *, std::pair<size_t, size_t>> FindOrNodesAndDependencies(Node *root, std::map<Node *, Node *> &deps)
  {
    std::map<Node *, std::pair<size_t, size_t>> orNodes;
    std::stack<Node *> nodes;
    nodes.push(root);

    while (!nodes.empty())
    {
      Node *node = nodes.top();
      nodes.pop();

      if (node->type == Or)
      {
        orNodes[node] = {node->children.size() - 1, node->children.size() - 1};
        for (auto child: node->children)
        {
          if (child->type == Or)
            deps[child] = node; // ребёнок зависит от родителя
        }
      }

      for (Node *child: std::ranges::reverse_view(node->children))
      {
        nodes.push(child);
      }
    }

    return orNodes;
  }

  void TreeViewer::Show() const
  {
    std::stack<std::tuple<Node *, size_t>> nodes;
    std::map<Node *, Node *> deps; // dependencies
    std::map<Node *, std::pair<size_t, size_t>> orNodes = FindOrNodesAndDependencies(_node, deps);
    size_t amount = 0;

    do
    {
      nodes.emplace(_node, 0);
      std::cout << "Number " << ++amount << std::endl;
      while (!nodes.empty())
      {
        auto [node, depth] = nodes.top();
        nodes.pop();

        std::cout << ReturnDepth(depth) << node->value << std::endl;
        if (node->type == Or)
        {
          auto &[current, _] = orNodes[node];
          nodes.emplace(node->children[current], depth + 1);
        }
        else
        {
          for (Node *child: std::ranges::reverse_view(node->children))
          {
            nodes.emplace(child, depth + 1);
          }
        }
      }
    }
    while (GeneratePermutationWithDependencies(orNodes, deps));
  }

} // namespace Tree::Viewer
