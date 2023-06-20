#ifndef ARRAY_H
#define ARRAY_H

#include "types.h"

class array
{
public:
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

    a_iterator begin() noexcept { return a_iterator(apart); }
    const a_iterator begin() const noexcept { return a_iterator(apart); }
    a_iterator end() noexcept { return a_iterator(apart+size); }
    const a_iterator end() const noexcept { return a_iterator(apart+size); }

    // -- доступ к элементам --
    reference operator[](const size_type &index);
    const_reference operator[](const size_type &index) const;

    reference front() noexcept { return apart[0]; }
    const_reference front() const noexcept { return apart[0]; }
    reference back() noexcept { return apart[size-1]; }
    const_reference back() const noexcept { return apart[size-1]; }

    // -- размеры --
    size_type get_size() const noexcept { return size; }            // текущее количество элементов

    bool empty() const noexcept { return !(size == 0); }                 // есть ли элементы

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
#endif // ARRAY_H
