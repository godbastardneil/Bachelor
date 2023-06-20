#ifndef LONG_H
#define LONG_H

#include <iostream>
#include <string>
#include <algorithm>


class Long
{
private:
    uint32_t f;
    uint32_t s;


    class more_then_20{};
    class no_znam{};

    friend void delenie(Long &chis, const Long &znam, Long &result);

public:
    Long(const uint32_t &S = 0) noexcept: f(0), s(S) {}
    Long(const uint32_t &F, const uint32_t &S) noexcept: f(F), s(S) {}
    Long(std::string ss): f(0), s(0)
    {
        size_t n = ss.size();
        if (n > 20) { throw more_then_20(); }
        size_t i=0;
        while(ss[i] == '0') { ss.erase(i); }
        n = ss.size();
        if (n)
        {
            s = uint32_t(ss[i++]-'0');
            while (i<n)
            {
                (*this) *= 10;
                (*this) += uint32_t(ss[i++]-'0');
            }
        }
    }

    Long& dopcode() noexcept; // перевод в доп код
    std::string toString() const noexcept ; // перевод в string

    Long &operator++() noexcept; // перфиксный инкремент
    Long &operator--() noexcept; // перфиксный декремент
    Long operator++(int) noexcept; // постфиксный инкремент
    Long operator--(int) noexcept;  // постфиксный декремент

    Long &operator+=(const Long &sec) noexcept; // Сумма
    Long &operator-=(const Long &sec) noexcept; // вычитание
    Long &operator*=(const Long &sec) noexcept; // умножение
    Long &operator/=(const Long &sec); // целочисленное деление
    Long &operator%=(const Long &sec); // осаток от целочисленного деления


    friend std::istream& operator>>(std::istream& t, Long &p) noexcept; // ввод
    friend std::ostream& operator<<(std::ostream& t, Long &p) noexcept; // вывод

    friend Long operator+(const Long &fir, const Long &sec) noexcept; // Сумма
    friend Long operator-(const Long &fir, const Long &sec) noexcept; // вычитание
    friend Long operator*(const Long &fir, const Long &sec) noexcept; // умножение
    friend Long operator/(const Long &fir, const Long &sec); // деление
    friend Long operator%(const Long &fir, const Long &sec); // деление
    /* функции сравнения */
    friend bool operator==(const Long &fir, const Long &sec) noexcept;
    friend bool operator!=(const Long &fir, const Long &sec) noexcept;
    friend bool operator<(const Long &fir, const Long &sec) noexcept;
    friend bool operator>(const Long &fir, const Long &sec) noexcept;
    friend bool operator<=(const Long &fir, const Long &sec) noexcept;
    friend bool operator>=(const Long &fir, const Long &sec) noexcept;
};

#endif // LONG_H
