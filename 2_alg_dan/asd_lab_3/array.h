#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <tuple>
#include <string>

// -- типы --
using size_type = size_t;
using value_type = std::tuple<
                                int           /*0 - идентификационный номер*/,
                                uint8_t       /*1 - количество комнат*/,
                                double        /*2 - общая площадь*/,
                                double        /*3 - жилая площадь*/,
                                std::string   /*4 - дата постройки дома 01 01 2001*/,
                                double        /*5 - запрашиваемая стоимость*/,
                                std::string   /*6 - телефон продавца*/
                             >;     //-- ОСНОВНОЙ тип элементов --
class array
{
public:

    using iterator = value_type*;             // -- это просто указатель --
    using const_iterator = const value_type*; // -- нужен указатель на константу --
    using reference = value_type& ;
    using const_reference = const value_type& ;

    // -- проверки на нулевой размер и существование элемента --
    inline void size_checker(size_type size) const;
    inline void element_checker(size_type i) const;
    inline void value_checker(value_type v) const;

    // -- конструкторы и присваивания --
    array() = default;
    explicit array(const size_type& n, value_type v = value_type());
    array(const std::initializer_list<value_type> &v);
    array(const array& other);
    array(array&& other) noexcept;              // -- конструктор переноса --


    array& operator=(const array& other) noexcept;
    array& operator=(array&& other) noexcept;   // -- операция перемещания --

    inline ~array() {}

    // -- итераторы -- это просто указатели --
    // -- операции с итераторами - это стандартные операции с указателями --
    // -- защита от неправильных действий отсутствует --
    const_iterator begin() const noexcept { return apart; }
    iterator begin() noexcept { return apart; }

    iterator end() noexcept { return (apart+size); }
    const_iterator end() const noexcept { return (apart+size); }


    // -- доступ к элементам --
    reference operator[](size_type index);
    const_reference operator[](size_type index) const;

    reference front() noexcept { return apart[0]; }
    const_reference front() const noexcept { return apart[0]; }

    reference back() noexcept { return apart[size-1]; }
    const_reference back() const noexcept { return apart[size-1]; }


    // -- размеры --
    size_type get_size() const noexcept { return size; }            // текущее количество элементов

    bool empty() const noexcept { return (size > 0); }                 // есть ли элементы

    size_type get_capacity() const noexcept{ return capacity; }         // потенциальный размер

    // -- методы-модификаторы
    void push_back(const value_type& v);             // -- добавить элемент в конец --
    void pop_back() noexcept;                        // удалить последний элемент

    void erase(size_type idx); 			 // -- удалить элемент idx

    void clear() noexcept;    	     		 // очистить массив

    std::string toString() const noexcept;
// -- дружественные функции ввода/вывода --
    friend std::ostream &operator<<(std::ostream& t, const array &arr) noexcept;
    friend std::istream &operator>>(std::istream& t, array &arr);

    /* функции сравнения */
    friend bool operator==(const array &arr, const array &b) noexcept;
    friend bool operator!=(const array &arr, const array &b) noexcept;
    friend bool operator<(const array &arr, const array &b) noexcept;
    friend bool operator>(const array &arr, const array &b) noexcept;
    friend bool operator<=(const array &arr, const array &b) noexcept;
    friend bool operator>=(const array &arr, const array &b) noexcept;

private:
    size_type size = 0; // количество квартир
    size_type capacity = 0; // размер контейнера

    value_type *apart = nullptr; // квартиры


    class zero_size {}; // размер 0

    class no_element {}; // нет запрашиваемого элемента

    class id_8 {}; // идентификационный номер из 8 элементов
    class data_8 {}; // дата из 8 элементов
    class phone_11 {}; // номер из 11 элементов
};
#endif // ARRAY_H
