#include "realty.h"

void realty::data_checker(const std::string &data)
{
    if (data.size() > 8) { throw data_8(); }
}

realty::realty(std::string d, const std::string &N, const std::initializer_list<data_t> &v): tree(v)
{
    data_checker(d);
    data = d;
    name = N;
}
realty::realty(std::string d, const std::string &N, const tree &other): tree(other)
{
    data_checker(d);
    data = d;
    name = N;
}
realty::realty(std::string d, const std::string &N, tree &&other): tree(std::move(other))
{
    data_checker(d);
    data = d;
    name = N;
}
realty::realty(const realty &other) noexcept: tree(other)
{
    name = other.name;
    data = other.data;
}
realty::realty(realty &&other) noexcept: tree(std::move(other))
{
    name = other.name;
    data = other.data;

    other.name.clear();
    other.data = nullptr;
}

void realty::_add_(const data_t &v) { insert(v); }

void realty::_change_(const key_t &s, const value_t &v) { replace(s, v); }

void realty::_delete_(const key_t &s) { erase(s); }

realty::value_t realty::find_id(const key_t &id) { return std::get<1>(find(id)); }


std::string realty::toString() noexcept
{
    std::string s = "Контора: " + name + "\n Дата создания: " + data + '\n';
    if (count() > 0)
    {
        s += to_string();
    } else { s += "\n Нет Информации"; }
    return s;
}
