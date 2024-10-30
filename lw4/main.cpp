/*
Ложкин Сергей, ПС-21
Среда: CLion, C++

25. На диске имеется база данных по физическим эффектам
(ФЭ).  Каждый ФЭ записан в виде тройки компонент: название,
входная физическая величина (вход), выходная физическая
величина (выход).  Имеется не более 100 различных физических
величин. Требуется построить в основной памяти граф связи ФЭ и
обеспечить поиск цепочек ФЭ от одного до четырех звеньев по
заданным входу и выходу по возрастанию количества звеньев(12).
*/


#include <iostream>

#include "libs/Graph.h"

int main(const int argc, const char *argv[])
{
  if (argc < 3)
  {
    std::cerr << "Указаны не все данные";
    return 1;
  }

  try
  {
    Graph graph;
    graph.ImportFromDefaultConfig();
    const std::vector<std::vector<Branch>> paths = graph.FindPaths(std::stoull(argv[1]), std::stoull(argv[2]));
    for (size_t i = 0; i < paths.size(); ++i)
    {
      std::cout << "Путь " << i + 1 << std::endl;
      for (auto &branch : paths[i])
      {
        std::cout << branch.node1 << " " << branch.name << " " << branch.node2 << " ";
      }
      std::cout << std::endl;
    }
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  return 0;
}
