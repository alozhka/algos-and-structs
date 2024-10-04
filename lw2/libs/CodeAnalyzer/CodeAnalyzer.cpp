//
// Created by sergey on 9/29/24.
//

#include "CodeAnalyzer.h"
#include "../Stack/Stack.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <utility>


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
  bool IsKeyword(const std::string &keyword)
  {
    return keyword == "REPEAT" || keyword == "BEGIN" || keyword == "RECORD" || keyword == "IF" || keyword == "UNTIL" ||
           keyword == "END" || keyword == "ELSE" || keyword == "THEN" || keyword == ".";
  }
  bool IsOpenedKeyword(const std::string &keyword)
  {
    return keyword == "REPEAT" || keyword == "BEGIN" || keyword == "IF";
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
    size_t lineNumber = 0;
    char state = 'O'; // O - origin, M - main, C - common, I - in if .. then, R - in record

    while (getline(stream, line))
    {
      lineNumber++;
      size_t index = 0;
      while (index < line.length())
      {
        const std::string &word = ParseHelper::ToUpperCase(ParseHelper::getNextKeyword(line, index));
        if (Match::IsKeyword(word))
        {
          if (state == 'M' && Match::IsClosedKeyword(word))
          {
            const Data *data = Pop(stack);
            if (data == nullptr || (IsEmpty(stack) || data->value != "BEGIN") || !Match::AreMatchingKeywords(data->value, word))
              state = 'E';
          }
          switch (state)
          {
            case 'O':
              if (word == "RECORD")
                state = 'R';
              else if (word == "BEGIN")
              {
                state = 'M';
                Push(stack, word, lineNumber);
              }
              else
                state = 'E';
              break;
            case 'R':
              if (word == "END")
                state = 'O';
              else
                state = 'E';
              break;
            case 'I':
              if (word == "THEN")
                state = 'M';
              else
                state = 'E';
              break;
            case 'M':
              if (Match::IsOpenedKeyword(word))
              {
                Push(stack, word, lineNumber);
                if (word == "IF")
                  state = 'I';
              }
          }
          if (state == 'E')
          {
            std::cout << "Ошибка вложенности в строке " << lineNumber << std::endl;
            ClearStack(stack);
            return;
          }
        }
      }
    }

    if (!IsEmpty(stack))
    {
      std::cout << "Ошибка вложенности в строке " << lineNumber << std::endl;
      ClearStack(stack);
      return;
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
