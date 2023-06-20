#ifndef BITSTRING_H
#define BITSTRING_H

#include "array.h"

class bitstring: public Array
{
public:
    static const uint8_t num = 2; // бинарная

    // -- проверка на бинарность
    inline void num_checker(value_type vt) { if (vt >= num) { throw no_2(); } }

    bitstring() = default;
    explicit bitstring(const size_type &n, value_type t = 0): Array(n, t)
    {
        num_checker(t); // проверка набинарность
    }
    bitstring(const std::string &source): Array(source)
    {
        // проверка набинарность
        for(uint i=0; i<source.size(); ++i) { num_checker(value_type(source[i] - '0')); }
    }

    bitstring& operator&=(const bitstring &b); // AHD
    bitstring& operator|=(const bitstring &b); // OR
    bitstring& operator^=(const bitstring &b); // XOR
    bitstring& operator<<=(const size_type &s); // сдвиг вправо
    bitstring& operator>>=(const size_type &s); // сдвиг влево

    bitstring operator~(); // NOT

    friend bitstring operator<<(const bitstring &arr, const size_type &s);
    friend bitstring operator>>(const bitstring &arr, const size_type &s);
    friend bitstring operator&(const bitstring &arr, const bitstring &b);
    friend bitstring operator|(const bitstring &arr, const bitstring &b);
    friend bitstring operator^(const bitstring &arr, const bitstring &b);

private:
    class no_2 {}; // не битовое

};

#endif // BITSTRING_H
