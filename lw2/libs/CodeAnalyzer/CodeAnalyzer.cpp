//
// Created by sergey on 9/29/24.
//

#include "CodeAnalyzer.h"
#include "../Stack/Stack.h"

#include <cctype>
#include <fstream>
#include <iostream>


namespace Analyzer::ParseHelper
{
  std::string getNextKeyword(const std::string &line, size_t &index)
  {
    std::string word;
    bool inDoubleQuoteString = false;
    bool inSingleQuoteString = false;
    bool inComment = false;

    while (index < line.length())
    {
      // Проверка на открывающую кавычку
      switch (line[index])
      {
        case '"':
          inDoubleQuoteString = !inDoubleQuoteString;
          break;
        case '\'':
          inSingleQuoteString = !inSingleQuoteString;
          break;
        case '{':
          inComment = true;
          break;
        case '}':
          inComment = false;
        default:;
      }

      bool canInsert = !inDoubleQuoteString && !inSingleQuoteString && !inComment;
      if (canInsert)
      {
        if (isalpha(line[index])) // Проверяем, является ли текущий символ буквой
        {
          word += line[index]; // Добавляем символ к слову
        }
        else if (!word.empty()) // Если слово не пустое, выходим из цикла
        {
          break;
        }
      }

      index++;
    }

    return word;
  }

  std::string ToUpperCase(const std::string &str)
  {
    std::string lower;
    for (const char c: str)
    {
      lower += std::toupper(c);
    }

    return lower;
  }
} // namespace Analyzer::ParseHelper

namespace Analyzer::Pascal::Match
{
  bool IsOpenedKeyword(const std::string &keyword)
  {
    return keyword == "REPEAT" || keyword == "BEGIN" || keyword == "RECORD" || keyword == "IF";
  }

  bool IsClosedKeyword(const std::string &keyword)
  {
    return keyword == "UNTIL" || keyword == "END" || keyword == "ELSE";
  }

  bool AreMatchingKeywords(const std::string &left, const std::string &right)
  {
    if (left == "REPEAT" && right == "UNTIL")
      return true;
    if ((left == "BEGIN" || left == "RECORD") && right == "END")
      return true;
    if (left == "IF" && right == "ELSE")
      return true;
    return false;
  }
} // namespace Analyzer::Pascal::Match

namespace Analyzer::Pascal
{
  void CheckNesting(std::ifstream &stream)
  {
    Node *stack = nullptr;
    std::string line;
    int lineNumber = 0;
    bool hasError = false, expectThen = false, expectEnd = false;

    while (getline(stream, line))
    {
      lineNumber++;
      size_t index = 0;

      while (index < line.length())
      {
        const std::string &word = ParseHelper::ToUpperCase(ParseHelper::getNextKeyword(line, index));

        if (Match::IsOpenedKeyword(word) || word == "THEN")
        {
          if (expectEnd)
            hasError = true;
          if (expectThen && word != "THEN")
            hasError = true;
          else
            expectThen = false;
          if (word == "IF")
            expectThen = true;
          if (word == "RECORD")
            expectEnd = true;
          Push(stack, word, lineNumber);
        }

        if (Match::IsClosedKeyword(word))
        {
          if (expectEnd && word == "END")
            expectEnd = false;
          if (const Data *data = Pop(stack); data == nullptr || !Match::AreMatchingKeywords(data->value, word))
            hasError = true;
        }
        if (hasError)
        {
          std::cout << "Ошибка вложенности в строке " << lineNumber << std::endl;
          ClearStack(stack);
          return;
        }
      }
    }

    std::cout << "Вложенность конструкций корректна.\n";
    ClearStack(stack);
  }

  void Analyze(const std::string &filename)
  {
    std::ifstream stream(filename);
    if (!stream.is_open())
    {
      std::cerr << "Ошибка при открытии файла!\n";
      return;
    }

    char repeat = 'y';
    while (repeat == 'y' || repeat == 'Y')
  {
    stream.clear();
    stream.seekg(0);
      CheckNesting(stream);
      std::cout << "Проверить ещё раз? (Y/n): ";
      std::cin >> repeat;
    }
  }
}
