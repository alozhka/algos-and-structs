/*

Ложкин Сергей. ПС-21.
Среда: c++

27. Задан  текстовый  файл. Каждая строка содержит не более
255 символов. Создать  новый  файл,  в  котором  строки  будут
следовать в обратном порядке. Размер файла  не ограничивается.
Запрещается размещать файл целиком в  основной  памяти.  Файлы
размером порядка 10 Мгб должны обрабатываться не  более 2 сек.
(9).

 */
#include <iostream>

#define BOOST_TIMER_ENABLE_DEPRECATED
#include <boost/timer.hpp>
#include "libs/files-handler.h"


int main() {
  boost::timer timer;

  setlocale(LC_ALL, "RUS");
  timer.restart();
  files::reverse_file_strings("../tests/MET_BIG.TXT");
  const double duration = timer.elapsed();

  std::cout << "Время: " << duration << std::endl;
  return 0;
}
