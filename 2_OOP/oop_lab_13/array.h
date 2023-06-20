#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <tuple>
#include <string>
#include <sstream>

template <class V>
class array
{
public:
    using size_type = size_t;
    using value_type = V;
    using reference = value_type&;
    using const_reference = const value_type&;
    struct iterator
    {
        value_type *nit = nullptr;
        // Конструкторы
        iterator() = default;
        explicit iterator(value_type *t) noexcept;
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

    // -- конструкторы и присваивания --
    array() = default;
    explicit array(const size_type &n, const_reference v = value_type());
    array(const std::initializer_list<value_type> &v);
    array(const array& other);
    array(array&& other) noexcept;              // -- конструктор переноса --

    array& operator=(const array& other) noexcept;
    array& operator=(array&& other) noexcept;   // -- операция перемещания --

    virtual ~array() { delete[] apart; }

    iterator begin() const noexcept { return iterator(apart); }
    iterator end() const noexcept { return iterator(apart+size); }

    // -- доступ к элементам --
    reference operator[](const size_type &index);
    const_reference operator[](const size_type &index) const;

    reference front() noexcept { return apart[0]; }
    const_reference front() const noexcept { return apart[0]; }
    reference back() noexcept { return apart[size-1]; }
    const_reference back() const noexcept { return apart[size-1]; }

    // -- размеры --
    size_type get_size() const noexcept { return size; }            // текущее количество элементов
    bool empty() const noexcept { return (size == 0); }                 // есть ли элементы

    // -- методы-модификаторы
    void push_back(const_reference v);             // -- добавить элемент в конец --
    void pop_back() noexcept;                        // удалить последний элемент

    void push_front(const_reference v);            // -- добавить элемент в начало --
    void pop_front() noexcept;                       // удалить первый элемент

    void erase(const size_type &idx); 			 // -- удалить элемент idx

    void clear() noexcept;    	     		 // очистить массив
    void swap(array& rhs);              // -- обмен массивов - типа перемещения --

    std::string to_String() const noexcept;

private:
    size_type size = 0; // количество квартир

    value_type *apart = nullptr;

    class zero_size {}; // размер 0
    class no_element {}; // нет запрашиваемого элемента
};

template <typename V>
void array<V>::size_checker(const size_type &size) const { if (size == 0) { throw zero_size(); } }
template <typename V>
void array<V>::element_checker(const size_type &i) const { if (i >= size) { throw no_element(); } }

template <typename V>
array<V>::array(const size_type &n, const_reference v)
{
    size_checker(n);
    size = n;
    apart = new value_type[size];
    for (size_type i=0; i<size; ++i) { apart[i] = v; }
}

template <typename V>
array<V>::array(const std::initializer_list<value_type> &v): array(v.size())
{
    int i = 0;
    for (value_type val: v) { apart[i] = val; ++i; }
}
template <typename V>
array<V>::array(const array& other): size(other.size), apart(new value_type[other.size])
{
    for(size_type i=0; i<size; ++i) { apart[i] = other[i]; }
}
template <typename V>
array<V>::array(array&& other) noexcept: size(other.size), apart(other.apart)
{
    other.size = 0;
    other.apart = nullptr;
}

template <typename V>
array<V> &array<V>::operator=(const array &other) noexcept
{
    if (this != &other) // самоприсваивание
    {
        array tmp(other);
        std::swap(size, tmp.size);
        std::swap(apart, tmp.apart);
    }
    return *this;
}
template <typename V>
array<V> &array<V>::operator=(array &&other) noexcept
{
    if (this != &other) // самоприсваивание
    {
        std::swap(size, other.size);
        std::swap(apart, other.apart);
    }
    return *this;
}

template <typename V>
typename array<V>::reference array<V>::operator[](const size_type &index)
{
    element_checker(index);
    return apart[index];
}
template <typename V>
typename array<V>::const_reference array<V>::operator[](const size_type &index) const
{
    element_checker(index);
    return apart[index];
}

template <typename V>
void array<V>::push_back(const_reference v)
{
    array a(size+1, v);
    for (size_type i=0; i<size; ++i) { a[i] = (*this)[i]; }
    ++size;
    (*this) = std::move(a);
}
template <typename V>
void array<V>::pop_back() noexcept
{
    array a(size-1);
    for (size_type i=0; i<size-1; ++i) { a[i] = (*this)[i]; }
    --size;
    (*this) = std::move(a);
}

template <typename V>
void array<V>::push_front(const_reference v)
{
    array a(size+1, v);
    for (size_type i=0; i<size; ++i) { a[i+1] = (*this)[i]; }
    ++size;
    (*this) = std::move(a);
}
template <typename V>
void array<V>::pop_front() noexcept
{
    array a(size-1);
    for (size_type i=0; i<size-1; ++i) { a[i] = (*this)[i+1]; }
    --size;
    (*this) = std::move(a);
}

template <typename V>
void array<V>::erase(const size_type &idx)
{
    if (idx == 0)
    {
        pop_front();
    } else if (idx == size-1)
    {
        pop_back();
    } else if (idx < size)
    {
        array a(--size);
        for (size_type i=0; i<idx; ++i) { a[i] = (*this)[i]; }
        for (size_type i=idx+1; i<size+1; ++i) { a[i] = (*this)[i]; }
        (*this) = std::move(a);
    }
}
template <typename V>
void array<V>::clear() noexcept
{
    size = 0;
    delete[] apart;
    apart = nullptr;
}

template <typename V>
array<V>::iterator::iterator(array<V>::value_type *t) noexcept
{
    nit = t;
}
template <typename V>
bool array<V>::iterator::operator==(const array<V>::iterator &it) const noexcept
{
    return (nit == it.nit);
}
template <typename V>
bool array<V>::iterator::operator!=(const array<V>::iterator &it) const noexcept
{
    return !(*this == it);
}
template <typename V>
typename array<V>::iterator &array<V>::iterator::operator++()
{
    ++nit;
    return *this;
}
template <typename V>
typename array<V>::iterator &array<V>::iterator::operator--()
{
    --nit;
    return *this;
}
template <typename V>
typename array<V>::reference array<V>::iterator::operator*()
{
    return *nit;
}
template <typename V>
bool array<V>::iterator::isnull() const noexcept
{
    return (nit == nullptr);
}
#endif // ARRAY_H
