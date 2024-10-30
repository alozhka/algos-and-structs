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
    _branches.emplace_back(std::stoi(parts[2]), sourceNode, parts[0]);
  }
}

void Graph::ParseLineToNode(const std::string &s)
{
  std::string parts[2];

  int divideIndex = s.find(':');
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

bool BranchesEqual(const Branch &left, const Branch &right)
{
  return left.node1 == left.node1 && left.node2 == left.node2 && left.name == right.name;
}

std::vector<std::vector<Branch>> Graph::FindPaths(const size_t start, const size_t end)
{
  std::stack<std::pair<size_t, std::vector<Branch>>> stack;
  stack.emplace(start, std::vector<Branch>{});
  std::set<std::string> visited;
  std::vector<std::vector<Branch>> paths;

  while (!stack.empty())
  {
    auto [currentNodeIndex, currentNodePath] = stack.top();
    stack.pop();

    if (currentNodeIndex == end)
    {
      paths.push_back(currentNodePath);
      continue;
    }

    Branch prevBranch = currentNodePath.size() > 0 ? currentNodePath.back() : Branch(0, 0, "");
    for (const Branch &childBranch: _branches)
    {
      if (childBranch.node1 == currentNodeIndex &&
          childBranch.node2 != prevBranch.node1 &&
          !visited.contains(childBranch.name)) // чтобы не вернуться в прошлую вершину
      {
        visited.insert(childBranch.name);
        std::vector<Branch> newPath = currentNodePath;
        newPath.push_back(childBranch);
        stack.emplace(childBranch.node2, newPath);
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
    for (auto &branch : paths[i])
    {
      // дебаг: std::cout << _vertexes[branch.node1] << " => " << branch.name << " => " << _vertexes[branch.node2] << " ";
      std::cout << branch.name << " => ";
    }
    std::cout << _vertexes[paths[i].back().node2] << std::endl;
    std::cout << std::endl;
  }
}
