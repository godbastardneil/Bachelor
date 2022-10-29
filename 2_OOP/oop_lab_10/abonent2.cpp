#include "abonent2.h"

void abonent2::value_check(const_reference val, const int &i)
{
    if (std::get<0>(val).size() > 8) { throw id_8();  }
    if (std::get<1>(val).size() > 11) { throw tel_11();  }
    for (int j=0; j<int(get_size()); ++j)
    {
        if (std::get<0>(val) == std::get<0>((*this)[j]) && j != i) { throw id_repit(); }
    }
}

abonent2::abonent2(const data_type &d, const std::string &O, const std::string &U, const std::initializer_list<value_type> &v): array(v)
{
    int i = 0;
    for (value_type val: v) { value_check(val, i); ++i; }
    data = d;
    oper = O;
    uprav = U;
}
abonent2::abonent2(const data_type &d, const std::string &O, const std::string &U, const array &other): array(other)
{
    for (size_type j=0; j<get_size(); ++j) { value_check(other[j], j); }
    data = d;
    oper = O;
    uprav = U;
}
abonent2::abonent2(const data_type &d, const std::string &O, const std::string &U, array&& other): array(other)
{
    for (size_type j=0; j<get_size(); ++j) { value_check(other[j], j); }
    data = d;
    oper = O;
    uprav = U;

    other.clear();
}
abonent2::abonent2(const abonent2& other) noexcept: array(other)
{
    oper = other.oper;
    uprav = other.uprav;
    data = other.data;
}
abonent2::abonent2(abonent2 &&other) noexcept: array(std::move(other)), oper(other.oper), uprav(other.uprav), data(other.data)
{
    other.uprav.clear();
    other.oper.clear();
    other.data = data_type(1, 1, 2000);
}

void abonent2::rand()
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


void abonent2::_add_(const_reference v)
{
    value_check(v, -1);
    push_back(v);
}

void abonent2::_delete_(const size_type &s) { erase(s); }

void abonent2::_change_(const size_type &i, const_reference v)
{
    value_check(v, i);
    (*this)[i] = v;
}

value_type abonent2::find_id(const std::string &id)
{
    for (size_type i=0; i<get_size(); ++i)
    {
        if (std::get<0>((*this)[i]) == id) { return (*this)[i]; }
    }
    return value_type("", "", data_type(1, 1, 2000), 0, 0);
}

array abonent2::find_tele(const std::string &tele)
{
    array f;
    for (size_type i=0; i<get_size(); ++i)
    {
        if (std::get<1>((*this)[i]) == tele) { f.push_back((*this)[i]); }
    }
    return f;
}

array abonent2::find_tarif(const double &t)
{
    array f;
    for (size_type i=0; i<get_size(); ++i)
    {
        if ((t - std::get<4>((*this)[i])) < 0.001) { f.push_back((*this)[i]); }
    }
    return f;
}

array abonent2::find_tarif_less(const double &t)
{
    array f;
    for (size_type i=0; i<get_size(); ++i)
    {
        if (t > std::get<4>((*this)[i])) { f.push_back((*this)[i]); }
    }
    return f;
}

array abonent2::find_tarif_more(const double &t)
{
    array f;
    for (size_type i=0; i<get_size(); ++i)
    {
        if (t < std::get<4>((*this)[i])) { f.push_back((*this)[i]); }
    }
    return f;
}

std::string abonent2::toString() const noexcept
{
    return ("Фамилия оператора: " + oper + "\n Управляющий списоком: " + uprav + "\n Дата создания: " + std::to_string(std::get<0>(data)) + "д" + std::to_string(std::get<1>(data)) + "м" + std::to_string(std::get<2>(data)) + "г\n" + to_String());
}
