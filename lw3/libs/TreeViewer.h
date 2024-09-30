//
// Created by sergey on 9/30/24.
//

#ifndef TREEVIEWER_H
#define TREEVIEWER_H
#include <string>
#include <vector>

namespace Tree::Viewer
{
  struct Node
  {
    std::string value;
    std::vector<Node *> children;

    explicit Node(const std::string &value);
  };

  class TreeViewer
  {
    Node *_tree;

  public:
    TreeViewer() : _tree(nullptr) {}

    void LoadFromFile(const std::string &filename);
    void Show() const;
  };

} // namespace Tree::Viewer

#endif // TREEVIEWER_H
