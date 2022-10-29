#ifndef NUMBER_H
#define NUMBER_H

#include "array.h"

class binary;
class twelve;
class six;

class number: public Array
{
public:
    inline void num_checker(const_reference v) { if (v >= get_num()) { throw no_num(); } }

    // -- конструкторы и присваивание -- //
    number() = default;
    explicit number(const size_type& n, const_reference v = 0): Array(n, v) {  }
    number(const std::initializer_list<value_type> &v): Array(v) {  }
    number(const std::string &str): Array(str) {  }
    number(const number& other): Array(other) {  }
    number(number&& other): Array(std::move(other)) {  }

    number& operator=(const number& other) = default;
    number& operator=(number&& other) = default;

    virtual ~number() {  }

    void set_num(const size_type& i = 0) { num = i; }
    value_type get_num() const { return num; }

    void sokr() noexcept; // Удаление лишних нулей в начале числа 0 0 0 1 2 3
    number& dopcode(size_type n) noexcept; // перевод в доп код
    // -- основные операции -- //
    number& operator+=(const number &b) noexcept;
    number& operator-=(const number &b);
    number& operator/=(const number &b);
    number& operator%=(const number &b);
    number& operator*=(const number &b) noexcept;

    // -- дружественные функции -- //
    friend number operator+(const number &a, const number &b) noexcept;
    friend number operator-(const number &a, const number &b);
    friend number operator/(const number &a, const number &b);
    friend number operator%(const number &a, const number &b);
    friend number operator*(const number &a, const number &b) noexcept;

    // -- мультиметоды -- //
    virtual std::string Operator_dymamic_cast(const number&) { return "n"; }
    virtual std::string Operator_typeid(const number&) { return "n"; }
    virtual std::string Operator_virtual(const number&) const { return "n"; }
    virtual std::string Operator_virtual(const binary&) const { return "n"; }
    virtual std::string Operator_virtual(const twelve&) const { return "n"; }
    virtual std::string Operator_virtual(const six&) const { return "n"; }

    class error{};
private:
    size_type num = 10;
    class no_num {}; // не *система исчесления*
    class no_minus {}; // вычитатся большее число из малого
    class no_znam {}; // нулевой знаменатель
};

#endif // NUMBER_H
