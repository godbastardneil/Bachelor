#include "pair.h"

std::istream& operator>>(std::istream &t, pair &p) noexcept
{
    int A;
    int B;
    t >> A >> B;
    p = pair(A, B);
    return t;
}

std::string pair::toString() noexcept { return "(" + std::to_string(a) + ", " + std::to_string(b) + ")"; }

std::ostream& operator<<(std::ostream &t, pair &p) noexcept { return (t << p.toString() << std::endl); }

//(a, b) * (c, d) = (a * c, b * d)
pair &pair::operator*=(const pair &sec) noexcept
{
    a *= sec.a;
    b *= sec.b;
    return *this;
}

//(a, b) – (c, d) = (a – b, c – d)
pair &pair::operator-=(const pair &sec) noexcept
{
    a -= sec.a;
    b -= sec.b;
    return *this;
}


pair operator-(const pair &fir, const pair &sec) noexcept
{
    pair tmp = fir;
    tmp -= sec;
    return tmp;
}
pair operator*(const pair &fir, const pair &sec) noexcept
{
    pair tmp = fir;
    tmp *= sec;
    return tmp;
}

/* функции сравнения */
bool operator==(const pair &fir, const pair &sec) noexcept { return (fir.a == sec.a) && (fir.b == sec.b); }
bool operator!=(const pair &fir, const pair &sec) noexcept { return !(fir == sec); }
bool operator<(const pair &fir, const pair &sec) noexcept { return (fir.a < sec.b) || (fir.a < sec.b); }
bool operator>(const pair &fir, const pair &sec) noexcept { return (fir.a > sec.b) || (fir.a > sec.b); }
bool operator<=(const pair &fir, const pair &sec) noexcept { return !(fir>sec); }
bool operator>=(const pair &fir, const pair &sec) noexcept { return !(fir<sec); }
