#include "bit.h"

void bit::CheckForBinary(const Array &arr) const
{
    bool b = std::all_of(arr.begin(),arr.end(),
                   [] (value_type c) {
                    return (c < num_sys);
                    });
    if (!b) throw not_binery_exception();
}

bit &bit::toAdditionalCode(size_type new_N)
{
    size_type diff = new_N - get_size();
    bit temp(new_N,num_sys-1);

    for (size_type i = diff; i < new_N; ++i)    // преобразую числа в соответствии с алгоритмом перевода в доп код -- //
    {
        temp[i] = num_sys-1 - (*this)[i-diff];
    }
    ++temp[new_N-1];
    (*this) = std::move(temp);
    return (*this);
}


bit &bit::operator^=(const bit &b)
{
    bit max, min;
    if (get_size() < b.get_size())
    {
        max = b;
        min = (*this);
    }
    else
    {
        max = (*this);
        min = b;
    }
    size_type N_min = min.get_size();

    std::reverse(max.begin(),max.end()); // -- переворачиваю -- //
    std::reverse(min.begin(),min.end()); // -- переворачиваю -- //

    for (size_type i = 0; i < N_min; ++i)
    {
        max[i] ^= min[i];
    }
    std::reverse(max.begin(), max.end()); // -- переворачиваю обратно -- //
    (*this) = std::move(max);
    return (*this);
}
bit operator^(const bit &a, const bit &b)
{
    bit t = a;
    t ^= b;
    return t;
}


bit &bit::operator&=(const bit &b)
{
    bit max, min;
    if (get_size() < b.get_size())
    {
        max = b;
        min = (*this);
    }
    else
    {
        max = (*this);
        min = b;
    }
    size_type N_min = min.get_size();

    std::reverse(max.begin(),max.end()); // -- переворачиваю -- //
    std::reverse(min.begin(),min.end()); // -- переворачиваю -- //

    for (size_type i = 0; i < N_min; ++i)
    {
        min[i] &= max[i];
    }
    std::reverse(min.begin(), min.end()); // -- переворачиваю обратно -- //
    (*this) = std::move(min);
    return (*this);
}
bit operator&(const bit &a, const bit &b)
{
    bit t = a;
    t &= b;
    return t;
}



bit& bit::operator%=(const bit &b)
{
    if (b == bit(1, 0)) { throw zero_divide_exception(); }


    bit tmp;
    size_t t = 0;
    size_t t_t = 0;
    while (t < (*this).get_size())
    {
        if (tmp == bit(1))
        {
            t_t = b.get_size();
            tmp = bit((*this).toString().substr(t, t_t));
        } else
        {
            t_t = b.get_size()-tmp.get_size();
            tmp = bit(tmp.toString() + (*this).toString().substr(t, t_t));
        }

        if (tmp.get_size() >= b.get_size()) { tmp ^= b; }
        tmp.sokr();
        t += t_t;
    }
    (*this) = std::move(tmp);

    return (*this);
}
bit operator%(const bit &a, const bit &b)
{
    bit t = a;
    t %= b;
    return t;
}

bit &bit::operator*=(const bit &b)
{
    bit max, min;
    if (get_size() < b.get_size())
    {
        max = b;
        min = (*this);
    }
    else
    {
        max = (*this);
        min = b;
    }

    std::reverse(max.begin(),max.end()); // -- переворачиваю -- //
    std::reverse(min.begin(),min.end()); // -- переворачиваю -- //

    size_t N_min = min.get_size();
    bit tmp1;
    bit tmp2;
    for (size_t i=0; i<N_min; ++i)
    {
        tmp1 = tmp2;
        if (min[i] == 1)
        {
            tmp2 = max;
        } else { tmp2 = bit(max.get_size(), 0); }
        if (i != 0)
        {
            tmp1 = bit("0"+std::string(tmp1.toString()));
            tmp2 = bit(tmp2.toString()+std::string(tmp1.get_size()-tmp2.get_size(), '0'));
            tmp2 ^= tmp1;
        }
    }

    (*this) = std::move(tmp2);
    return (*this);
}
bit operator*(const bit &a, const bit &b)
{
    bit t = a;
    t *= b;
    return t;
}


bit& bit::operator<<=(uint64_t i)
{
    bit new_string(get_size());
    std::move(begin()+i, end(), new_string.begin());
    std::move(begin(), begin()+i, new_string.end()-i);
    (*this) = std::move(new_string);
    return (*this);
}
bit operator<<(const bit &a, const uint8_t &b)
{
    bit t = a;
    t <<= b;
    return t;
}


bit& bit::operator>>=(uint64_t i)
{
    bit new_string(get_size());
    std::move(begin(), end(), new_string.begin()+i);
    std::move(end()-i, end(), new_string.begin());
    (*this) = std::move(new_string);
    return (*this);
}
bit operator>>(const bit &a, const uint8_t &b)
{
    bit t = a;
    t >>= b;
    return t;
}
