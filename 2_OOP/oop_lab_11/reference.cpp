#include "reference.h"
#include "array.h"

reference &reference::operator=(const value_type &t)
{
    strm.arr[pos] = t;
    return (*this);
}

reference &reference::operator+=(const value_type &t)
{
    strm.arr[pos] += t;
    return (*this);
}
reference &reference::operator-=(const value_type &t)
{
    strm.arr[pos] -= t;
    return (*this);
}
reference &reference::operator*=(const value_type &t)
{
    strm.arr[pos] *= t;
    return (*this);
}
reference &reference::operator/=(const value_type &t)
{
    strm.arr[pos] /= t;
    return (*this);
}
reference &reference::operator&=(const value_type &t)
{
    strm.arr[pos] &= t;
    return (*this);
}
reference &reference::operator|=(const value_type &t)
{
    strm.arr[pos] |= t;
    return (*this);
}
reference &reference::operator^=(const value_type &t)
{
    strm.arr[pos] ^= t;
    return (*this);
}
reference &reference::operator%=(const value_type &t)
{
    strm.arr[pos] %= t;
    return (*this);
}

reference &reference::operator++()
{
    ++strm.arr[pos];
    return (*this);
}
reference &reference::operator--()
{
    --strm.arr[pos];
    return (*this);
}

reference::operator value_type() const { return strm.arr[pos]; }

const_reference::operator value_type() const { return strm.arr[pos]; }
