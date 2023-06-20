#include "long.h"

void delenie(Long &chis, const Long &znam, Long &result)
{
    result = 0;
    if (znam == Long(0, 0))
    {
        throw Long::no_znam();
    } else if (znam != Long(0, 1))
    {
        while (chis>=znam)
        {
            chis -= znam;
            ++result;
        }
    } else { result = chis; }
}

Long &Long::dopcode() noexcept
{
    f = ~f;
    s = ~s;
    ++(*this);
    return (*this);
}

std::string Long::toString() const noexcept
{
    std::string ss;

    Long l = (*this);
    Long o;

    do {
        delenie(l, Long(0, 10), o);
        uint32_t num = l.s;
        ss += std::to_string(num);
        l = o;
    } while (l != Long(0, 0));
    std::reverse(ss.begin(), ss.end());

    return ss;
}

Long &Long::operator++() noexcept
{
    ++s;
    if (s == 0) { ++f; }
    return (*this);
}
Long Long::operator++(int) noexcept
{
    Long tmp = (*this);
    ++(*this);
    return tmp;
}
Long &Long::operator--() noexcept
{
    if (s == 0)
    {
        --f;
    }
    --s;
    return (*this);
}
Long Long::operator--(int) noexcept
{
    Long tmp = (*this);
    --(*this);
    return tmp;
}

Long &Long::operator+=(const Long &sec) noexcept
{
    uint32_t S = s;
    s += sec.s;
    f += sec.f;
    if (s < S) { ++f; }
    return *this;
}
Long &Long::operator-=(const Long &sec) noexcept
{
    Long tmp = sec;
    tmp.dopcode();
    (*this) += tmp;
    return (*this);
}
Long &Long::operator*=(const Long &sec) noexcept
{
    if (sec == 0)
    {
        f = 0; s = 0;
    } else if (sec != 1)
    {
        Long tmp = (*this);
        Long o = sec;
        f = 0; s = 0;
        while (o>0)
        {
            (*this) += tmp;
            o -= 1;
        }
    }
    return (*this);
}
Long &Long::operator/=(const Long &sec)
{
    Long o;
    delenie((*this), sec, o);
    (*this) = o;
    return (*this);
}
Long &Long::operator%=(const Long &sec)
{
    Long o;
    delenie((*this), sec, o);
    return (*this);
}


std::istream& operator>>(std::istream &t, Long &l) noexcept
{
    uint32_t A;
    uint32_t B;
    t >> A >> B;
    l = Long(A, B);
    return t;
}
std::ostream& operator<<(std::ostream &t, Long &l) noexcept { return (t << l.toString() << std::endl); }



Long operator+(const Long &fir, const Long &sec) noexcept
{
    Long tmp = fir;
    tmp += sec;
    return tmp;
}
Long operator-(const Long &fir, const Long &sec) noexcept
{
    Long tmp = fir;
    tmp -= sec;
    return tmp;
}
Long operator*(const Long &fir, const Long &sec) noexcept
{
    Long tmp = fir;
    tmp *= sec;
    return tmp;
}
Long operator/(const Long &fir, const Long &sec)
{
    Long tmp = fir;
    tmp /= sec;
    return tmp;
}
Long operator%(const Long &fir, const Long &sec)
{
    Long tmp = fir;
    tmp %= sec;
    return tmp;
}



/* функции сравнения */
bool operator==(const Long &fir, const Long &sec) noexcept { return (fir.f == sec.f) && (fir.s == sec.s); }
bool operator!=(const Long &fir, const Long &sec) noexcept { return !(fir == sec); }
bool operator<(const Long &fir, const Long &sec) noexcept
{
    if (fir.f == sec.f)
    {
        return fir.s<sec.s;
    }
    return fir.f<sec.f;
}
bool operator>(const Long &fir, const Long &sec) noexcept
{
    if (fir.f == sec.f)
    {
        return fir.s>sec.s;
    }
    return fir.f>sec.f;
}
bool operator<=(const Long &fir, const Long &sec) noexcept { return !(fir>sec); }
bool operator>=(const Long &fir, const Long &sec) noexcept { return !(fir<sec); }
