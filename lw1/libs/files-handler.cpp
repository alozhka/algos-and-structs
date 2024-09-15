//
// Created by sergey on 9/9/24.
//

#include "files-handler.h"

#include <fstream>
#include <iostream>
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

  // Считываем смещения строк в файле
  while (std::getline(inFile, line)) {
    positions.push_back(inFile.tellg());
  }

  // Записываем строки в обратном порядке
  for (auto it = positions.rbegin(); it != positions.rend(); ++it) {
    inFile.clear(); // Сбрасываем флаги ошибок
    inFile.seekg(it == positions.rbegin() ? std::streampos(0) : *(it - 1)); // Устанавливаем указатель
    std::getline(inFile, line); // Считываем строку
    outFile << line << std::endl;  // Записываем строку в выходной файл
  }

  inFile.close();
  outFile.close();}
