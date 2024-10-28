//
// Created by sergey on 10/21/24.
//

#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <vector>

struct Branch
{
  size_t node1, node2;
  std::string name;

  Branch(const size_t n1, const size_t n2, std::string s) : node1(n1), node2(n2), name(std::move(s)) {}
};

class Graph
{
  std::vector<Branch> _branches;

  void AddBranch(size_t node1, size_t node2, const std::string &name);
  void ParseLineToBranch(const std::string &s);

public:
  void ImportFromDefaultConfig();
  std::vector<std::vector<Branch>> FindPaths(size_t start, size_t end);
};


#endif // GRAPH_H
