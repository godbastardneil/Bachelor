#include "abonent.h"

void abonent::id_checker(const std::string &id, const int &i) const
{
    int j = 0;
    for (iterator it=begin(); it != end(); it = it->next)
    {
        if (id == it->item.get_id() && j != i) { throw id_repit(); }
        ++j;
    }
}

abonent::abonent(const data_type &d, const std::string &O, const std::string &U, const std::initializer_list<value_type> &v): list(v)
{
    data = d;
    oper = O;
    uprav = U;
}
abonent::abonent(const data_type &d, const std::string &O, const std::string &U, const list &other): list(other)
{
    data = d;
    oper = O;
    uprav = U;
}
abonent::abonent(const data_type &d, const std::string &O, const std::string &U, list&& other): list(other)
{
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

    int n = dis(re);
    for (int i=0; i<n; ++i)
    {
        std::string id = std::to_string(10000000*dis(re)+1000000*dis(re)+100000*dis(re)+10000*dis(re)+1000*dis(re)+100*dis(re)+10*dis(re)+dis(re));
        std::string tel = std::to_string(1000000000*dis(re)+100000000*dis(re)+10000000*dis(re)+1000000*dis(re)+100000*dis(re)+10000*dis(re)+1000*dis(re)+100*dis(re)+10*dis(re)+dis(re));

        data_type data = data_type(disdata(re)/30, disdata(re)/12, disdata(re));

        double opl = disd(re);
        double tar = disd(re);

        value_type v(id, tel, data, opl, tar);

        push_back(v);
    }
}


void abonent::_add_(const value_type &v)
{
    id_checker(v.get_id(), -1);
    push_back(v);
}

void abonent::_delete_(const size_type &s)
{
    erase(s);
}

void abonent::_change_(const size_type &i, const value_type &v)
{
    id_checker(v.get_id(), i);
    set_i(i, v);
}

iterator abonent::find_id(std::string id)
{
    iterator i;
    for (i=begin(); i != nullptr; i = i->next)
    {
        if (i->item.get_id() == id) { return i; }
    }
    return i;
}

list abonent::find_tele(std::string tele)
{
    list f;
    for (iterator i=begin(); i != nullptr; i = i->next)
    {
        if (i->item.get_tel() == tele) { f.push_back(i->item); }
    }
    return f;
}

list abonent::find_tarif(double t)
{
    list f;
    for (iterator i=begin(); i != nullptr; i = i->next)
    {
        if ((t - i->item.get_tar()) < 0.001) { f.push_back(i->item); }
    }
    return f;
}

list abonent::find_tarif_less(double t)
{
    list f;
    for (iterator i=begin(); i != nullptr; i = i->next)
    {
        if (t > i->item.get_tar()) { f.push_back(i->item); }
    }
    return f;
}

list abonent::find_tarif_more(double t)
{
    list f;
    for (iterator i=begin(); i != nullptr; i = i->next)
    {
        if (t < i->item.get_tar()) { f.push_back(i->item); }
    }
    return f;
}

std::string abonent::toString() const noexcept
{
    return ("Фамилия оператора: " + oper + "\n Управляющий списоком: " + uprav + "\n Дата создания: " + std::to_string(std::get<0>(data)) + "д" + std::to_string(std::get<1>(data)) + "м" + std::to_string(std::get<2>(data)) + "г" + '\n' + to_String());
}
