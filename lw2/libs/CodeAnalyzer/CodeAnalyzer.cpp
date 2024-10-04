//
// Created by sergey on 10/4/24.
//

#include "CodeAnalyzer.h"

#include <fstream>
#include <iostream>

namespace Pascal
{
  bool IsKeyword(const std::string &keyword)
  {
    return keyword == "REPEAT" || keyword == "BEGIN" || keyword == "RECORD" || keyword == "IF" || keyword == "UNTIL" ||
           keyword == "END" || keyword == "ELSE" || keyword == "THEN";
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
    if (left == "BEGIN" && right == "END")
      return true;
    if (left == "IF" && right == "ELSE")
      return true;
    return false;
  }

  std::string GetNextKeyword(const std::string &line, size_t &index)
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

      if (!inDoubleQuoteString && !inSingleQuoteString && !inComment)
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

  void CodeAnalyzer::ProcessState(const std::string &word)
  {
    switch (_state)
    {
      case 'O':
        if (word == "RECORD")
          _state = 'R';
        else if (word == "BEGIN")
        {
          _state = 'M';
          _stack.Push(word);
        }
        else
          _state = 'E';
        break;
      case 'R':
        if (word == "END")
          _state = 'O';
        else
          _state = 'E';
        break;
      case 'I':
        if (word == "THEN")
          _state = 'M';
        else
          _state = 'E';
        break;
      case 'M':
        if (IsOpenedKeyword(word))
        {
          _stack.Push(word);
          if (word == "IF")
            _state = 'I';
        }
      break;
    }
  }
  void CodeAnalyzer::CheckNesting()
  {
    std::string line;
    size_t lineNumber = 0;
    _state = 'O';

    while (getline(_stream, line))
    {
      lineNumber++;
      size_t index = 0;
      while (index < line.length())
      {
        const std::string &word = ToUpperCase(GetNextKeyword(line, index));
        if (IsKeyword(word))
        {
          if (_state == 'M' && IsClosedKeyword(word))
          {
            const std::string data = _stack.Pop();
            if ((_stack.IsEmpty() || data != "BEGIN") || !AreMatchingKeywords(data, word))
              _state = 'E';
          }
          this->ProcessState(word);
          if (_state == 'E')
          {
            std::cout << "Ошибка вложенности в строке " << lineNumber << std::endl;
            _stack.Clear();
            return;
          }
        }
      }
    }
  }

  void CodeAnalyzer::Analyze(const std::string &filename)
  {

    _stream.open(filename);
    if (!_stream.is_open())
    {
      std::cerr << "Ошибка при открытии файла!\n";
      return;
    }

    char repeat = 'y';
    while (repeat == 'y' || repeat == 'Y')
    {
      _stream.clear();
      _stream.seekg(0);
      CheckNesting();
      std::cout << "Проверить ещё раз? (Y/n): ";
      std::cin >> repeat;
    }
  }

} // namespace Pascal
