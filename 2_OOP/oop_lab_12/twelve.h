#ifndef TWELVE_H
#define TWELVE_H

#include "number.h"

class twelve: public number
{
public:
    twelve() = default;
    explicit twelve(const size_type& n, const_reference v= 0): number(n, v)
    {
        set_num(12);
        num_checker(v);
        sokr();
    }
    twelve(const std::initializer_list<value_type> &v): number(v)
    {
        set_num(12);
        for (value_type val: v) { num_checker(val); }
        sokr();
    }
    twelve(const std::string &str): number(str)
    {
        set_num(12);
        for (char val: str) { num_checker(value_type(val-'0')); }
        sokr();
    }

    twelve(const number& other): number(other) {  }
    twelve(number&& other): number(std::move(other)) {  }

    // мультиметоды
    virtual std::string Operator_dymamic_cast(const number &n);
    virtual std::string Operator_typeid(const number &n);
    virtual std::string Operator_virtual(const number &n) const;
    virtual std::string Operator_virtual(const binary&) const;
    virtual std::string Operator_virtual(const six&) const;
    virtual std::string Operator_virtual(const twelve&) const;
};

#endif // TWELVE_H
