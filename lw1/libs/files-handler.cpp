//
// Created by sergey on 9/9/24.
//

#include "files-handler.h"

#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

void files::reverse_file_strings(const std::string &file_name) {
  std::ifstream inFile(file_name);
  std::ofstream outFile("output.txt");

  if (!inFile.is_open()) {
    std::cerr << "Не удалось открыть входной файл!\n";
    return;
  }

  std::vector<std::streampos> positions;
  std::string line;

  while (inFile.peek() != EOF) {
    positions.push_back(inFile.tellg()); // Сохраняем позицию перед чтением строки
    std::getline(inFile, line);
  }

  // Записываем строки в обратном порядке
  for (auto &position: std::ranges::reverse_view(positions)) {
    inFile.clear(); // Сбрасываем флаги ошибок
    inFile.seekg(position); // Устанавливаем указатель
    std::getline(inFile, line); // Считываем строку
    outFile << line << std::endl;  // Записываем строку в выходной файл
  }


  inFile.close();
  outFile.close();
}
