#ifndef LIST_H
#define LIST_H

#include "types.h"

class list
{
public:
    struct node
    {
        value_type item;
        node *next = nullptr;
        node *prev = nullptr;

        friend bool operator==(const node &a, const node &b) { return (a.item == b.item); }
        friend bool operator!=(const node &a, const node &b) { return (a.item != b.item); }

    };
    struct iterator
    {
        node *nit = nullptr;
        // Конструкторы
        iterator() = default;
        explicit iterator(node *t) noexcept { nit = t; }
        ~iterator() { delete nit; }
        // Сравнение итераторов
        bool operator==(const iterator &it) const noexcept { return (nit == it.nit); }
        bool operator!=(const iterator &it) const noexcept { return !(nit == it.nit); }
        // Перемещение итератора
        iterator& operator++()              // вперед
        {
            nit = nit->next;
            return (*this);
        }
        iterator& operator--()              // назад
        {
            nit = nit->prev;
            return (*this);
        }
        reference operator*() { return nit->item; }   // разыменование
    };
    struct const_iterator
    {
        node *nit = nullptr;
        // Конструкторы
        const_iterator() = default;
        explicit const_iterator(node *t) noexcept { nit = t; }
        ~const_iterator() { delete nit; }
        // Сравнение итераторов
        bool operator==(const const_iterator &it) const noexcept { return (nit == it.nit); }
        bool operator!=(const const_iterator &it) const noexcept { return !(nit == it.nit); }
        // Перемещение итератора
        const_iterator& operator++()              // вперед
        {
            nit = nit->next;
            return (*this);
        }
        const_iterator& operator--()              // назад
        {
            nit = nit->prev;
            return (*this);
        }
        reference operator*() { return nit->item; }   // разыменование
    };

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
    void push_front (const_reference v) noexcept;          // добавить в начало
    void pop_front () noexcept;                        // удалить первый
    void push_back (const_reference v) noexcept;           // добавить в начало
    void pop_back () noexcept;                         // удалить последний
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

