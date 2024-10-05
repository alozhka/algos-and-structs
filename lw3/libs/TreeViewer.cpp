//
// Created by sergey on 9/30/24.
//

#include "TreeViewer.h"

#include <fstream>
#include <iostream>
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
      case 'B':
        type = Default;
        break;
      default:
        throw std::runtime_error("Неизвестный тип узла");
    }
    std::string value = str.substr(depth + 2, value.length() - 1); // парсим значение
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

    std::stack<Node *> nodes;
    while (std::getline(stream, line))
    {
      Node *node = ParseToNode(line, depth);
    }
  }
  void TreeViewer::Show() const { std::cout << _node->value << "Зашёл в вывод\n";
  }

} // namespace Tree::Viewer
