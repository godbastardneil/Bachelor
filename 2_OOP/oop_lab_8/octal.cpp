#include "octal.h"

void octal::sokr() noexcept
{
    while (get_s()>1 && (*this)[0] == 0) { pop_forvard(); }
}

octal& octal::dopcode(Array::size_type n) noexcept
{
    octal tmp(n, num-1);
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

octal& octal::operator+=(const octal &b) noexcept
{
    octal o(b);
    std::reverse(begin(), end());
    std::reverse(o.begin(), o.end());
    size_type n = get_s()-1;
    size_type p = o.get_s()-1;
    if (n<p)
    {
        for (size_type i=n; i<p; ++i) { push_back(); }
        n = p;
    } else
    {
        for (size_type i=p; i<n; ++i) { o.push_back(); }
    }

    int s = 0;
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
octal& octal::operator-=(const octal &b)
{
    if ((*this)<b) { throw no_minus(); }
    octal o(b);
    o.dopcode(get_s());

    (*this) += o;
    std::reverse(begin(), end());
    if (get_s() > o.get_s()) { pop_back(); }
    std::reverse(begin(), end());
    sokr();

    return (*this);
}
octal& octal::operator/=(const octal &b)
{
    if (b == octal(1, 0)) { throw no_znam(); }
    if ((*this) == b)
    {
        (*this) = octal(1, 1);
    }
    else if ((*this) < b)
    {
        (*this) = octal(1, 0);
    }
    else
    {
        octal o = (*this);
        (*this) = octal(1, 0);
        if (b == (*this)) { throw no_znam(); }
        octal one(1, 1);
        while (o>=b)
        {
            o -= b;
            (*this) += one;
        }
    }
    return (*this);
}
octal& octal::operator%=(const octal &b)
{
    if (b == octal(1, 0)) { throw no_znam(); }
    while ((*this)>=b) { (*this) -= b; }
    return (*this);
}
octal& octal::operator*=(const octal &b) noexcept
{
    octal o;
    octal o1;
    if ((*this) < b)
    {
        o = (*this);
        o1 = b;
    } else
    {
        o = b;
        o1 = (*this);
    }
    (*this) = octal(1, 0);
    while (o>octal(1, 0))
    {
        (*this) += o1;
        o -= octal(1, 1);
    }
    return (*this);
}

octal operator+(const octal &a, const octal &b) noexcept
{
    octal tmp = a;
    tmp += b;
    return tmp;
}
octal operator-(const octal &a, const octal &b)
{
    octal tmp = a;
    tmp -= b;
    return tmp;
}
octal operator/(const octal &a, const octal &b) noexcept
{
    octal tmp = a;
    tmp /= b;
    return tmp;
}
octal operator%(const octal &a, const octal &b) noexcept
{
    octal tmp = a;
    tmp %= b;
    return tmp;
}
octal operator*(const octal &a, const octal &b) noexcept
{
    octal tmp = a;
    tmp *= b;
    return tmp;
}
