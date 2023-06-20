#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "abon.h"


using value_type = abon;
using size_type = size_t;
struct node
{
    node(const value_type &v):item(v) {}
    node() {}
    value_type item;
    node *next = nullptr;
    node *prev = nullptr;
};
using iterator = node*;
using reference = value_type& ;
using const_reference = const value_type& ;

class list
{
public:
    // -- проверки на нулевой размер и существование элемента --
    inline void size_checker(size_type size) const { if (size == 0) { throw zero_size(); } }
    inline void element_checker(size_type i) const { if (i >= size) { throw no_element(); } }


    /* Конструкторы/деструктор/присваивания */
    list() = default;
    virtual ~list() noexcept { clear(); }
    list(const size_type& n, value_type v = value_type());
    list(const std::initializer_list<value_type> &t);
    list(const list& other);
    list(list &&other);
    list& operator=(const list &other);
    list& operator=(list &&other) noexcept;

    // Итераторы -------------------------
    iterator begin() noexcept { return head; };
    iterator end() noexcept { return tail; };
    iterator begin() const noexcept { return head; };
    iterator end() const noexcept { return tail; };

    // Доступ к элементам -------
    reference front()
    {
        size_checker(size);
        return head->item;
    }
    reference back()
    {
        size_checker(size);
        return head->item;
    }

    // Размеры ------------------
    bool empty () const noexcept { return (size == 0); }
    size_type get_size() const noexcept { return size; }

    // Модификаторы контейнера --
    void push_front (const_reference v);          // добавить в начало
    void pop_front ();                        // удалить первый
    void push_back (const_reference v);           // добавить в начало
    void pop_back ();                         // удалить последний
    iterator insert (iterator it, const_reference v);  // вставить в позицию итератора
    void set_i (iterator it, const_reference v);
    void set_i (const size_type i, const_reference v);
    iterator erase (iterator it);                    // удалить указанный (в позиции)
    iterator erase (const size_type i);                    // удалить указанный (в позиции)
    void clear ();                                // удалить все
    void swap (list &t) noexcept;        // обменять с заданным списком

    std::string to_String() const noexcept;

private:
    size_type size = 0;

    iterator head = nullptr, tail = nullptr;

    class zero_size {}; // размер 0

    class no_element {}; // нет запрашиваемого элемента
};

#endif // LIST_H
