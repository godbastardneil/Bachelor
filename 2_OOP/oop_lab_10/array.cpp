#include "array.h"

void array::size_checker(const size_type &size) const { if (size == 0) { throw zero_size(); } }
void array::element_checker(const size_type &i) const { if (i >= size) { throw no_element(); } }

array::array(const size_type &n, const_reference v)
{
    size_checker(n);
    size = n;
    apart = new value_type[size];
    for (size_type i=0; i<size; ++i) { apart[i] = v; }
}

array::array(const std::initializer_list<value_type> &v): array(v.size())
{
    int i = 0;
    for (value_type val: v) { apart[i] = val; ++i; }
}
array::array(const array& other): size(other.size), apart(new value_type[other.size])
{
    for(size_type i=0; i<size; ++i) { apart[i] = other[i]; }
}
array::array(array&& other) noexcept: size(other.size), apart(other.apart)
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

reference array::operator[](const size_type &index)
{
    element_checker(index);
    return apart[index];
}
const_reference array::operator[](const size_type &index) const
{
    element_checker(index);
    return apart[index];
}

void array::push_back(const_reference v)
{
    array a(size+1, v);
    for (size_type i=0; i<size; ++i) { a[i] = (*this)[i]; }
    ++size;
    (*this) = std::move(a);
}
void array::pop_back() noexcept
{
    array a(size-1);
    for (size_type i=0; i<size-1; ++i) { a[i] = (*this)[i]; }
    --size;
    (*this) = std::move(a);
}

void array::push_front(const_reference v)
{
    array a(size+1, v);
    for (size_type i=0; i<size; ++i) { a[i+1] = (*this)[i]; }
    ++size;
    (*this) = std::move(a);
}
void array::pop_front() noexcept
{
    array a(size-1);
    for (size_type i=0; i<size-1; ++i) { a[i] = (*this)[i+1]; }
    --size;
    (*this) = std::move(a);
}

void array::erase(const size_type &idx)
{
    if (idx == 0)
    {
        pop_front();
    } else if (idx == size-1)
    {
        pop_back();
    } else if (idx < size)
    {
        a_iterator it(begin().nit+idx);
        array a(--size);
        for (size_type i=0; i<idx; ++i) { a[i] = (*this)[i]; }
        for (size_type i=idx+1; i<size+1; ++i) { a[i] = (*this)[i]; }
        (*this) = std::move(a);
    }
}
void array::clear() noexcept
{
    size = 0;
    delete[] apart;
    apart = nullptr;
}


std::string array::to_String() const noexcept
{
    std::stringstream ss;
    std::string s = "";
    if (size > 0)
    {
        for (size_type i=0; i<size; ++i)
        {
            data_type dt = std::get<2>(apart[i]);
            ss << "\n Номер договора: " << std::get<0>(apart[i])
               << "\n Номер телефона: " << std::get<1>(apart[i])
               << "\n Дата заключения договора: " << std::to_string(std::get<0>(dt)) << "д" << std::to_string(std::get<1>(dt)) << "м" << std::to_string(std::get<2>(dt)) << "г"
               << "\n Стоимость: " << std::to_string(std::get<3>(apart[i]))
               << "\n Тариф: " << std::to_string(std::get<4>(apart[i]));
        }
    } else { ss << "\nНет информации"; }
    return ss.str();
}
