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
private:
  std::vector<Branch> branches;
};


#endif // GRAPH_H
