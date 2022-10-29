#ifndef TYPES_H
#define TYPES_H

#include <iostream>
#include <tuple>
#include <string>
#include <sstream>

// -- типы --
using size_type = size_t;
using data_type = std::tuple<uint8_t, uint8_t, uint>;
using value_type = std::tuple<  std::string  /*0 - номер договора*/,
                                std::string  /*1 - телефон*/,
                                data_type /*2 - дата заключения договора 01 01 2001*/,
                                double    /*3 - оплата за установку*/,
                                double    /*4 - тариф помесячный*/

                             >; //-- ОСНОВНОЙ тип элементов --
using reference = value_type& ;
using const_reference = const value_type& ;

struct node
{
    node(const value_type &v):item(v) {}
    node() {}
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
struct reverse_iterator
{
    node *nit = nullptr;
    // Конструкторы
    reverse_iterator() = default;
    explicit reverse_iterator(node *t) noexcept { nit = t; }
    ~reverse_iterator() { delete nit; }
    // Сравнение итераторов
    bool operator==(const reverse_iterator &it) const noexcept { return (nit == it.nit); }
    bool operator!=(const reverse_iterator &it) const noexcept { return !(nit == it.nit); }
    // Перемещение итератора
    reverse_iterator& operator++()              // вперед
    {
        nit = nit->prev;
        return (*this);
    }
    reverse_iterator& operator--()              // назад
    {
        nit = nit->next;
        return (*this);
    }
    reference operator*() { return nit->item; }   // разыменование
};
struct const_reverse_iterator
{
    node *nit = nullptr;
    // Конструкторы
    const_reverse_iterator() = default;
    explicit const_reverse_iterator(node *t) noexcept { nit = t; }
    ~const_reverse_iterator() { delete nit; }
    // Сравнение итераторов
    bool operator==(const const_reverse_iterator &it) const noexcept { return (nit == it.nit); }
    bool operator!=(const const_reverse_iterator &it) const noexcept { return !(nit == it.nit); }
    // Перемещение итератора
    const_reverse_iterator& operator++()              // вперед
    {
        nit = nit->prev;
        return (*this);
    }
    const_reverse_iterator& operator--()              // назад
    {
        nit = nit->next;
        return (*this);
    }
    reference operator*() { return nit->item; }   // разыменование
};

struct a_iterator
{
    value_type *nit = nullptr;
    // Конструкторы
    a_iterator() = default;
    explicit a_iterator(value_type *t) noexcept { nit = t; }
    ~a_iterator() { delete nit; }
    // Сравнение итераторов
    bool operator==(const a_iterator &it) const noexcept { return (nit == it.nit); }
    bool operator!=(const a_iterator &it) const noexcept { return !(nit == it.nit); }
    // Перемещение итератора
    a_iterator& operator++()              // вперед
    {
        ++nit;
        return (*this);
    }
    a_iterator& operator--()              // назад
    {
        --nit;
        return (*this);
    }
    reference operator*() { return *nit; }   // разыменование
};
#endif // TYPES_H
