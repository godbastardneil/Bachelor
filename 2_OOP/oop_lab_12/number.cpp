#include "number.h"

void number::sokr() noexcept
{
    while (get_s()>1 && (*this)[0] == 0) { pop_forvard(); }
}

number& number::dopcode(size_type n) noexcept
{
    number tmp(n, num-1);
    size_type d = n - get_s();
    for (size_type i=d; i<n; ++i)
    {
        tmp[i] = num-1-(*this)[i-d];
    }
    ++tmp[n-1];
    (*this) = std::move(tmp);
    sokr();
    return (*this);
}

number& number::operator+=(const number &b) noexcept
{
    num = b.num;
    number o(b);
    std::reverse(begin(), end());
    std::reverse(o.begin(), o.end());
    size_type n = get_s()-1;
    size_type p = o.get_s()-1;
    if (n<p)
    {
        for (size_type i=n; i<p; ++i) { push_back(value_type(0)); }
        n = p;
    } else
    {
        for (size_type i=p; i<n; ++i) { o.push_back(value_type(0)); }
    }

    size_type s = 0;
    for (size_type i=0; i<n; ++i)
    {
        s += (*this)[i] + o[i];
        if (s>=num)
        {
            (*this)[i] = value_type(s%num);
            s = 1;
        } else
        {
            (*this)[i] = value_type(s);
            s = 0;
        }
    }
    s += (*this)[n] + o[n];
    if (s>=num)
    {
        (*this)[n] = value_type(s%num);
        push_back(value_type(s/num));
    } else { (*this)[n] = value_type(s); }

    std::reverse(begin(), end());
    sokr();
    return (*this);
}
number& number::operator-=(const number &b)
{
    if ((*this)<b) { throw no_minus(); }

    num = b.num;
    size_type n = b.get_s();
    number o(b);
    o.num = num;
    o.dopcode(n);
    (*this) += o;

    if (get_s() > o.get_s()) { pop_forvard(); }
    sokr();

    return (*this);
}
number& number::operator/=(const number &b)
{
    if (b == number(1, 0)) { throw no_znam(); }
    if ((*this) == b)
    {
        (*this) = number(1, 1);
    }
    else if ((*this) < b)
    {
        (*this) = number(1, 0);
    }
    else
    {
        number o = (*this);
        num = b.num;
        (*this) = number(1, 0);
        if (b == (*this)) { throw no_znam(); }
        number one(1, 1);
        one.num = num;
        while (o>=b)
        {
            o -= b;
            (*this) += one;
        }
    }
    return (*this);
}
number& number::operator%=(const number &b)
{
    if (b == number(1, 0)) { throw no_znam(); }
    while ((*this)>=b) { (*this) -= b; }
    return (*this);
}
number& number::operator*=(const number &b) noexcept
{
    number o;
    number o1;
    if ((*this) < b)
    {
        o = (*this);
        o1 = b;
    } else
    {
        o = b;
        o1 = (*this);
    }
    num = b.num;
    (*this) = number(1, 0);
    while (o>number(1, 0))
    {
        (*this) += o1;
        o -= number(1, 1);
    }
    return (*this);
}

number operator+(const number &a, const number &b) noexcept
{
    number tmp = a;
    tmp.num = a.num;
    tmp += b;
    return tmp;
}
number operator-(const number &a, const number &b)
{
    number tmp = a;
    tmp.num = a.num;
    tmp -= b;
    return tmp;
}
number operator/(const number &a, const number &b)
{
    number tmp = a;
    tmp.num = a.num;
    tmp /= b;
    return tmp;
}
number operator%(const number &a, const number &b)
{
    number tmp = a;
    tmp.num = a.num;
    tmp %= b;
    return tmp;
}
number operator*(const number &a, const number &b) noexcept
{
    number tmp = a;
    tmp.num = a.num;
    tmp *= b;
    return tmp;
}
