//
// Created by sergey on 10/4/24.
//

#ifndef CODEANALYZER_H
#define CODEANALYZER_H
#include <fstream>


#include "../Stack/Stack.h"

namespace Pascal
{

  class CodeAnalyzer
  {
    Stack::Stack _stack;
    std::ifstream _stream;
    /*
     * O - origin, M - main, C - common, I - in if .. then, R - in record
     */
    char _state = 'O';

    void ProcessState(const std::string &word);
    void CheckNesting();

  public:
    explicit CodeAnalyzer(): _stack(), _stream() {};

    void Analyze(const std::string &filename);
  };

} // namespace Pascal

#endif // CODEANALYZER_H
