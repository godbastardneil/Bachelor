#include "array.h"

Array &Array::operator=(const Array &other) noexcept
{
    if (this != &other) // отслеживаем самоприсваивание
    {
        Array tmp(other);
        std::swap(size, tmp.size);
        std::swap(arr, tmp.arr);
    }
    return *this;
}

Array &Array::operator=(Array &&other) noexcept
{
    if (this != &other) // отслеживаем самоприсваивание
    {
        std::swap(size, other.size);
        std::swap(arr, other.arr);
    }
    return *this;
}

reference Array::operator[](size_type index)
{
    element_checker(index);
    return reference((*this), index);
}
const_reference Array::operator[](size_type index) const
{
    element_checker(index);
    return const_reference((*this), index);
}

void Array::clear() noexcept
{
    size = 0;
    delete[] arr;
}

void Array::pop_back()
{
    Array new_data(size-1, 0);
    std::move(begin(), end()-1, new_data.begin());
    (*this) = std::move(new_data);
}

void Array::pop_forvard()
{
    Array new_data(size-1, 0);
    std::move(begin()+1, end(), new_data.begin());
    (*this) = std::move(new_data);
}
void Array::push_back(value_type t) noexcept
{
    Array new_data(size+1, t);
    std::move(begin(), end(), new_data.begin());
    (*this) = std::move(new_data);
}

void Array::push_forvard(value_type t) noexcept
{
    Array new_data(size+1, t);
    std::move(begin(), end(), new_data.begin()+1);
    (*this) = std::move(new_data);
}

std::string Array::toString() const noexcept
{
    std::stringstream ss;
    for (int a: (*this)) {  ss << a << ' '; }
    std::string s(ss.str());
    s.pop_back();
    return s;
}
std::ostream &operator<<(std::ostream &t, const Array &a) noexcept
{
    return (t << a.toString() << std::endl);
}

std::istream &operator>>(std::istream &t, Array &a)
{
    std::string s;
    t >> s;
    a = s;
    return t;
}

// --- методы сравнения
bool operator==(const Array &a, const Array &b) noexcept
{
    if (a.size != b.size) { return false; }
    for (size_type i=0; i<a.size; ++i)
    {
        if (a.arr[i] != b.arr[i]) { return false; }
    }
    if (a.arr[0] != b.arr[0]) { return false; }
    return true;
}
bool operator!=(const Array &a, const Array &b) noexcept { return !(a == b); }

bool operator<(const Array &a, const Array &b) noexcept
{
    if (a.size > b.size)
    {
        return false;
    } else if (a.size < b.size) { return true; }
    for (size_type i=0; i<a.size; ++i)
    {
        if (a.arr[i]<b.arr[i])
        {
            return true;
        } else if (a.arr[i]>b.arr[i]) { return false; }
    }
    return false;
}
bool operator>=(const Array &a, const Array &b) noexcept { return !(a<b); }

bool operator>(const Array &a, const Array &b) noexcept { return (b<a); }
bool operator<=(const Array &a, const Array &b) noexcept { return !(b<a); }
