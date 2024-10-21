/*
Ложкин Сергей, ПС-21
Среда: CLion, C++

26. Программа на ПАСКАЛЕ включает такие  сочетания ключевых
слов,    как    REPEAT..UNTIL,   IF..THEN..ELSE,   BEGIN..END,
RECORD..END. Конец оператора  определяется  точкой  с  запятой
(";").  Требуется  проверить  правильность  вложенности данных
конструкций с учетом допустимости взаимных вложений. В случае
ошибок указать номер первой некорректной строки (12).

*/

#include <iostream>
#include "libs/CodeAnalyzer/CodeAnalyzer.h"

int main(const int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cerr << "Не передано имя файла";
    return 1;
  }
  Pascal::CodeAnalyzer analyzer;
  analyzer.Analyze(argv[1]);
  return 0;
}
