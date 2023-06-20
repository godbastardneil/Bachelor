#include "list.h"

void list::size_checker(const size_type &size) const { if (size == 0) { throw zero_size(); } }
void list::element_checker(const size_type &i) const { if (i >= size) { throw no_element(); } }

list::list(const size_type n, const_reference v)
{
    size_checker(n); // защита "от дурака"
    for (size_type i=0; i<n; ++i) { push_back(v); }
}

list::list(const std::initializer_list<value_type> &v)
{
    size_checker(v.size()); // защита "от дурака"
    for (value_type i: v) { push_back(i); }
}
list::list(const list& other)
{
    size_checker(other.get_size()); // защита "от дурака"
    for (iterator i=iterator(other.head); i.nit != nullptr; ++i) { push_back(*i); }
}
list::list(list &&other): size(other.size), head(other.head), tail(other.tail)
{
    other.size = 0;
    other.head = nullptr;
    other.tail = nullptr;
}
list &list::operator=(const list &other)
{
    if (this != &other)
    {
        list temp(other);
        std::swap(size, temp.size);
        std::swap(head, temp.head);
        std::swap(tail, temp.tail);
    }
    return *this;
}

list &list::operator=(list &&other) noexcept
{
    if (this != &other)
    {
        std::swap(size, other.size);
        std::swap(head, other.head);
        std::swap(tail, other.tail);
    }
    return *this;
}


void list::push_front(const_reference v)
{
    node *tmp = new node(v);

    tmp->next = nullptr;
    tmp->prev = nullptr;

    if(size != 0) {
        head->prev = tmp;
        tmp->next = head;
        head = tmp;
    } else { head = tail = tmp; }

    ++size;
}

void list::pop_front()
{
    if (size > 0)
    {
        node *tmp = head;
        if (head != tail)
        {
            head = head->next;
            head->prev = nullptr;
        } else
        {
            head = nullptr;
            tail = nullptr;
        }
        delete tmp;

        --size;
    }
}

void list::push_back(const_reference v)
{
    node *tmp = new node(v);

    tmp->next = nullptr;
    tmp->prev = nullptr;

    if(size > 0) {
        tail->next = tmp;
        tmp->prev = tail;
        tail = tmp;
    } else { head = tail = tmp; }

    ++size;
}

void list::pop_back()
{
    if (size > 0)
    {
        node *tmp = tail;
        if (head != tail)
        {
            tail = tail->prev;
            tail->next = nullptr;
        } else
        {
            head = nullptr;
            tail = nullptr;
        }
        delete tmp;
        --size;
    }
}

void list::set_i(const size_type &i, const_reference v)
{
    element_checker(i);
    node *it = head;
    for (size_type j=0; j < i; ++j) { it = it->next; }
    it->item = v;
}

void list::erase(const size_type &i)
{
    element_checker(i);
    node *it = head;
    for (size_type j=0; j != i; ++j) { it = it->next; }
    if (size > 0)
    {
        if (it == tail)
        {
            pop_back();
        } else if (it == head)
        {
            pop_front();
        } else
        {
            node *p = it;
            it->prev->next = it->next;
            it->next->prev = it->prev;
            it = it->next;
            delete p;
            --size;
        }
    }
}

void list::clear()
{
    while (size > 0) { pop_back(); }
}

void list::swap(list &t) noexcept
{
    if (head != t.head)
    {
        std::swap(size, t.size);
        std::swap(head, t.head);
        std::swap(tail, t.tail);
    }

}

std::string list::to_String() const noexcept
{
    std::stringstream ss;
    std::string s = "";
    if (size > 0)
    {
        for (iterator it = begin(); it.nit != nullptr; ++it)
        {
            data_type dt = std::get<2>(*it);
            ss << "\n Номер договора: " << std::get<0>(*it)
               << "\n Номер телефона: " << std::get<1>(*it)
               << "\n Дата заключения договора: " << std::to_string(std::get<0>(dt)) << "д" << std::to_string(std::get<1>(dt)) << "м" << std::to_string(std::get<2>(dt)) << "г"
               << "\n Стоимость: " << std::to_string(std::get<3>(*it))
               << "\n Тариф: " << std::to_string(std::get<4>(*it));
        }
    } else { ss << "\nНет информации"; }
    return ss.str();
}
