#include "realty.h"

void realty::id_checker(int id, int i) const
{
    for (int j=0; j<int(all_apart.get_size()); ++j)
    {
        if (id == std::get<0>(all_apart[j]) && j != i) { throw id_repit(); }
    }
}
void realty::data_checker(std::string data) const
{
    if (data.size() > 8) { throw data_8(); }
}

realty::realty(std::string d, const std::string &N, const std::initializer_list<value_type> &v)
{
    data_checker(d);
    data = d;
    name = N;
    for (value_type i:v)
    {
        id_checker(std::get<0>(i), -1);
    }
    all_apart = array(v);
}
realty::realty(std::string d, const std::string &N, const array &other)
{
    data_checker(d);
    data = d;
    name = N;
    for (value_type i:other)
    {
        id_checker(std::get<0>(i), -1);
    }
    all_apart = other;
}
realty::realty(std::string d, const std::string &N, array &&other)
{
    data_checker(d);
    data = d;
    name = N;
    for (value_type i:other)
    {
        id_checker(std::get<0>(i), -1);
    }
    all_apart = std::move(other);
}
realty::realty(const realty &other) noexcept
{
    name = other.name;
    data = other.data;
    all_apart = other.all_apart;
}
realty::realty(realty &&other) noexcept
{
    name = other.name;
    data = other.data;

    all_apart = std::move(other.all_apart);

    other.name.clear();
    other.data = nullptr;
}

void realty::rand()
{
    all_apart.clear();
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

        all_apart.push_back(v);
    }
}

void realty::selectionSort_id()
{
    int min;
    value_type temp; // для поиска минимального элемента и для обмена
    for (size_type i = 0; i < (all_apart.get_size()-1); ++i)
    {
        min = i;
        for (size_type j = i+1; j < all_apart.get_size(); j++)
        {
            if (std::get<0>(all_apart[j]) < std::get<0>(all_apart[min])) { min = j; }
        }
        std::swap(all_apart[i], all_apart[min]);
    }
}
void realty::selectionSort_commonS()
{
    int min;
    value_type temp; // для поиска минимального элемента и для обмена
    for (size_type i = 0; i < (all_apart.get_size()-1); ++i)
    {
        min = i;
        for (size_type j = i+1; j < all_apart.get_size(); j++)
        {
            if (std::get<2>(all_apart[j]) < std::get<2>(all_apart[min])) { min = j; }
        }
        std::swap(all_apart[i], all_apart[min]);
    }
}
void realty::selectionSort_livingS()
{
    int min;
    value_type temp; // для поиска минимального элемента и для обмена
    for (size_type i = 0; i < (all_apart.get_size()-1); ++i)
    {
        min = i;
        for (size_type j = i+1; j < all_apart.get_size(); j++)
        {
            if (std::get<3>(all_apart[j]) < std::get<3>(all_apart[min])) { min = j; }
        }
        std::swap(all_apart[i], all_apart[min]);
    }
}

void realty::_add_(array::const_reference v)
{
    id_checker(std::get<0>(v), -1);
    all_apart.push_back(v);
}

void realty::_change_(const size_type &s, const value_type &v)
{
    id_checker(std::get<0>(v), s);
    all_apart[s] = v;
}

void realty::_delete_(const size_type &s)
{
    all_apart.erase(s);
}

int realty::find_id(int id)
{
    size_type i = 0;
    while (i < all_apart.get_size() && std::get<0>(all_apart[i]) != id) { ++i;  }
    if (i < all_apart.get_size()) { return i; }

    return -1;
}
int realty::find_id_disordered(int id)
{
    all_apart.push_back(value_type(id, 0, 0, 0, "", 0, ""));
    size_type i = 0;
    while (std::get<0>(all_apart[i]) != id) { ++i; }
    all_apart.pop_back();
    if (i < all_apart.get_size()) { return i; }

    return -1;
}
int realty::find_id_sordered(int id)
{
    selectionSort_id();
    all_apart.push_back(value_type(id, 0, 0, 0, "", 0, ""));
    size_type i = 0;
    while (std::get<0>(all_apart[i]) != id) { ++i; }
    all_apart.pop_back();
    if (i < all_apart.get_size()) { return i; }

    return -1;
}
int realty::binary_search(int id)
{
    selectionSort_id();
    int low, high, mid;

    low = 0;
    high = all_apart.get_size();
    while(low <= high) {
        mid = (low + high) / 2;
        if(id < std::get<0>(all_apart[mid]))
        {
            high = mid - 1;
        }
        else if(id > std::get<0>(all_apart[mid]))
        {
            low = mid + 1;
        } else { return mid; }
    }

    return -1;
}
int realty::interpolat_search(int id)
{
    selectionSort_id();
    int mid, left=0, right=all_apart.get_size()-1;
    while ((std::get<0>(all_apart[left])<id) && (std::get<0>(all_apart[right])>id))
    {
        mid=left+((id-std::get<0>(all_apart[left]))*(right-left))/(std::get<0>(all_apart[right])-std::get<0>(all_apart[left]));

        if (std::get<0>(all_apart[mid])<id)
        {
            left=mid+1;
        } else if (std::get<0>(all_apart[mid])>id)
        {
            right=mid-1;
        } else { return mid; }
    }
    if (std::get<0>(all_apart[left]) == id)
    {
        return left;
    } else if (std::get<0>(all_apart[right]) == id)
    {
        return right;
    } else { return -1; }
}

array realty::find_data(std::string data)
{
    array f;

    for (value_type v:all_apart)
    {
        if (data == (std::get<4>(v))) { f.push_back(v); }
    }

    return f;
}

array realty::find_commonS(double S)
{
    array f;

    for (value_type v:all_apart)
    {
        if (S == (std::get<2>(v))) { f.push_back(v); }
    }

    return f;
}

array realty::find_commonS_less(double S)
{
    array f;

    for (value_type v:all_apart)
    {
        if (S > (std::get<2>(v))) { f.push_back(v); }
    }

    return f;
}

array realty::find_commonS_more(double S)
{
    array f;

    for (value_type v:all_apart)
    {
        if (S < (std::get<2>(v))) { f.push_back(v); }
    }

    return f;
}

array realty::find_livingS(double S)
{
    array f;

    for (value_type v:all_apart)
    {
        if (S == (std::get<3>(v))) { f.push_back(v); }
    }

    return f;
}

array realty::find_livingS_less(double S)
{
    array f;

    for (value_type v:all_apart)
    {
        if (S > (std::get<3>(v))) { f.push_back(v); }
    }

    return f;
}

array realty::find_livingS_more(double S)
{
    array f;

    for (value_type v:all_apart)
    {
        if (S < (std::get<3>(v))) { f.push_back(v); }
    }

    return f;
}

std::string realty::toString() const noexcept
{
    return ("Контора: " + name + "\nДата создания: " + data + '\n' + all_apart.toString());
}

std::ostream &operator<<(std::ostream &t, const realty &r) noexcept
{
    return (t << r.toString());
}
std::istream &operator>>(std::istream &t, realty &r)
{
    t >> r.data;
    t >> r.name;

    t >> r.all_apart;

    return t;
}
