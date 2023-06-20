#include "abonent.h"

void abonent::value_check(const_reference val, const int &i)
{
    int j = 0;
    if (std::get<0>(val).size() > 8) { throw id_8();  }
    if (std::get<1>(val).size() > 11) { throw tel_11();  }
    for (iterator it=begin(); it.nit != nullptr; ++it)
    {
        if (std::get<0>(val) == std::get<0>(*it) && j != i) { throw id_repit(); }
        ++j;
    }
}

abonent::abonent(const data_type &d, const std::string &O, const std::string &U, const std::initializer_list<value_type> &v): list(v)
{
    int i = 0;
    for (value_type val: v) { value_check(val, i); ++i; }
    data = d;
    oper = O;
    uprav = U;
}
abonent::abonent(const data_type &d, const std::string &O, const std::string &U, const list &other): list(other)
{
    int i = 0;
    for (iterator it=other.begin(); it.nit != nullptr; ++it) { value_check(*it, i); ++i; }
    data = d;
    oper = O;
    uprav = U;
}
abonent::abonent(const data_type &d, const std::string &O, const std::string &U, list&& other): list(other)
{
    int i = 0;
    for (iterator it=other.begin(); it.nit != nullptr; ++it) { value_check(*it, i); ++i; }
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

void abonent::rand()
{
    clear();
    std::random_device re;
    std::uniform_int_distribution<int> dis(1, 9);
    std::uniform_int_distribution<int> disdata(1, 3000);
    std::uniform_real_distribution<double> disd(1, 500);
    int n = 1+dis(re)%4;
    for (int i=0; i<n; ++i)
    {
        std::string id = std::to_string(10000000*dis(re)+1000000*dis(re)+100000*dis(re)+10000*dis(re)+1000*dis(re)+100*dis(re)+10*dis(re)+dis(re));
        std::string tel = std::to_string(1000000000*dis(re)+100000000*dis(re)+10000000*dis(re)+1000000*dis(re)+100000*dis(re)+10000*dis(re)+1000*dis(re)+100*dis(re)+10*dis(re)+dis(re));

        data_type data = data_type(disdata(re)/30, disdata(re)/12, disdata(re));

        double opl = disd(re);
        double tar = disd(re);

        value_type v(id, tel, data, opl, tar);
        try {
            value_check(v, -1);
            push_back(v);
        } catch (id_repit()) { --i; }
    }
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

value_type abonent::find_id(const std::string &id)
{
    iterator it = begin();
    while (it.nit != nullptr)
    {
        if (std::get<0>(*it) == id) { return *it; }
        ++it;
    }
    return value_type("", "", data_type(1, 1, 2000), 0, 0);
}

list abonent::find_tele(const std::string &tele)
{
    list f;
    for (iterator it=begin(); it.nit != nullptr; ++it)
    {
        if (std::get<1>(*it) == tele) { f.push_back(*it); }
    }
    return f;
}

list abonent::find_tarif(const double &t)
{
    list f;
    for (iterator it=begin(); it.nit != nullptr; ++it)
    {
        if ((t - std::get<4>(*it)) < 0.001) { f.push_back(*it); }
    }
    return f;
}

list abonent::find_tarif_less(const double &t)
{
    list f;
    for (iterator it=begin(); it.nit != nullptr; ++it)
    {
        if (t > std::get<4>(*it)) { f.push_back(*it); }
    }
    return f;
}

list abonent::find_tarif_more(const double &t)
{
    list f;
    for (iterator it=begin(); it.nit != nullptr; ++it)
    {
        if (t < std::get<4>(*it)) { f.push_back(*it); }
    }
    return f;
}

std::string abonent::toString() const noexcept
{
    return ("Фамилия оператора: " + oper + "\n Управляющий списоком: " + uprav + "\n Дата создания: " + std::to_string(std::get<0>(data)) + "д" + std::to_string(std::get<1>(data)) + "м" + std::to_string(std::get<2>(data)) + "г\n" + to_String());
}
