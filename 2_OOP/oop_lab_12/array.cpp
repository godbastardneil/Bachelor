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

Array::reference Array::operator[](size_type index)
{
    element_checker(index);
    return arr[index];
}
Array::const_reference Array::operator[](size_type index) const
{
    element_checker(index);
    return arr[index];
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
    --size;
    (*this) = std::move(new_data);
}
void Array::pop_forvard()
{
    Array new_data(size-1, 0);
    std::move(begin()+1, end(), new_data.begin());
    --size;
    (*this) = std::move(new_data);
}
void Array::push_back(const_reference v) noexcept
{
    Array new_data(size+1, v);
    std::move(begin(), end(), new_data.begin());
    ++size;
    (*this) = std::move(new_data);
}
void Array::push_forvard(const_reference v) noexcept
{
    Array new_data(size+1, v);
    std::move(begin(), end(), new_data.begin()+1);
    ++size;
    (*this) = std::move(new_data);
}

std::string Array::toString() const noexcept
{
    std::stringstream ss;
    for (value_type a: (*this)) { ss << a << ' '; }
    std::string s = ss.str();
    s.pop_back();
    return s;
}

// --- методы сравнения
bool operator==(const Array &a, const Array &b) noexcept
{
    if (a.size != b.size) { return false; }
    for (Array::size_type i=0; i<a.size; ++i)
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
    for (Array::size_type i=0; i<a.size; ++i)
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
