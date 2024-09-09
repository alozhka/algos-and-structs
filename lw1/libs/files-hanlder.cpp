//
// Created by sergey on 9/9/24.
//

#include "files-hanlder.h"

#include <fstream>
#include <iostream>

void files::reverse_file_strings(const std::string &file_name) {
  std::ifstream input(file_name);

  if (!input.is_open()) {
    std::cerr << "Не удалось открыть входной файл!\n";
    return;
  }

  std::cout << "Прошли";
}
