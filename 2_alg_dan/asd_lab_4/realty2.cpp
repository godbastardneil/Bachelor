#include "realty2.h"

void realty2::data_checker(std::string data)
{
    if (data.size() > 8) { throw data_8(); }
}
void realty2::element_checker(const realty2::size_type &i) const { if (i >= size()) { throw no_element(); } }

realty2::realty2(std::string d, const std::string &N, const std::initializer_list<value_type> &v): list<value_type>(v)
{
    data_checker(d);
    data = d;
    name = N;
}
realty2::realty2(std::string d, const std::string &N, const list<value_type> &other): list<value_type>(other)
{
    data_checker(d);
    data = d;
    name = N;
}
realty2::realty2(std::string d, const std::string &N, list<value_type> &&other): list<value_type>(std::move(other))
{
    data_checker(d);
    data = d;
    name = N;
}
realty2::realty2(const realty2 &other) noexcept: list(other)
{
    name = other.name;
    data = other.data;
}
realty2::realty2(realty2 &&other) noexcept: list(std::move(other))
{
    name = other.name;
    data = other.data;

    other.name.clear();
    other.data = nullptr;
}

void realty2::rand()
{
    clear();
    std::random_device re;
    std::uniform_int_distribution<int> dis(1, 9);
    std::uniform_real_distribution<double> disd(1, 500);

    int n = dis(re);
    for (int i=0; i<n; ++i)
    {
        int id = 10000000*dis(re)+1000000*dis(re)+100000*dis(re)+10000*dis(re)+1000*dis(re)+100*dis(re)+10*dis(re)+dis(re);
        uint8_t kolkom = dis(re);
        double obS = disd(re);
        double liS = disd(re);
        std::string data = std::to_string(100000*dis(re)+10000*dis(re)+1000*dis(re)+100*dis(re)+10*dis(re)+dis(re));
        double prise = disd(re);
        std::string tel = std::to_string(1000000*dis(re)+100000*dis(re)+10000*dis(re)+1000*dis(re)+100*dis(re)+10*dis(re)+dis(re));

        value_type v(id, kolkom, obS, liS, data, prise, tel);

        push_back(v);
    }
}

void realty2::_add_(const_reference v) { push_back(v); }

void realty2::_change_(const size_type &s, const_reference v) { set_i(s, v); }

void realty2::_delete_(const size_type &s) { erase_by_i(s); }

void realty2::_delete_repit_()
{
    for (auto i=begin(); i != end(); ++i)
    {
        iterator j = i; ++j;
        for (auto it=j; it != end(); ++it)
        {
            if (std::get<0>(*i) == std::get<0>(*it)) { erase(it); }
        }
    }
}

value_type realty2::find_id(int id)
{
    for (auto it=begin(); it != end(); ++it)
    {
        if (std::get<0>(*it) == id) { return *it; }
    }
    return value_type(0, 0, 0, 0, "", 0, "");
}
value_type realty2::binary_search(int id)
{
    sort_realty2(begin(), end());
    int low, high, mid;

    low = 0;
    high = size();
    while(low <= high)
    {
        mid = (low + high) / 2;
        if(id < std::get<0>(get_i(mid)))
        {
            high = mid-1;
        } else if(id > std::get<0>(get_i(mid)))
        {
            low = mid+1;
        } else { return get_i(mid); }
    }
    return value_type(0, 0, 0, 0, "", 0, "");
}
value_type realty2::interpolat_search(int id)
{
    sort_realty2(begin(), end());
    int mid, left=0, right=size()-1;
    while ((std::get<0>(get_i(left))<id) && (std::get<0>(get_i(right))>id))
    {
        mid=left+((id-std::get<0>(get_i(left)))*(right-left))/(std::get<0>(get_i(right))-std::get<0>(get_i(left)));

        if (std::get<0>(get_i(mid))<id)
        {
            left=mid+1;
        } else if (std::get<0>(get_i(mid))>id)
        {
            right=mid-1;
        } else { return get_i(mid); }
    }
    if (std::get<0>(get_i(left)) == id)
    {
        return get_i(left);
    } else if (std::get<0>(get_i(right)) == id)
    {
        return get_i(right);
    } else { return value_type(0, 0, 0, 0, "", 0, ""); }
}

realty2 realty2::find_data(std::string data)
{
    realty2 f;
    for (auto it=begin(); it != end(); ++it)
    {
        if (data == std::get<4>(*it)) { f.push_back(*it); }
    }
    return f;
}
realty2 realty2::find_commonS(double S)
{
    realty2 f;
    for (auto it=begin(); it != end(); ++it)
    {
        if (S == std::get<2>(*it)) { f.push_back(*it); }
    }
    return f;
}
realty2 realty2::find_commonS_less(double S)
{
    realty2 f;
    for (auto it=begin(); it != end(); ++it)
    {
        if (S > std::get<2>(*it)) { f.push_back(*it); }
    }
    return f;
}
realty2 realty2::find_commonS_more(double S)
{
    realty2 f;
    for (auto it=begin(); it != end(); ++it)
    {
        if (S < std::get<2>(*it)) { f.push_back(*it); }
    }
    return f;
}
realty2 realty2::find_livingS(double S)
{
    realty2 f;
    for (auto it=begin(); it != end(); ++it)
    {
        if (S == std::get<3>(*it)) { f.push_back(*it); }
    }
    return f;
}
realty2 realty2::find_livingS_less(double S)
{
    realty2 f;
    for (auto it=begin(); it != end(); ++it)
    {
        if (S > std::get<3>(*it)) { f.push_back(*it); }
    }
    return f;
}
realty2 realty2::find_livingS_more(double S)
{
    realty2 f;
    for (auto it=begin(); it != end(); ++it)
    {
        if (S < std::get<3>(*it)) { f.push_back(*it); }
    }
    return f;
}

std::string realty2::toString() noexcept
{
    std::string s = "Контора: " + name + "\n Дата создания: " + data;
    if (size() > 0)
    {
        for (auto it=begin(); it != end(); ++it)
        {
            s += "\n идентификационный номер: " + std::to_string(std::get<0>(*it))
               + "\n количество комнат: " + std::to_string(std::get<1>(*it))
               + "\n общая площадь: " + std::to_string(std::get<2>(*it))
               + "\n жилая площадь: " + std::to_string(std::get<3>(*it))
               + "\n дата постройки дома: " + std::get<4>(*it)
               + "\n запрашиваемая стоимость: " + std::to_string(std::get<5>(*it))
               + "\n телефон продавца: " + std::get<6>(*it) + '\n';
        }
    } else { s += "\n Нет Информации"; }
    return s;
}

void sort_realty2(realty2::iterator b, realty2::iterator e)
{
    value_type pivot = *b;
    int id = std::get<0>(pivot);
    realty2::iterator b1 = b, e1 = e;
    while (b != e)
    {
        while ((std::get<0>(*e) >= id) && (b != e)) { --e; }
        if (b != e)
        {
            *b = *e;
            ++b;
        }
        while (std::get<0>(*b) <= id && (b != e)) { ++b; }
        if (b != e)
        {
            *e = *b;
            --e;
        }
    }
    *b = pivot;
    realty2::iterator e2 = b;
    b = b1; e = e1;
    if (std::get<0>(*b) < std::get<0>(*e2))
    {
        sort_realty2(b, --e2);
    }
    if (std::get<0>(*e) > std::get<0>(*e2)) { sort_realty2(++e2, e); }
}
