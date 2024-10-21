/*
Ложкин Сергей, ПС-21
Среда: CLion, C++

27. Имеется  И-ИЛИ   дерево,   соответствующее   некоторому
множеству  конструкций.  Требуется выдать на экран в наглядном
виде все элементы дерева (13).
*/

#include <iostream>


#include "libs/TreeViewer.h"

int main(const int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cerr << "Отсутствует путь до файла";
    return 1;
  }

  char repeat = 'y';
  Tree::Viewer::TreeViewer viewer;
  do
  {
    try
    {
      viewer.LoadFromFile(argv[1]);
      viewer.Show();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
      }

    std::cout << "Повторить считывание из файла? (Y/n): ";
    std::cin >> repeat;
    } while (repeat == 'Y' || repeat == 'y');

  return 0;
}
