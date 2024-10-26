//
// Created by sergey on 10/21/24.
//

#include "Graph.h"

#include <fstream>
#include <sstream>
#include <stack>

void Graph::ParseLineToBranch(const std::string &s)
{
  std::istringstream str_stream(s);
  std::string parts[3];
  std::vector<int> sourcesIds;

  std::getline(str_stream, parts[0], ';');
  std::getline(str_stream, parts[1], ';');
  std::getline(str_stream, parts[2], ';');

  std::istringstream intStream(parts[1]);
  std::string intPart;

  while (std::getline(intStream, intPart, ','))
  {
    sourcesIds.push_back(std::stoi(intPart));
  }

  for (size_t sourceNode: sourcesIds)
  {
    _branches.emplace_back(sourceNode, std::stoi(parts[2]), parts[0]);
  }
}

void Graph::BranchesToAdjMatrix()
{
  size_t maxNode = 0;
  for (const Branch &branch: _branches)
  {
    if (maxNode < branch.node1)
    {
      maxNode = branch.node1;
    }
    if (maxNode < branch.node2)
    {
      maxNode = branch.node2;
    }
  }

  _matrix.resize(maxNode);
  for (auto &m: _matrix)
  {
    m.resize(44);
  }

  for (const Branch &branch: _branches)
  {
    _matrix[branch.node1][branch.node2] = 1;
  }
}


void Graph::AddBranch(size_t node1, size_t node2, const std::string &name)
{
  _branches.emplace_back(node1, node2, name);
}


void Graph::ImportFromDefaultConfig()
{
  std::ifstream stream("../data/PHYS.TXT");

  if (!stream.is_open())
  {
    throw std::invalid_argument("Ошибка при открытии файла");
  }

  std::string line;
  while (std::getline(stream, line))
  {
    ParseLineToBranch(line);
  }

  BranchesToAdjMatrix();
}


std::vector<std::vector<size_t>> Graph::FindPaths(const size_t start, const size_t end)
{
  std::stack<std::pair<size_t, std::vector<size_t>>> stack;
  stack.emplace(start, std::vector<size_t>(start));
  std::vector<std::vector<size_t>> paths;

  while (!stack.empty())
  {
    auto &[currentIndex, path] = stack.top();
    stack.pop();

    if (currentIndex == end)
    {
      paths.push_back(path);
      continue;
    }

    for (size_t vertex : _matrix[currentIndex])
    {
      std::vector<size_t> newPath = path;
      newPath.push_back(vertex);
      stack.emplace(vertex, newPath);
    }
  }

  return paths;
}

