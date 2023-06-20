#ifndef BIT_H
#define BIT_H

#include "array.h"

#include <numeric>

class bit : public Array
{
    bit& toAdditionalCode(size_type new_N);
public:
    static constexpr uint8_t num_sys = 2; // -- система счисления -- //

    // -- проверки -- //
    void CheckForBinary(const Array &arr) const;    // -- цифры должны быть четверичными -- //
    // -- конструкторы и присваивание -- //
    bit() = default;
    explicit bit(const size_type& n, value_type t = 0) : Array(n,t) { CheckForBinary(*this); }
    bit(const std::initializer_list<value_type> &t) : Array(t) { CheckForBinary(*this); }
    bit(const std::string &str) : Array(str) { CheckForBinary(*this); }

    void sokr() noexcept
    {
        while (get_size()>1 && (*this)[0] == 0) { pop_forvard(); }
    }
    // -- основные операции -- //
    bit& operator^=(const bit &b);
    bit& operator&=(const bit &b);
    bit& operator%=(const bit &b);
    bit& operator*=(const bit &b);
    bit& operator<<=(uint64_t i);
    bit& operator>>=(uint64_t i);

    // -- дружественные функции -- //
    friend bit operator^(const bit &a, const bit &b); // сложение по модулю два
    friend bit operator&(const bit &a, const bit &b);
    friend bit operator%(const bit &a, const bit &b);
    friend bit operator*(const bit &a, const bit &b);
    // -- операции сравнения -- //

    // -- исключения -- //
    class not_binery_exception {}; // -- не бинарного числа -- //
    class a_is_less_than_b_when_subtracted {};  // -- левое число меньше правого при вычитании -- //
    class zero_divide_exception {}; // -- деление на ноль -- //
};

#endif // BIT_H
