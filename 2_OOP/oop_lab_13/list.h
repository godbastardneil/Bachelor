#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <tuple>
#include <string>
#include <sstream>

template <class Y>
class const_iterator;
template <class V>

class list
{
public:
    using size_type = size_t;
    using value_type = V;
    using reference = value_type&;
    using const_reference = const value_type&;
    struct node
    {
        node *next = nullptr;
        node *prev = nullptr;
        value_type item;
        friend bool operator==(const node &a, const node &b);
        friend bool operator!=(const node &a, const node &b);

    };
    template <class Y>
    struct iterator
    {
        node *nit = nullptr;
        // Конструкторы
        iterator() = default;
        explicit iterator(node *t) noexcept;
        // Сравнение итераторов
        bool operator==(const iterator &it) const noexcept;
        bool operator!=(const iterator &it) const noexcept;
        // Перемещение итератора
        iterator& operator++();
        iterator& operator--();
        reference operator*();   // разыменование
        bool isnull() const noexcept;
    };
    // -- проверки на нулевой размер и существование элемента --
    void size_checker(const size_type &size) const;
    void element_checker(const size_type &i) const;

    /* Конструкторы/деструктор/присваивания */
    list() = default;
    list(const std::initializer_list<value_type> &t);
    list(const list<V>& other);
    list(list<V> &&other);
    list& operator=(const list<V> &other);
    list& operator=(list<V>&& other) noexcept;

    virtual ~list();

    // Итераторы -------------------------
    iterator<V> begin() noexcept { return iterator<V>(head); }
    iterator<V> end() noexcept { return iterator<V>(tail); }
    const_iterator<V> begin() const noexcept;
    const_iterator<V> end() const noexcept;

    // Доступ к элементам -------
    reference front();
    reference back();

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
    void swap (list<V> &t) noexcept;        // обменять с заданным списком

private:
    size_type size = 0;
    node *head = nullptr, *tail = nullptr;
    class zero_size {}; // размер 0
    class no_element {}; // нет запрашиваемого элемента
};

template <class Y>
class const_iterator
{
    using node = typename list<Y>::node;
    using const_reference = typename list<Y>::const_reference;
    node *nit = nullptr;
    // Конструкторы
    const_iterator() = default;
    explicit const_iterator(node *t) noexcept;
    // Сравнение итераторов
    bool operator==(const const_iterator &it) const noexcept;
    bool operator!=(const const_iterator &it) const noexcept;
    // Перемещение итератора
    const_iterator& operator++();
    const_iterator& operator--();
    const_reference operator*();   // разыменование
    bool isnull() const noexcept;
};

template <typename V>
void list<V>::size_checker(const size_type &size) const { if (size == 0) { throw zero_size(); } }
template <typename V>
void list<V>::element_checker(const size_type &i) const { if (i >= size) { throw no_element(); } }

template <typename V>
list<V>::list(const std::initializer_list<value_type> &v)
{
    size_checker(v.size()); // защита "от дурака"
    for (value_type i: v) { push_back(i); }
}
template <typename V>
list<V>::list(const list<V>& other)
{
    size_checker(other.get_size()); // защита "от дурака"
    for (iterator<V> i=iterator<V>(other.head); i.nit != nullptr; ++i) { push_back(*i); }
}
template <typename V>
list<V>::list(list<V> &&other): size(other.size), head(other.head), tail(other.tail)
{
    other.size = 0;
    other.head = nullptr;
    other.tail = nullptr;
}
template <typename V>
list<V> &list<V>::operator=(const list<V> &other)
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

template <typename V>
list<V> &list<V>::operator=(list<V> &&other) noexcept
{
    if (this != &other)
    {
        std::swap(size, other.size);
        std::swap(head, other.head);
        std::swap(tail, other.tail);
    }
    return *this;
}

template<class V>
list<V>::~list() { clear(); }

template<class V>
const_iterator<V> list<V>::begin() const noexcept { return const_iterator<V>(head); }

template<class V>
const_iterator<V> list<V>::end() const noexcept { return const_iterator<V>(tail); }

template <typename V>
typename list<V>::reference list<V>::front()
{
    size_checker(size);
    return head->item;
}

template <typename V>
typename list<V>::reference list<V>::back()
{
    size_checker(size);
    return tail->item;
}
template <typename V>
void list<V>::push_front(const_reference v)
{
    node *tmp = new node();

    tmp->item = v;
    tmp->next = nullptr;
    tmp->prev = nullptr;

    if(size != 0) {
        head->prev = tmp;
        tmp->next = head;
        head = tmp;
    } else { head = tail = tmp; }

    ++size;
}

template <typename V>
void list<V>::pop_front()
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

template <typename V>
void list<V>::push_back(const_reference v)
{
    node *tmp = new node();

    tmp->item = v;
    tmp->next = nullptr;
    tmp->prev = nullptr;

    if(size > 0) {
        tail->next = tmp;
        tmp->prev = tail;
        tail = tmp;
    } else { head = tail = tmp; }

    ++size;
}

template <typename V>
void list<V>::pop_back()
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

template <typename V>
void list<V>::set_i(const size_type &i, const_reference v)
{
    element_checker(i);
    node *it = head;
    for (size_type j=0; j < i; ++j) { it = it->next; }
    it->item = v;
}

template <typename V>
void list<V>::erase(const size_type &i)
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

template <typename V>
void list<V>::clear()
{
    while (size > 0) { pop_back(); }
}

template <typename V>
void list<V>::swap(list<V> &t) noexcept
{
    if (head != t.head)
    {
        std::swap(size, t.size);
        std::swap(head, t.head);
        std::swap(tail, t.tail);
    }

}

template<class V>
bool operator==(const typename list<V>::node &a, const typename list<V>::node &b) { return (a.item == b.item); }

template<class V>
bool operator!=(const typename list<V>::node &a, const typename list<V>::node &b) { return (a.item != b.item); }


template <typename V> template <typename Y>
list<V>::iterator<Y>::iterator(node *t) noexcept { nit = t; }

template<class V> template<class Y>
bool list<V>::iterator<Y>::operator==(const list<V>::iterator<Y> &it) const noexcept { return (nit == it.nit); }

template<class V> template<class Y>
bool list<V>::iterator<Y>::operator!=(const list<V>::iterator<Y> &it) const noexcept { return (nit != it.nit); }

template <typename V> template <typename Y>
typename list<V>::template iterator<Y> &list<V>::iterator<Y>::operator++()
{
    nit = nit->next;
    return (*this);
}

template <typename V> template <typename Y>
typename list<V>::template iterator<Y> &list<V>::iterator<Y>::operator--()
{
    nit = nit->prev;
    return (*this);
}

template <typename V> template <typename Y>
typename list<V>::reference list<V>::iterator<Y>::operator*() { return nit->item; }

template <typename V> template<class Y>
bool list<V>::iterator<Y>::isnull() const noexcept { return (nit == nullptr); }


template<class Y>
const_iterator<Y>::const_iterator(node *t) noexcept { nit = t; }

template<class Y>
bool const_iterator<Y>::operator==(const const_iterator &it) const noexcept { return (nit == it.nit); }

template<class Y>
bool const_iterator<Y>::operator!=(const const_iterator &it) const noexcept { return (nit != it.nit); }

template <typename Y>
const_iterator<Y> &const_iterator<Y>::operator++()
{
    nit = nit->next;
    return (*this);
}

template <typename Y>
const_iterator<Y> &const_iterator<Y>::operator--()
{
    nit = nit->prev;
    return (*this);
}

template <typename Y>
typename const_iterator<Y>::const_reference const_iterator<Y>::operator*() { return nit->item; }

template<class Y>
bool const_iterator<Y>::isnull() const noexcept { return (nit == nullptr); }

#endif // LIST_H

