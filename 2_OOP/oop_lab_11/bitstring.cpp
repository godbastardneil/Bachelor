#include "bitstring.h"

bitstring& bitstring::operator&=(const bitstring &b)
{
    bitstring o, o1;
    if (get_s() > b.get_s())
    {
        o = b;
        o1 = (*this);
    } else
    {
        o = (*this);
        o1 = b;
    }
    size_type n = o1.get_s();
    for (size_type i=0; i<n; ++i) { o[i] &= o1[i]; }

    (*this) = std::move(o);
    return (*this);
}
bitstring& bitstring::operator|=(const bitstring &b)
{
    bitstring o, o1;
    if (get_s() > b.get_s())
    {
        o = b;
        o1 = (*this);
    } else
    {
        o = (*this);
        o1 = b;
    }
    size_type n = o1.get_s();
    for (size_type i=0; i<n; ++i) { o[i] |= o1[i]; }

    (*this) = std::move(o);
    return (*this);
}
bitstring& bitstring::operator^=(const bitstring &b)
{
    bitstring o, o1;
    if (get_s() > b.get_s())
    {
        o = b;
        o1 = (*this);
    } else
    {
        o = (*this);
        o1 = b;
    }
    size_type n = o1.get_s();
    for (size_type i=0; i<n; ++i) { o[i] ^= o1[i]; }

    (*this) = std::move(o);
    return (*this);
}
bitstring& bitstring::operator<<=(const size_type &s)
{
    bitstring tmp(get_s()+s);
    std::move(begin(), end(), tmp.begin());
    (*this) = std::move(tmp);
    return (*this);
}
bitstring& bitstring::operator>>=(const size_type &s)
{
    bitstring tmp(get_s()+s);
    std::move(begin(), end(), tmp.begin()+s);
    (*this) = std::move(tmp);
    return (*this);
}

bitstring bitstring::operator~()
{
    bitstring tmp = (*this);
    for (size_t i=0; i<get_s(); ++i) { tmp[i] = 1 - tmp[i]; }
    return tmp;
}

bitstring operator<<(const bitstring &a, const size_type &s)
{
    bitstring tmp = a;
    tmp <<= s;
    return tmp;
}

bitstring operator>>(const bitstring &a, const size_type &s)
{
    bitstring tmp = a;
    tmp >>= s;
    return tmp;
}


bitstring operator&(const bitstring &a, const bitstring &b)
{
    bitstring tmp = a;
    tmp &= b;
    return tmp;
}
bitstring operator|(const bitstring &a, const bitstring &b)
{
    bitstring tmp = a;
    tmp |= b;
    return tmp;
}
bitstring operator^(const bitstring &a, const bitstring &b)
{
    bitstring tmp = a;
    tmp ^= b;
    return tmp;
}
