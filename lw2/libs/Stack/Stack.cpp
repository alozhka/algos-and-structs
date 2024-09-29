//
// Created by sergey on 9/21/24.
//

#include "Stack.h"

void Push(Node *&stack, const std::string &value, const size_t line)
{
  const auto node = new Node(new Data(value, line), stack);
  stack = node;
}

Data *Pop(Node *&stack)
{
  const auto temp = new Data(stack->data->value, stack->data->line);
  Node *node = stack->next;
  stack = node;
  delete node;
  return temp;
}

bool IsEmpty(const Node *&stack)
{
  return stack == nullptr;
}
