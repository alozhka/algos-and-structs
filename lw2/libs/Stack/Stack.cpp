//
// Created by sergey on 9/21/24.
//

#include "Stack.h"

void ClearStack(Node *&top)
{
  while (!IsEmpty(top))
  {
    const Data *data = Pop(top); // удаление узла
    delete data; // удаление значений узла
  }
}

void Push(Node *&stack, const std::string &value, const size_t line)
{
  auto *node = new Node(new Data(value, line), stack);
  stack = node;
}

Data *Pop(Node *&stack)
{
  if (stack == nullptr)
  {
    return nullptr; // Пустой стек
  }

  Node *node = stack; // Сохраняем указатель на текущий узел
  Data *data = node->data; // Сохраняем указатель на данные
  stack = stack->next; // Переключаем стек на следующий узел
  delete node;              // Удаляем узел
  return data;
}

bool IsEmpty(Node *&stack)
{
  return stack == nullptr;
}
