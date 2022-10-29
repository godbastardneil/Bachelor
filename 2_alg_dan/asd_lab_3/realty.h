#ifndef REALTY_H
#define REALTY_H

#include "array.h"
#include <random>

class realty
{
public:
    realty() = default;
    realty(std::string d, const std::string &N, const std::initializer_list<value_type> &v);
    realty(std::string d, const std::string &N, const array& other);
    realty(std::string d, const std::string &N, array&& other);
    realty(const realty& other) noexcept;
    realty(realty&& other) noexcept;

    size_type get_size() { return all_apart.get_size(); }

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

    array find_data(std::string data);

    array find_commonS(double S);
    array find_commonS_less(double S);
    array find_commonS_more(double S);

    array find_livingS(double S);
    array find_livingS_less(double S);
    array find_livingS_more(double S);

    std::string toString() const noexcept;
// -- дружественные функции ввода/вывода --
    friend std::ostream &operator<<(std::ostream& t, const realty &r) noexcept;
    friend std::istream &operator>>(std::istream& t, realty &r);

private:
    array all_apart;
    std::string data; // дата создания фирмы
    std::string name; // название конторы

    inline void id_checker(int id, int i) const;
    inline void data_checker(std::string data) const;

    class id_repit {}; // повтор идентификационного номера
    class data_8 {}; // дата из 8 элементов
};

#endif // REALTY_H
