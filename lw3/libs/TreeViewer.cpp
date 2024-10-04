//
// Created by sergey on 9/30/24.
//

#include "TreeViewer.h"

#include <fstream>
#include <iostream>

namespace Tree::Viewer
{
  void TreeViewer::LoadFromFile(const std::string &filename)
  {
    const std::ifstream stream(filename);

    if (!stream.is_open())
    {
      throw std::invalid_argument("Ошибка при открытии файла");
    }

    
  }
  void TreeViewer::Show() const
  {
    std::cout << _tree->value << "Зашёл в вывод\n";
  }

} // namespace Tree::Viewer
