#include "array.h"

void array::size_checker(size_type size) const { if (size == 0) { throw zero_size(); } }
void array::element_checker(size_type i) const { if (i >= size) { throw no_element(); } }
void array::value_checker(value_type v) const
{
    int n = 0;
    double k = std::get<0>(v);
    while (k>=1)
    {
        ++n;
        k /= 10;
    }

    if (n > 8)
    {
        throw id_8();
    }
    else if (std::get<4>(v).size() > 8)
    {
        throw data_8();
    }
    else if (std::get<6>(v).size() > 11) { throw phone_11(); }
}

array::array(const size_type& n, value_type v)
{
    size_checker(n); // защита "от дурака"

    size = n; // количество квартир
    capacity = n; // размер массива
    value_checker(v);
    apart = new value_type[n]; // новый массив
    std::fill(begin(), end(), v); // заполние apart элементов v
}
array::array(const std::initializer_list<value_type> &v): array(v.size())
{
    for(value_type i:v) { value_checker(i); }
    std::copy(v.begin(), v.end(), begin()); // копирование
}
array::array(const array& other): size(other.size), capacity(other.size), apart(new value_type[other.size])
{
    std::copy(other.begin(), other.end(), begin()); // копирование
}
array::array(array&& other) noexcept: size(other.size), capacity(other.size), apart(other.apart)
{
    other.size = 0;
    other.apart = nullptr;
}

array &array::operator=(const array &other) noexcept
{
    if (this != &other) // самоприсваивание
    {
        array tmp(other);
        std::swap(size, tmp.size);
        std::swap(apart, tmp.apart);
    }
    return *this;
}
array &array::operator=(array &&other) noexcept
{
    if (this != &other) // самоприсваивание
    {
        std::swap(size, other.size);
        std::swap(apart, other.apart);
    }
    return *this;
}


array::reference array::operator[](size_type index)
{
    element_checker(index);
    return apart[index];
}
array::const_reference array::operator[](size_type index) const
{
    element_checker(index);
    return apart[index];
}


void array::push_back(const value_type &v)
{
    array tmp(size+1, v);
    std::move(begin(), end(), tmp.begin());
    *this = std::move(tmp);
}
void array::pop_back() noexcept
{
    if (size != 0) { size--; }
}

void array::erase(size_type idx)
{
    if (size > 0) { size--; }
    for (size_t i=idx; i<size; ++i)
    {
        apart[i] = apart[i+1];
    }
}

void array::clear() noexcept
{
    size = 0;
    capacity = 0;
    delete [] apart;
    apart = nullptr;
}

std::string array::toString() const noexcept
{
    if (size != 0)
    {
        std::string s;

        for (value_type v:(*this))
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

std::ostream &operator<<(std::ostream &t, const array &a) noexcept
{
    return (t << a.toString());
}
std::istream &operator>>(std::istream &t, array &a)
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
        a.push_back(value_type(id, k, cS, lS, data, pr, tele));
    }

    return t;
}

// --- методы сравнения
bool operator==(const array &a, const array &b) noexcept
{
    if (a.size != b.size) { return false; }
    for (size_type i=0; i<a.size; ++i)
    {
        if (a.apart[i] != b.apart[i]) { return false; }
    }
    if (a.apart[0] != b.apart[0]) { return false; }
    return true;
}
bool operator!=(const array &a, const array &b) noexcept { return !(a == b); }

bool operator<(const array &a, const array &b) noexcept
{
    if (a.size > b.size)
    {
        return false;
    } else if (a.size < b.size) { return true; }
    for (size_type i=0; i<a.size; ++i)
    {
        if (a.apart[i]<b.apart[i])
        {
            return true;
        } else if (a.apart[i]>b.apart[i]) { return false; }
    }
    return false;
}
bool operator>=(const array &a, const array &b) noexcept { return !(a<b); }

bool operator>(const array &a, const array &b) noexcept
{
    if (a.size < b.size)
    {
        return false;
    } else if (a.size > b.size) { return true; }
    for (size_type i=0; i<a.size; ++i)
    {
        if (a.apart[i]>b.apart[i])
        {
            return true;
        } else if (a.apart[i]<b.apart[i]) { return false; }
    }
    return false;
}
bool operator<=(const array &a, const array &b) noexcept { return !(a>b); }
