#ifndef REALTY2_H
#define REALTY2_H

#include <iostream>
#include <list>
#include <tuple>
#include <random>

using value_type = std::tuple<
                        int           /*0 - идентификационный номер*/,
                        uint8_t       /*1 - количество комнат*/,
                        double        /*2 - общая площадь*/,
                        double        /*3 - жилая площадь*/,
                        std::string   /*4 - дата постройки дома 01 01 2001*/,
                        double        /*5 - запрашиваемая стоимость*/,
                        std::string   /*6 - телефон продавца*/
                     >;     //-- ОСНОВНОЙ тип элементов --

class realty2: std::list<value_type>
{
public:
    using size_type = size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = iterator;

    realty2() = default;
    realty2(std::string d, const std::string &N, const std::initializer_list<value_type> &v);
    realty2(std::string d, const std::string &N, const list<value_type>& other);
    realty2(std::string d, const std::string &N, list<value_type>&& other);
    realty2(const realty2& other) noexcept;
    realty2(realty2&& other) noexcept;

    void rand();

    void _add_(const_reference v);
    void _change_(const size_type &s, const value_type &v);
    void _delete_(const size_type &s);
    void _delete_repit_();

    value_type find_id(int id);
    value_type binary_search(int id);
    value_type interpolat_search(int id);

    realty2 find_data(std::string data);

    realty2 find_commonS(double S);
    realty2 find_commonS_less(double S);
    realty2 find_commonS_more(double S);

    realty2 find_livingS(double S);
    realty2 find_livingS_less(double S);
    realty2 find_livingS_more(double S);

    size_type get_s() const noexcept { return size(); }
    void _clear() { clear(); }

    value_type get_i(const size_type &i)
    {
        element_checker(i);
        auto it = begin();
        for (size_type j=0; j<i; ++j) { ++it; }
        return *it;
    }
    void set_i(const size_type &i, const_reference v)
    {
        element_checker(i);
        auto it = begin();
        for (size_type j=0; j<i; ++j) { ++it; }
        *it = v;
    }
    void erase_by_i(const size_type &i)
    {
        element_checker(i);
        auto it = begin();
        for (size_type j=0; j<i; ++j) { ++it; }
        erase(it);
    }

    iterator HEAD() { return begin(); }
    iterator TAIL() { return end(); }

    std::string toString() noexcept;

private:
    std::string data; // дата создания фирмы
    std::string name; // название конторы

    inline void data_checker(std::string data);
    void element_checker(const size_type &i) const;

    class id_repit {}; // повтор идентификационного номера
    class data_8 {}; // дата из 8 элементов
    class no_element {}; // нет запрашиваемого элемента
};

void sort_realty2(realty2::iterator b, realty2::iterator e);

#endif // REALTY2_H
