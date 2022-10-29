#include "rational.h"

// (a, b) + (c, d) = (a * d + b * c, b * d)
rational &rational::operator+=(const rational &sec) noexcept
{
    set_a(get_a()*sec.pair::get_b() + get_b()*sec.pair::get_a());
    set_b(get_b()*sec.pair::get_b());
    return *this;
}

// (a, b) / (c, d) = (a * d, b * c)
rational &rational::operator/=(const rational &sec) noexcept
{
    set_a(get_a()*sec.pair::get_b());
    set_b(get_b()*sec.pair::get_a());
    return *this;
}

//(a, b) – (c, d) = (ad – bc, bd)
pair &rational::operator-=(const pair &sec) noexcept
{
    set_a(get_a()*sec.get_b() - get_b()*sec.get_a());
    set_b(get_b()*sec.get_b());
    return *this;
}

rational operator+(const rational &fir, const rational &sec) noexcept
{
    rational tmp = fir;
    tmp += sec;
    return tmp;
}

rational operator/(const rational &fir, const rational &sec) noexcept
{
    rational tmp = fir;
    tmp /= sec;
    return tmp;
}

rational operator-(const rational &fir, const rational &sec) noexcept
{
    rational tmp = fir;
    tmp -= sec;
    return tmp;
}

rational operator*(const rational &fir, const rational &sec) noexcept
{
    rational tmp = fir;
    tmp *= sec;
    return tmp;
}
