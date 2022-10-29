#ifndef BINARY_H
#define BINARY_H

#include "number.h"

class binary: public number
{
public:
    binary() = default;
    explicit binary(const size_type& n, const_reference v = 0): number(n, v)
    {
        set_num(2);
        num_checker(v);
        sokr();
    }
    binary(const std::initializer_list<value_type> &v): number(v)
    {
        set_num(2);
        for (value_type val: v) { num_checker(val); }
        sokr();
    }
    binary(const std::string &str): number(str)
    {
        set_num(2);
        for (char val: str) { num_checker(value_type(val-'0')); }
        sokr();
    }

    binary(const number& other): number(other) {  }
    binary(number&& other): number(std::move(other)) {  }

    // мультиметоды
    virtual std::string Operator_dymamic_cast(const number &n);
    virtual std::string Operator_typeid(const number &n);
    virtual std::string Operator_virtual(const number &n) const;
    virtual std::string Operator_virtual(const twelve&) const;
    virtual std::string Operator_virtual(const six&) const;
    virtual std::string Operator_virtual(const binary&) const;
};

#endif // BINARY_H
