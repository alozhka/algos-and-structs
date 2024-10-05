//
// Created by sergey on 9/30/24.
//

#ifndef TREEVIEWER_H
#define TREEVIEWER_H
#include <string>
#include <vector>


namespace Tree::Viewer
{
  const enum NodeType { Default, And, Or };

  struct Node
  {
    std::string value;
    NodeType type;
    std::vector<Node *> children;

    Node(std::string value, const NodeType type) : value(std::move(value)), type(type) {}
  };

  class TreeViewer
  {
    Node *_node;

  public:
    TreeViewer() : _node(nullptr) {}

    void LoadFromFile(const std::string &filename);
    void Show() const;
  };

} // namespace Tree::Viewer

#endif // TREEVIEWER_H
