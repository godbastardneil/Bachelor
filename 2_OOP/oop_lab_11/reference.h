#ifndef REFERENCE_H
#define REFERENCE_H

#include <iostream>

using size_type = size_t;        // -- тип размера --
using value_type = uint8_t;      //-- ОСНОВНОЙ тип элементов --

class Array;

class reference
{
public:
    // Конструктор proxy-объекта
    reference(Array &a, size_type index) noexcept: strm(a), pos(index) {}

    reference& operator=(const value_type &t);			// l-value

    reference& operator+=(const value_type &t);
    reference& operator-=(const value_type &t);
    reference& operator*=(const value_type &t);
    reference& operator/=(const value_type &t);
    reference& operator&=(const value_type &t);
    reference& operator|=(const value_type &t);
    reference& operator^=(const value_type &t);
    reference& operator%=(const value_type &t);

    reference& operator++();
    reference& operator--();

    operator value_type() const;								// r-value

private:
    friend class Array;     // основной класс - друг

    Array &strm;            // ссылка на основной класс
    size_type  pos;         // позиция на диске = индекс в основном классе
};

class const_reference
{
public:
    // Конструктор proxy-объекта
    const_reference(const Array &a, size_type index) noexcept: strm(a), pos(index) {}

    operator value_type() const;								// r-value

private:
    friend class Array;     // основной класс - друг

    const Array &strm;            // ссылка на основной класс
    size_type  pos;         // позиция на диске = индекс в основном классе
};

#endif // REFERENCE_H
