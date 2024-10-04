//
// Created by sergey on 9/21/24.
//

#ifndef STACK_H
#define STACK_H
#include <string>


struct Node
{
  std::string data;
  Node *next;
};

void ClearStack(Node*& top);
bool IsEmpty(Node*& stack);
void Push(Node *&stack, const std::string &value, size_t line);
Data* Pop(Node *&stack);

#endif // STACK_H
