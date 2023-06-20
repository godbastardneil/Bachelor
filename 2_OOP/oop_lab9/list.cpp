#include "list.h"

list::list(const size_type& n, value_type v)
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
    for (iterator i=other.head; i != nullptr; i=i->next) { push_back(i->item); }
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
    iterator temp = new node(v);

    temp->next = nullptr;
    temp->prev = nullptr;

    if(size != 0) {
        head->prev = temp;
        temp->next = head;
        head = temp;
    } else { head = tail = temp; }

    ++size;
}

void list::pop_front()
{

    if (size > 0)
    {
        iterator tmp = head;
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
    iterator temp = new node(v);
    temp->next = nullptr;
    temp->prev = nullptr;

    if(size > 0) {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    } else { head = tail = temp; }

    ++size;
}

void list::pop_back()
{
    if (size > 0)
    {
        iterator tmp = tail;
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

iterator list::insert(iterator it, const value_type &v)
{
    if (size > 0)
    {
        if (it == tail)
        {
            push_back(v);
        } else if (it == head)
        {
            push_front(v);
        } else
        {
            iterator p = new node(v);
            p->next = it->next;
            p->prev = it;
            it->next = p;
            it->next->prev = p;
            ++size;
        }
    }
    return it;
}

void list::set_i(iterator it, const_reference v)
{
    it->item = v;
}
void list::set_i(const size_type i, const_reference v)
{
    element_checker(i);
    iterator it = begin();
    for (size_type j=0; j != i; ++j) { it = it->next; }
    set_i(it, v);
}

iterator list::erase(iterator it)
{
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
            iterator p = it;
            it->prev->next = it->next;
            it->next->prev = it->prev;
            it = it->next;
            delete p;
            --size;
        }
    }
    return it;
}

iterator list::erase(const size_type i)
{
    element_checker(i);
    iterator it = begin();
    for (size_type j=0; j != i; ++j) { it = it->next; }
    return erase(it);
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
    std::string s;
    if (size > 0)
    {
        for (iterator it = begin(); it != nullptr; it=it->next) { s += it->item.toString(); }
    } else { s = "\nНет информации"; }
    return s;
}
