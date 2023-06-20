#include "abonent.h"

void abonent::value_check(abonent::const_reference val, const int &i)
{
    int j = 0;
    if (std::get<0>(val).size() > 8) { throw id_8();  }
    if (std::get<1>(val).size() > 11) { throw tel_11();  }
    for (auto it=begin(); !it.isnull(); ++it)
    {
        if (std::get<0>(val) == std::get<0>(*it) && j != i) { throw id_repit(); }
        ++j;
    }
}

abonent::abonent(const data_type &d, const std::string &O, const std::string &U, const std::initializer_list<abonent::value_type> &v): list(v)
{
    int i = 0;
    for (list::value_type val: v) { value_check(val, i); ++i; }
    data = d;
    oper = O;
    uprav = U;
}
abonent::abonent(const data_type &d, const std::string &O, const std::string &U, list &other): list(other)
{
    int i = 0;
    for (auto it=other.begin(); !it.isnull(); ++it) { value_check(*it, i); ++i; }
    data = d;
    oper = O;
    uprav = U;
}
abonent::abonent(const data_type &d, const std::string &O, const std::string &U, list&& other): list(other)
{
    int i = 0;
    for (auto it=other.begin(); !it.isnull(); ++it) { value_check(*it, i); ++i; }
    data = d;
    oper = O;
    uprav = U;

    other.clear();
}
abonent::abonent(const abonent& other) noexcept: list(other)
{
    oper = other.oper;
    uprav = other.uprav;
    data = other.data;
}
abonent::abonent(abonent &&other) noexcept: list(std::move(other)), oper(other.oper), uprav(other.uprav), data(other.data)
{
    other.uprav.clear();
    other.oper.clear();
    other.data = data_type(1, 1, 2000);
}



void abonent::_add_(const_reference v)
{
    value_check(v, -1);
    push_back(v);
}

void abonent::_delete_(const size_type &s) { erase(s); }

void abonent::_change_(const size_type &i, const_reference v)
{
    value_check(v, i);
    set_i(i, v);
}

abonent::value_type abonent::find_id(const std::string &id)
{
    auto it = begin();
    while (!it.isnull())
    {
        if (std::get<0>(*it) == id) { return *it; }
        ++it;
    }
    return abonent::value_type("", "", data_type(1, 1, 2000), 0, 0);
}

abonent abonent::find_tele(const std::string &tele)
{
    abonent f;
    for (auto it=begin(); !it.isnull(); ++it)
    {
        if (std::get<1>(*it) == tele) { f.push_back(*it); }
    }
    return f;
}

abonent abonent::find_tarif(const double &t)
{
    abonent f;
    for (auto it=begin(); !it.isnull(); ++it)
    {
        if ((t - std::get<4>(*it)) < 0.001) { f.push_back(*it); }
    }
    return f;
}

abonent abonent::find_tarif_less(const double &t)
{
    abonent f;
    for (auto it=begin(); !it.isnull(); ++it)
    {
        if (t > std::get<4>(*it)) { f.push_back(*it); }
    }
    return f;
}

abonent abonent::find_tarif_more(const double &t)
{
    abonent f;
    for (auto it=begin(); !it.isnull(); ++it)
    {
        if (t < std::get<4>(*it)) { f.push_back(*it); }
    }
    return f;
}

std::string abonent::toString() noexcept
{
    std::stringstream ss;
    ss << "Фамилия оператора: " << oper
       << "\n Управляющий списоком: " << uprav
       << "\n Дата создания: " << std::to_string(std::get<0>(data)) << "д" << std::to_string(std::get<1>(data)) << "м" << std::to_string(std::get<2>(data)) << "г\n";
    if (!empty())
    {
        for (auto it = begin(); !it.isnull(); ++it)
        {
            data_type dt = std::get<2>(*it);
            ss << "\n Номер договора: " << std::get<0>(*it)
               << "\n Номер телефона: " << std::get<1>(*it)
               << "\n Дата заключения договора: " << std::to_string(std::get<0>(dt)) << "д" << std::to_string(std::get<1>(dt)) << "м" << std::to_string(std::get<2>(dt)) << "г"
               << "\n Стоимость: " << std::to_string(std::get<3>(*it))
               << "\n Тариф: " << std::to_string(std::get<4>(*it));
        }
    } else { ss << "\nНет информации"; }
    return ss.str();
}
