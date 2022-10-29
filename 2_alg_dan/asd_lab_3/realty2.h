#ifndef REALTY2_H
#define REALTY2_H

#include "array.h"
#include <vector>
#include <random>

using vec = std::vector<value_type>;

class realty2
{
public:
    realty2() = default;
    realty2(std::string d, const std::string &N, const vec& other);
    realty2(std::string d, const std::string &N, vec&& other);
    realty2(const realty2& other) noexcept;
    realty2(realty2&& other) noexcept;

    size_type get_size() { return all_apart.size(); }

    void rand();

    void selectionSort_id();
    void selectionSort_commonS();
    void selectionSort_livingS();

    void _add_(const value_type &v);
    void _change_(const size_type &s, const value_type &v);
    void _delete_(const size_type &s);

    void _clear() { all_apart.clear(); }

    int find_id(int id);
    int find_id_disordered(int id);
    int find_id_sordered(int id);
    int binary_search(int id);
    int interpolat_search(int id);

    vec find_data(std::string data);

    vec find_commonS(double S);
    vec find_commonS_less(double S);
    vec find_commonS_more(double S);

    vec find_livingS(double S);
    vec find_livingS_less(double S);
    vec find_livingS_more(double S);

    std::string apart_toString() const noexcept;
    std::string toString() const noexcept;


    // -- дружественные функции ввода/вывода --
    friend std::istream &operator>>(std::istream& t, vec &v);

// -- дружественные функции ввода/вывода --
    friend std::ostream &operator<<(std::ostream& t, const realty2 &r) noexcept;
    friend std::istream &operator>>(std::istream& t, realty2 &r);

private:
    vec all_apart;
    std::string data; // дата создания фирмы
    std::string name; // название конторы

    // -- проверки на нулевой размер и существование элемента --
    inline void size_checker(size_type size) const;
    inline void element_checker(size_type i) const;
    inline void value_checker(vec v) const;

    inline void id_checker(int id, int i) const;
    inline void data_checker(std::string data) const;

    class id_repit {}; // повтор идентификационного номера
    class data_8 {}; // дата из 8 элементов

    class zero_size {}; // размер 0

    class no_element {}; // нет запрашиваемого элемента

    class id_8 {}; // идентификационный номер из 8 элементов
    class phone_11 {}; // номер из 11 элементов
};

#endif // REALTY2_H
