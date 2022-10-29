#include "realty.h"

void realty::data_checker(std::string data)
{
    if (data.size() > 8) { throw data_8(); }
}

realty::realty(std::string d, const std::string &N, const std::initializer_list<list<vt>::value_type> &v): list<vt>(v)
{
    data_checker(d);
    data = d;
    name = N;
}
realty::realty(std::string d, const std::string &N, const list<vt> &other): list<vt>(other)
{
    data_checker(d);
    data = d;
    name = N;
}
realty::realty(std::string d, const std::string &N, list<vt> &&other): list<vt>(std::move(other))
{
    data_checker(d);
    data = d;
    name = N;
}
realty::realty(const realty &other) noexcept: list(other)
{
    name = other.name;
    data = other.data;
}
realty::realty(realty &&other) noexcept: list<vt>(std::move(other))
{
    name = other.name;
    data = other.data;

    other.name.clear();
    other.data = nullptr;
}

void realty::rand()
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

        list<vt>::value_type v(id, kolkom, obS, liS, data, prise, tel);

        push_back(v);
    }
}

void realty::_add_(list<vt>::const_reference v) { push_back(v); }

void realty::_change_(const list<vt>::size_type &s, list<vt>::const_reference v) { set_i(s, v); }

void realty::_delete_(const list<vt>::size_type &s) { erase(s); }

void realty::_delete_repit_()
{
    for (auto i=begin(); !i.isnull(); ++i)
    {
        iterator j = i; ++j;
        for (auto it=j; !it.isnull(); ++it)
        {
            if (std::get<0>(*i) == std::get<0>(*it)) { erase(it); }
        }
    }
}

list<vt>::value_type realty::find_id(int id)
{
    for (auto it=begin(); !it.isnull(); ++it)
    {
        if (std::get<0>(*it) == id) { return *it; }
    }
    return list<vt>::value_type(0, 0, 0, 0, "", 0, "");
}
list<vt>::value_type realty::binary_search(int id)
{
    sort(begin(), end());
    int low, high, mid;

    low = 0;
    high = get_size();
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
    return list<vt>::value_type(0, 0, 0, 0, "", 0, "");
}
list<vt>::value_type realty::interpolat_search(int id)
{
    sort(begin(), end());
    int mid, left=0, right=get_size()-1;
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
    } else { return list<vt>::value_type(0, 0, 0, 0, "", 0, ""); }
}

realty realty::find_data(std::string data)
{
    realty f;
    for (auto it=begin(); !it.isnull(); ++it)
    {
        if (data == std::get<4>(*it)) { f.push_back(*it); }
    }
    return f;
}
realty realty::find_commonS(double S)
{
    realty f;
    for (auto it=begin(); !it.isnull(); ++it)
    {
        if (S == std::get<2>(*it)) { f.push_back(*it); }
    }
    return f;
}
realty realty::find_commonS_less(double S)
{
    realty f;
    for (auto it=begin(); !it.isnull(); ++it)
    {
        if (S > std::get<2>(*it)) { f.push_back(*it); }
    }
    return f;
}
realty realty::find_commonS_more(double S)
{
    realty f;
    for (auto it=begin(); !it.isnull(); ++it)
    {
        if (S < std::get<2>(*it)) { f.push_back(*it); }
    }
    return f;
}
realty realty::find_livingS(double S)
{
    realty f;
    for (auto it=begin(); !it.isnull(); ++it)
    {
        if (S == std::get<3>(*it)) { f.push_back(*it); }
    }
    return f;
}
realty realty::find_livingS_less(double S)
{
    realty f;
    for (auto it=begin(); !it.isnull(); ++it)
    {
        if (S > std::get<3>(*it)) { f.push_back(*it); }
    }
    return f;
}
realty realty::find_livingS_more(double S)
{
    realty f;
    for (auto it=begin(); !it.isnull(); ++it)
    {
        if (S < std::get<3>(*it)) { f.push_back(*it); }
    }
    return f;
}

std::string realty::toString() noexcept
{
    std::string s = "Контора: " + name + "\n Дата создания: " + data;
    if (get_size() > 0)
    {
        for (auto it=begin(); !it.isnull(); ++it)
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

void sort(realty::iterator b, realty::iterator e)
{
    list<vt>::value_type pivot = *b;
    int id = std::get<0>(pivot);
    realty::iterator b1 = b, e1 = e;
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
    realty::iterator e2 = b;
    b = b1; e = e1;
    if (std::get<0>(*b) < std::get<0>(*e2))
    {
        sort(b, --e2);
    }
    if (std::get<0>(*e) > std::get<0>(*e2)) { sort(++e2, e); }
}
