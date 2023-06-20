#ifndef TWELVE_H
#define TWELVE_H

#include "array.h"

class twelve: public Array
{
public:
    static const uint8_t num = 12; // восмиричная система

    // -- проверка на восьмиричность --
    inline void num_checker(const value_type &vt) { if (vt >= num) { throw no_12(); } }

    twelve() = default;
    explicit twelve(const size_type &n, value_type t = 0): Array(n, t)
    {
        num_checker(t);
        sokr();
    }
    twelve(const std::initializer_list<value_type> &v) : Array(v)
    {
        for (value_type i:v) { num_checker(i); }
    }
    twelve(const std::string &source): Array(source)
    {
        for (char i:source) { num_checker(i-'0'); }
        sokr();
    }
    void sokr() noexcept; // Удаление лишних нулей в начале числа 0 0 0 1 2 3
    twelve& dopcode(size_type n) noexcept; // перевод в доп код

    twelve& operator+=(const twelve &b) noexcept;
    twelve& operator-=(const twelve &b);
    twelve& operator/=(const twelve &b);
    twelve& operator%=(const twelve &b);
    twelve& operator*=(const twelve &b) noexcept;

    friend twelve operator+(const twelve &arr, const twelve &b) noexcept;
    friend twelve operator-(const twelve &arr, const twelve &b);
    friend twelve operator/(const twelve &arr, const twelve &b) noexcept;
    friend twelve operator%(const twelve &arr, const twelve &b) noexcept;
    friend twelve operator*(const twelve &arr, const twelve &b) noexcept;

private:
    class no_12 {}; // не двенацетиричный
    class no_minus {}; // вычитатся большее число из малого
    class no_znam {};
};

#endif // TWELVE_H
