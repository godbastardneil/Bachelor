#ifndef RATIONAL_H
#define RATIONAL_H

#include <pair.h>

class rational: public pair
{
public:
    class Zero{}; //  исключение, когда вводят в знаменатель 0
    rational() noexcept: pair(1, 1){}
    rational(int c, int z): pair(c, z)
    {
        if(z ==0) { throw Zero(); }
    }
    ~rational() override {}

    int get_a () noexcept { return pair::get_a(); }
    int get_b () noexcept { return pair::get_b(); }

    rational& operator+=(const rational &sec) noexcept; // сложение с присваиванием
    rational& operator/=(const rational &sec) noexcept; // деление с присваиванием
    pair& operator-=(const pair &sec) noexcept override; // вычитание с присваиванием -- переопределена


    friend rational operator+(const rational &fir, const rational &sec) noexcept; // сложение
    friend rational operator/(const rational &fir, const rational &sec) noexcept; // деление
    friend rational operator-(const rational &fir, const rational &sec) noexcept; // вычитание

    friend rational operator*(const rational &fir, const rational &sec) noexcept; // умножение
};

#endif // RATIONAL_H
