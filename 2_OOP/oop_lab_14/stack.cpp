#include "stack.h"
#include "list.h"

stack::stack(): st(new list) {}

stack::stack(const stack &other) noexcept: st(new list(*other.st)){}

stack::stack(stack &&other) noexcept: st(new list(std::move(*other.st))) {  }

stack &stack::operator=(const stack &other) noexcept
{
    st->operator=(*other.st);
    return *this;
}

stack &stack::operator=(stack &&other) noexcept
{
    st->operator=(std::move(*other.st));
    return *this;
}

stack::~stack() noexcept { delete st; }

bool stack::empty() noexcept { return st->empty(); }
void stack::clear() noexcept { st->clear(); }
size_type stack::get_size() noexcept { return st->get_size(); }

value_type stack::top() noexcept { return st->back(); }

void stack::push(const_reference v) noexcept { st->push_back(v); }
void stack::pop() noexcept { st->pop_back(); }

std::string stack::to_String() const noexcept { return st->to_String(); }
