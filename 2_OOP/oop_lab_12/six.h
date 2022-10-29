#ifndef SIX_H
#define SIX_H

#include "number.h"

class six: public number
{
public:
    six() = default;
    explicit six(const size_type& n, const_reference v = 0): number(n, v)
    {
        set_num(6);
        num_checker(v);
        sokr();
    }
    six(const std::initializer_list<value_type> &v): number(v)
    {
        set_num(6);
        for (value_type val: v) { num_checker(val); }
        sokr();
    }
    six(const std::string &str): number(str)
    {
        set_num(6);
        for (char val: str) { num_checker(value_type(val-'0')); }
        sokr();
    }

    six(const number& other): number(other) {  }
    six(number&& other): number(std::move(other)) {  }

    // мультиметоды
    virtual std::string Operator_dymamic_cast(const number &n);
    virtual std::string Operator_typeid(const number &n);
    virtual std::string Operator_virtual(const number &n) const;
    virtual std::string Operator_virtual(const binary&) const;
    virtual std::string Operator_virtual(const twelve&) const;
    virtual std::string Operator_virtual(const six&) const;
};

#endif // SIX_H
