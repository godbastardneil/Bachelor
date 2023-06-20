#ifndef PAIR_H
#define PAIR_H

#include <iostream>
#include <string>

class pair
{
private:
    int a;
    int b;
public:
    pair() noexcept: a(0), b(0) {}
    pair(int C, int Z) noexcept
    {
        a = C;
        b = Z;
    }
    virtual ~pair() {}

    std::string toString() noexcept; // перевод в string

    inline void set_a (int A) noexcept { a = A; }
    inline void set_b (int B) noexcept { b = B; }

    inline int get_a () const noexcept { return a; }
    inline int get_b () const noexcept { return b; }

    pair& operator*=(const pair &sec) noexcept; // умножение с присваиванием

    // переопределяется в rational
    virtual pair& operator-=(const pair &sec) noexcept; // вычитание с присваиванием


    friend std::istream& operator>>(std::istream& t, pair &p) noexcept; // ввод
    friend std::ostream& operator<<(std::ostream& t, pair &p) noexcept; // вывод

    friend pair operator*(const pair &fir, const pair &sec) noexcept; // умножение
    friend pair operator-(const pair &fir, const pair &sec) noexcept; // вычитание
    /* функции сравнения */
    friend bool operator==(const pair &fir, const pair &sec) noexcept;
    friend bool operator!=(const pair &fir, const pair &sec) noexcept;
    friend bool operator<(const pair &fir, const pair &sec) noexcept;
    friend bool operator>(const pair &fir, const pair &sec) noexcept;
    friend bool operator<=(const pair &fir, const pair &sec) noexcept;
    friend bool operator>=(const pair &fir, const pair &sec) noexcept;
};

#endif // PAIR_H
