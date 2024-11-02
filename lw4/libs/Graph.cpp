//
// Created by sergey on 10/21/24.
//

#include "Graph.h"

#include <fstream>
#include <iostream>
#include <set>
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

void Graph::BranchesToMatrix()
{
  for (const Branch &branch: _branches)
  {
    _matrix[branch.node1][branch.node2] = 1;
    _matrix[branch.node2][branch.node1] = 1;
  }
}

void Graph::ParseLineToNode(const std::string &s)
{
  std::string parts[2];

  const int divideIndex = s.find(':');
  parts[0] = s.substr(0, divideIndex);
  parts[1] = s.substr(divideIndex + 1, s.length() - divideIndex);

  _vertexes[std::stoi(parts[0])] = parts[1];
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
    throw std::invalid_argument("Ошибка при открытии списка физических эффектов");
  }

  std::string line;
  while (std::getline(stream, line))
  {
    ParseLineToBranch(line);
  }

  size_t maxId = 0;
  for (const Branch &branch: _branches)
  {
    if (branch.node1 > maxId)
      maxId = branch.node1;
    if (branch.node2 > maxId)
      maxId = branch.node2;
  }

  _matrix.resize(++maxId);
  for (std::vector<size_t> &vector: _matrix)
  {
    vector.resize(maxId);
  }
  BranchesToMatrix();

  stream.close();
  stream.open("../data/P_NAME.TXT");
  if (!stream.is_open())
  {
    throw std::invalid_argument("Ошибка при открытии списка физических величин");
  }

  while (std::getline(stream, line))
  {
    ParseLineToNode(line);
  }
}

std::vector<std::vector<size_t>> Graph::FindPaths(const size_t start, const size_t end)
{
  std::set<size_t> visited;
  std::vector<std::vector<size_t>> paths;
  std::stack<std::pair<size_t, std::vector<size_t>>> stack;
  stack.emplace(start, std::vector{start});

  while (!stack.empty())
  {
    auto [currentNodeIndex, currentNodePath] = stack.top();
    stack.pop();
    if (currentNodeIndex == end)
    {
      paths.push_back(currentNodePath);
      continue;
    }

    visited.insert(currentNodeIndex);

    if (currentNodePath.size() > 4) // 5 звена отвалятся на проверке выше
    {
      continue;
    }


    for (size_t i = 1; i < _matrix.size(); i++)
    {
      if (_matrix[currentNodeIndex][i] && !visited.contains(i))
      {
        std::vector<size_t> pathToI = currentNodePath;
        pathToI.push_back(i);
        stack.emplace(i, pathToI);
      }
    }
   }

  return paths;
}

void Graph::PrintPaths(const std::vector<std::vector<Branch>> &paths)
{
  for (size_t i = 0; i < paths.size(); ++i)
  {
    std::cout << "Путь " << i + 1 << std::endl;
    std::cout << _vertexes[paths[i][0].node1] << " => ";
    for (auto &branch: paths[i])
    {
      // дебаг: std::cout << _vertexes[branch.node1] << " => " << branch.name << " => " << _vertexes[branch.node2] << "
      // ";
      std::cout << branch.name << " => ";
    }
    std::cout << _vertexes[paths[i].back().node2] << std::endl;
    std::cout << std::endl;
  }
}
