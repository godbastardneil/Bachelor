#ifndef MONEY_H
#define MONEY_H

#include <iostream>
#include <string>

class money
{
private:
    unsigned long long r;
    unsigned char c;
public:
    class less_then_0 {}; // исключение меньше 0
    class more_then_99 {}; // исключение введено копеек больше, чем 99

    money() noexcept: r(0), c(0) {}
    money(unsigned long long R, unsigned char C=0)
    {
        if (C > 99) { throw more_then_99(); }
        r = R;
        c = C;
    }

    std::string toString() noexcept; // перевод в string // вывод

    void set_c (const unsigned char &C)
    {
        if (C > 99) { throw more_then_99();}
        c = C;
    }
    void set_r (const unsigned long long  &R) noexcept { r = R; } // ввод r

    unsigned long long get_r () const { return r; }
    u_char get_c () const { return c; }

    double to_cop () const noexcept { return (double(r)*100 + c); }

    money& operator+=(const money &b) noexcept; // сложение с присваиванием
    money& operator-=(const money &b); // вычитание с присваиванием

    double operator/(const money &b) noexcept; // деление на money
    double operator/(const double &b) noexcept; // деление на число

    money& operator*=(const double &b) noexcept; // умножение с присваиванием
    money& operator*=(const money &b) noexcept; // умножение с присваиванием


    friend std::istream& operator>>(std::istream& t, money &m);

    friend std::ostream& operator<<(std::ostream& t, money &m) noexcept;

    friend money operator+(const money &a, const money &b) noexcept; // сложение
    friend money operator-(const money &a, const money &b); // вычитание, может быть исключение less_then_0
    friend money operator*(const money &a, const money &b) noexcept; // сложение
    friend money operator*(const money &a, const double &b) noexcept; // сложение
};

#endif // MONEY_H
