#include "twelve.h"

void twelve::sokr() noexcept
{
    while (get_s()>1 && (*this)[0] == 0) { pop_forvard(); }
}

twelve& twelve::dopcode(size_type n) noexcept
{
    twelve tmp(n, num-1);
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

twelve& twelve::operator+=(const twelve &b) noexcept
{
    twelve o(b);
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
twelve& twelve::operator-=(const twelve &b)
{
    if ((*this)<b) { throw no_minus(); }
    twelve o(b);
    o.dopcode(get_s());

    (*this) += o;
    std::reverse(begin(), end());
    if (get_s() > o.get_s()) { pop_back(); }
    std::reverse(begin(), end());
    sokr();

    return (*this);
}
twelve& twelve::operator/=(const twelve &b)
{
    if (b == twelve(1, 0)) { throw no_znam(); }
    twelve o = (*this);
    (*this) = twelve(1, 0);
    twelve one(1, 1);
    while (o>=b)
    {
        o -= b;
        (*this) += one;
    }
    return (*this);
}
twelve& twelve::operator%=(const twelve &b)
{
    if (b == twelve(1, 0)) { throw no_znam(); }
    while ((*this)>=b) { (*this) -= b; }
    return (*this);
}
twelve& twelve::operator*=(const twelve &b) noexcept
{
    twelve o;
    twelve o1;
    if ((*this) < b)
    {
        o = (*this);
        o1 = b;
    } else
    {
        o = b;
        o1 = (*this);
    }
    (*this) = twelve(1, 0);
    while (o>twelve(1, 0))
    {
        (*this) += o1;
        o -= twelve(1, 1);
    }
    return (*this);
}

twelve operator+(const twelve &a, const twelve &b) noexcept
{
    twelve tmp = a;
    tmp += b;
    return tmp;
}
twelve operator-(const twelve &a, const twelve &b)
{
    twelve tmp = a;
    tmp -= b;
    return tmp;
}
twelve operator/(const twelve &a, const twelve &b) noexcept
{
    twelve tmp = a;
    tmp /= b;
    return tmp;
}
twelve operator%(const twelve &a, const twelve &b) noexcept
{
    twelve tmp = a;
    tmp %= b;
    return tmp;
}
twelve operator*(const twelve &a, const twelve &b) noexcept
{
    twelve tmp = a;
    tmp *= b;
    return tmp;
}
