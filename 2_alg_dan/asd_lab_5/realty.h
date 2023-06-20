#ifndef REALTY_H
#define REALTY_H

#include "tree.h"

class realty: public tree
{
public:
    realty() = default;
    realty(std::string d, const std::string &N, const std::initializer_list<data_t> &v);
    realty(std::string d, const std::string &N, const tree& other);
    realty(std::string d, const std::string &N, tree&& other);
    realty(const realty& other) noexcept;
    realty(realty&& other) noexcept;

    void _add_(const data_t &v);
    void _change_(const key_t &s, const value_t &v);
    void _delete_(const key_t &s);

    value_t find_id(const key_t &id);

    size_t get_s() const noexcept { return count(); }
    void _clear() { clear(); }

    std::string toString() noexcept;

private:
    std::string data; // дата создания фирмы
    std::string name; // название конторы

    void data_checker(const std::string &data);
    void value_checker(const value_t &d);

    class data_8 {}; // дата из 8 элементов
};

#endif // REALTY_H
