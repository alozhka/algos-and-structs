//
// Created by sergey on 9/29/24.
//

#ifndef CODEANALYZER_H
#define CODEANALYZER_H
#include <string>

namespace Analyzer::Pascal::Match
{
  bool IsOpenedKeyword(const std::string& keyword);
  bool IsClosedKeyword(const std::string& keyword);
  bool AreMatchingKeywords(const std::string& left, const std::string& right);
}

namespace Analyzer::Pascal
{
  void Analyze(const std::string& filename);
}

#endif //CODEANALYZER_H
