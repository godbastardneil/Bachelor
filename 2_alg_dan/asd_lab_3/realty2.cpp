#include "realty2.h"


void realty2::size_checker(size_type size) const { if (size == 0) { throw zero_size(); } }
void realty2::element_checker(size_type i) const { if (i >= all_apart.size()) { throw no_element(); } }
void realty2::value_checker(vec v) const
{
    for (size_type i=0; i<v.size(); ++i)
    {
        int n = 0;
        double k = std::get<0>(v[i]);
        while (k>=1)
        {
            ++n;
            k /= 10;
        }

        if (n > 8)
        {
            throw id_8();
        }
        else if (std::get<4>(v[i]).size() > 8)
        {
            throw data_8();
        }
        else if (std::get<6>(v[i]).size() > 11) { throw phone_11(); }
    }
}

void realty2::id_checker(int id, int i) const
{
    for (int j=0; j<int(all_apart.size()); ++j)
    {
        if (id == std::get<0>(all_apart[j]) && j != i) { throw id_repit(); }
    }
}
void realty2::data_checker(std::string data) const
{
    if (data.size() > 8) { throw data_8(); }
}

realty2::realty2(std::string d, const std::string &N, const vec &other)
{
    data_checker(d);
    value_checker(other);
    data = d;
    name = N;
    for (value_type i:other)
    {
        id_checker(std::get<0>(i), -1);
    }
    all_apart = other;
}
realty2::realty2(std::string d, const std::string &N, vec &&other)
{
    data_checker(d);
    value_checker(other);
    data = d;
    name = N;
    for (value_type i:other)
    {
        id_checker(std::get<0>(i), -1);
    }
    all_apart = std::move(other);
}
realty2::realty2(const realty2 &other) noexcept
{
    name = other.name;
    data = other.data;
    all_apart = other.all_apart;
}
realty2::realty2(realty2 &&other) noexcept
{
    name = other.name;
    data = other.data;

    all_apart = std::move(other.all_apart);

    other.name.clear();
    other.data = nullptr;
}


void realty2::rand()
{
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

void realty2::selectionSort_id()
{
    int min;
    value_type temp; // для поиска минимального элемента и для обмена
    for (size_type i = 0; i < (all_apart.size()-1); ++i)
    {
        min = i;
        for (size_type j = i+1; j < all_apart.size(); j++)
        {
            if (std::get<0>(all_apart[j]) < std::get<0>(all_apart[min])) { min = j; }
        }
        std::swap(all_apart[i], all_apart[min]);
    }
}
void realty2::selectionSort_commonS()
{
    int min;
    value_type temp; // для поиска минимального элемента и для обмена
    for (size_type i = 0; i < (all_apart.size()-1); ++i)
    {
        min = i;
        for (size_type j = i+1; j < all_apart.size(); j++)
        {
            if (std::get<2>(all_apart[j]) < std::get<2>(all_apart[min])) { min = j; }
        }
        std::swap(all_apart[i], all_apart[min]);
    }
}
void realty2::selectionSort_livingS()
{
    int min;
    value_type temp; // для поиска минимального элемента и для обмена
    for (size_type i = 0; i < (all_apart.size()-1); ++i)
    {
        min = i;
        for (size_type j = i+1; j < all_apart.size(); j++)
        {
            if (std::get<3>(all_apart[j]) < std::get<3>(all_apart[min])) { min = j; }
        }
        std::swap(all_apart[i], all_apart[min]);
    }
}

void realty2::_add_(const value_type &v)
{
    id_checker(std::get<0>(v), -1);
    all_apart.push_back(v);
}

void realty2::_change_(const size_type &s, const value_type &v)
{
    id_checker(std::get<0>(v), s);
    all_apart[s] = v;
}

void realty2::_delete_(const size_type &s)
{
    all_apart.erase(all_apart.begin()+s);
}

int realty2::find_id(int id)
{
    size_type i = 0;
    while (i < all_apart.size() && std::get<0>(all_apart[i]) != id) { ++i;  }
    if (i < all_apart.size()) { return i; }

    return -1;
}
int realty2::find_id_disordered(int id)
{
    all_apart.push_back(value_type(id, 0, 0, 0, "", 0, ""));
    size_type i = 0;
    while (std::get<0>(all_apart[i]) != id) { ++i; }
    all_apart.pop_back();
    if (i < all_apart.size()) { return i; }

    return -1;
}
int realty2::find_id_sordered(int id)
{
    selectionSort_id();
    all_apart.push_back(value_type(id, 0, 0, 0, "", 0, ""));
    size_type i = 0;
    while (std::get<0>(all_apart[i]) != id) { ++i; }
    all_apart.pop_back();
    if (i < all_apart.size()) { return i; }

    return -1;
}
int realty2::binary_search(int id)
{
    selectionSort_id();
    int low, high, mid;

    low = 0;
    high = all_apart.size();
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
int realty2::interpolat_search(int id)
{
    selectionSort_id();
    int mid, left=0, right=all_apart.size()-1;
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

vec realty2::find_data(std::string data)
{
    vec f;

    for (value_type v:all_apart)
    {
        if (data == (std::get<4>(v))) { f.push_back(v); }
    }

    return f;
}

vec realty2::find_commonS(double S)
{
    vec f;

    for (value_type v:all_apart)
    {
        if (S == (std::get<2>(v))) { f.push_back(v); }
    }

    return f;
}

vec realty2::find_commonS_less(double S)
{
    vec f;

    for (value_type v:all_apart)
    {
        if (S > (std::get<2>(v))) { f.push_back(v); }
    }

    return f;
}

vec realty2::find_commonS_more(double S)
{
    vec f;

    for (value_type v:all_apart)
    {
        if (S < (std::get<2>(v))) { f.push_back(v); }
    }

    return f;
}

vec realty2::find_livingS(double S)
{
    vec f;

    for (value_type v:all_apart)
    {
        if (S == (std::get<3>(v))) { f.push_back(v); }
    }

    return f;
}

vec realty2::find_livingS_less(double S)
{
    vec f;

    for (value_type v:all_apart)
    {
        if (S > (std::get<3>(v))) { f.push_back(v); }
    }

    return f;
}

vec realty2::find_livingS_more(double S)
{
    vec f;

    for (value_type v:all_apart)
    {
        if (S < (std::get<3>(v))) { f.push_back(v); }
    }

    return f;
}


std::string realty2::apart_toString() const noexcept
{
    if (all_apart.size() != 0)
    {
        std::string s;

        for (value_type v:all_apart)
        {
            s += " идентификационный номер : " + std::to_string(std::get<0>(v)) + '\n';
            s += " количество комнат : " + std::to_string(std::get<1>(v)) + '\n';
            s += " общая площадь : " + std::to_string(std::get<2>(v)) + '\n';
            s += " жилая площадь : " + std::to_string(std::get<3>(v)) + '\n';
            s += " дата постройки дома : " + (std::get<4>(v)) + '\n';
            s += " запрашиваемая стоимость : " + std::to_string(std::get<5>(v)) + '\n';
            s += " телефон продавца : " + (std::get<6>(v)) + '\n';
            s += '\n';
        }
        return s;
    }
    return "Нет Информации";
}

std::string realty2::toString() const noexcept
{
    return ("Контора: " + name + "\nДата создания: " + data + '\n' + apart_toString());
}

std::istream &operator>>(std::istream &t, vec &v)
{
    std::string s;

    size_type n;
    t >> n;

    int id;
    uint8_t k;
    double cS, lS, pr;
    std::string data, tele;

    for (size_type i=0; i<n; ++i)
    {
        std::cout << (i+1) << ": ";
        t >> id >> k >> cS >> lS >> data >> pr >> tele;
        v.push_back(value_type(id, k, cS, lS, data, pr, tele));
    }

    return t;
}

std::ostream &operator<<(std::ostream &t, const realty2 &r) noexcept
{
    return (t << r.toString());
}
std::istream &operator>>(std::istream &t, realty2 &r)
{
    t >> r.data;
    t >> r.name;

    t >> r.all_apart;

    return t;
}
