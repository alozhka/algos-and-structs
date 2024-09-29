/*
Ложкин Сергей, ПС-21
Среда: C++

26. Программа на ПАСКАЛЕ включает такие  сочетания ключевых
слов,    как    REPEAT..UNTIL,   IF..THEN..ELSE,   BEGIN..END,
RECORD..END. Конец оператора  определяется  точкой  с  запятой
(";").  Требуется  проверить  правильность  вложенности данных
конструкций с учетом допустимости взаимных вложений. В случае
ошибок указать номер первой некорректной строки (12).

*/

#include "libs/CodeAnalyzer/CodeAnalyzer.h"

int main()
{
  Analyzer::Pascal::Analyze("../tests/err_repeat_until.pas");
  return 0;
}
