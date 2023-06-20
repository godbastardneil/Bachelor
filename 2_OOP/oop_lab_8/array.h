#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

class Array
{
public:
    using size_type = size_t;        // -- тип размера --
    using value_type = uint8_t;      //-- ОСНОВНОЙ тип элементов --

    // -- проверки на нулевой размер и существование элемента --
    inline void size_checker(size_type s) const { if (s == 0) { throw zero_size(); } }
    inline void element_checker(size_type i) const { if (i >= size) { throw no_element(); } }

// -- конструкторы и присваивание --
    Array() = default;
    explicit Array(size_type n, value_type t = 0)
    {
        size_checker(n); // защита "от дурака"

        size = n; // размер массива
        arr = new value_type[size]; // новый массив
        std::fill(begin(), end(), t); // заполние arr элементов t
    }
    Array(const Array& other) noexcept: size(other.size), arr(new value_type[size])
    {
        std::copy(other.begin(), other.end(), begin()); // копирование
    }
    Array(Array&& other) noexcept: size(other.size), arr(other.arr)
    {
        other.size = 0;
        other.arr = nullptr;
    }

    Array(const std::string &source): Array(source.size()) // создаю массив размера сроки, заполненый нулями
    {
        size_type i = 0;
        for (char a: source)
        {
            arr[i] = value_type(a-'0'); // копирование
            ++i;
        }
    }
    ~Array() { delete []arr; }

    Array& operator=(const Array& other) noexcept;
    Array& operator=(Array&& other) noexcept;

    value_type &operator[](size_type index);
    const value_type &operator[](size_type index) const;

    inline size_type get_s() const noexcept { return size; }

    inline value_type *begin() const noexcept { return arr; }
    inline value_type *end() const noexcept { return (arr+size); }

    inline void clear() noexcept; // очистить Array
    void pop_back(); // удалить элемент в конце
    void pop_forvard(); // удалить элемент в начале
    void push_back(value_type t = 0) noexcept; // добавить элемент в конец
    void push_forvard(value_type t = 0) noexcept; // доавить элемент в начало

    std::string toString() const noexcept;
// -- дружественные функции ввода/вывода --
    friend std::ostream& operator<<(std::ostream& t, const Array &arr) noexcept;
    friend std::istream &operator>>(std::istream& t, Array &arr);

    /* функции сравнения */
    friend bool operator==(const Array &arr, const Array &b) noexcept;
    friend bool operator!=(const Array &arr, const Array &b) noexcept;
    friend bool operator<(const Array &arr, const Array &b) noexcept;
    friend bool operator>(const Array &arr, const Array &b) noexcept;
    friend bool operator<=(const Array &arr, const Array &b) noexcept;
    friend bool operator>=(const Array &arr, const Array &b) noexcept;

private:
    size_type size = 0;
    value_type* arr = nullptr;

    class zero_size {}; // размер 0
    class no_element {}; // нет запрашиваемого элемента
};

#endif // ARRAY_H
