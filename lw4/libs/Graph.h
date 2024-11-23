//
// Created by sergey on 10/21/24.
//

#ifndef GRAPH_H
#define GRAPH_H
#include <map>
#include <set>
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
  std::vector<std::vector<size_t>> _matrix;
  std::map<int, std::string> _vertexes;
  std::vector<std::vector<size_t>> _paths;
  std::set<size_t> _visited;

  void BranchesToMatrix();
  void AddBranch(size_t node1, size_t node2, const std::string &name);

  void ParseLineToBranch(const std::string &s);
  void ParseLineToNode(const std::string &s);

  void FindPathsRecursiverly(size_t start, size_t end, std::vector<std::size_t> path);
public:
  void ImportFromDefaultConfig();
  std::vector<std::vector<size_t>> FindPaths(size_t start, size_t end);
  void PrintPaths(const std::vector<std::vector<Branch>> &paths);
};


#endif // GRAPH_H
