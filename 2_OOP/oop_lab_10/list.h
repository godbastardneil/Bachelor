#ifndef LIST_H
#define LIST_H

#include "types.h"

class list
{
public:
    // -- проверки на нулевой размер и существование элемента --
    void size_checker(const size_type &size) const;
    void element_checker(const size_type &i) const;

    /* Конструкторы/деструктор/присваивания */
    list() = default;
    explicit list(const size_type n, const_reference v);
    list(const std::initializer_list<value_type> &t);
    list(const list& other);
    list(list &&other);
    list& operator=(const list &other);
    list& operator=(list &&other) noexcept;

    virtual ~list() noexcept { clear(); }

    // Итераторы -------------------------
    iterator begin() noexcept { return iterator(head); }
    iterator end() noexcept { return iterator(tail); }
    const iterator begin() const noexcept { return iterator(head); }
    const iterator end() const noexcept { return iterator(tail); }

    // Доступ к элементам -------
    reference front()
    {
        size_checker(size);
        return head->item;
    }
    reference back()
    {
        size_checker(size);
        return tail->item;
    }

    // Размеры ------------------
    bool empty () const noexcept { return (size == 0); }
    size_type get_size() const noexcept { return size; }

    // Модификаторы контейнера --
    void push_front (const_reference v);          // добавить в начало
    void pop_front ();                        // удалить первый
    void push_back (const_reference v);           // добавить в начало
    void pop_back ();                         // удалить последний
    void set_i (const size_type &i, const_reference v);
    void erase (const size_type &i);                    // удалить указанный (в позиции)
    void clear ();                                // удалить все
    void swap (list &t) noexcept;        // обменять с заданным списком

    std::string to_String() const noexcept;

private:
    size_type size = 0;

    node *head = nullptr, *tail = nullptr;

    class zero_size {}; // размер 0
    class no_element {}; // нет запрашиваемого элемента
};

#endif // LIST_H

