#ifndef OCTAL_H
#define OCTAL_H

#include "array.h"

class octal: public Array
{
public:
    static const uint8_t num = 8; // восмиричная система

    // -- проверка на восьмиричность --
    inline void num_checker(value_type vt) { if (vt >= num) { throw no_8(); } }

    octal() = default;
    explicit octal(const size_type &n, value_type t = 0): Array(n, t)
    {
        num_checker(t);
        sokr();
    }
    octal(const std::string &source): Array(source)
    {
        for (size_type i=0; i<source.size(); ++i) { num_checker(value_type(source[i]-'0')); }
        sokr();
    }
    void sokr() noexcept; // Удаление лишних нулей в начале числа 0 0 0 1 2 3
    octal& dopcode(size_type n) noexcept; // перевод в доп код

    octal& operator+=(const octal &b) noexcept;
    octal& operator-=(const octal &b);
    octal& operator/=(const octal &b);
    octal& operator%=(const octal &b);
    octal& operator*=(const octal &b) noexcept;

    friend octal operator+(const octal &arr, const octal &b) noexcept;
    friend octal operator-(const octal &arr, const octal &b);
    friend octal operator/(const octal &arr, const octal &b) noexcept;
    friend octal operator%(const octal &arr, const octal &b) noexcept;
    friend octal operator*(const octal &arr, const octal &b) noexcept;

private:
    class no_8 {}; // не восмиричное
    class no_minus {}; // вычитатся большее число из малого
    class no_znam {};
};

#endif // OCTAL_H
