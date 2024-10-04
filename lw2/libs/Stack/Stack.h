//
// Created by sergey on 10/4/24.
//

#ifndef STACK_H
#define STACK_H
#include <string>
#include <utility>

namespace Stack
{
  struct Node
  {
    std::string data;
    Node *next;

    explicit Node(std::string  data, Node *next = nullptr) : data(std::move(data)), next(next) {}
  };

  class Stack
  {
    Node *_node;

  public:
    explicit Stack() : _node(nullptr) {}
    ~Stack() { Clear(); }

    bool IsEmpty() const;
    void Clear();
    void Push(const std::string& data);
    std::string Pop();
  };

} // namespace Stack

#endif // STACK_H
