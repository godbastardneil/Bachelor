#ifndef STACK_H
#define STACK_H

#include <iostream>

#include "types.h"

class list;

class stack
{
public:
    // конструкторы
    stack();
    stack(const stack& other) noexcept;
    stack(stack&& other) noexcept;              // -- конструктор переноса -- //
    stack& operator=(const stack& other) noexcept;
    stack& operator=(stack&& other) noexcept;   // -- операция перемещения -- //
    ~stack() noexcept;

    bool empty() noexcept;
    void clear() noexcept;
    size_type get_size() noexcept;
    value_type top() noexcept;
    void push(const_reference v) noexcept;
    void pop() noexcept;

    std::string to_String() const noexcept;
private:
    list* st;
};

#endif // STACK_H
