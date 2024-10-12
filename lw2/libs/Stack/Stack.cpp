//
// Created by sergey on 10/4/24.
//

#include "Stack.h"

#include <stdexcept>
#include <utility>

namespace Stack
{
  bool Stack::IsEmpty() const { return _node == nullptr; }

  void Stack::Clear()
  {
    while (!this->IsEmpty())
    {
      const Node *temp = _node;
      _node = _node->next;
      delete temp;
    }
  }

  std::string Stack::Pop()
  {
    if (this->IsEmpty())
    {
      throw std::runtime_error("Called pop of the empty stack");
    }
    const Node *temp = _node;
    std::string data = std::move(_node->data);
    _node = _node->next;
    delete temp;
    return data;
  }

  void Stack::Push(const std::string& data)
  {
    _node = new Node(data, _node);
  }

} // namespace Stack
