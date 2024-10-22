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
};

class Graph
{
  std::vector<Branch> branches;
public:
  void AddBranch(std::string name, size_t node1, size_t node2);
  std::vector<std::string> FindPaths(size_t node1, size_t node2);
};


#endif // GRAPH_H
