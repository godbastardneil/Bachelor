#ifndef REALTY_H
#define REALTY_H

#include "list.h"
#include <random>

using vt = std::tuple<
                        int           /*0 - идентификационный номер*/,
                        uint8_t       /*1 - количество комнат*/,
                        double        /*2 - общая площадь*/,
                        double        /*3 - жилая площадь*/,
                        std::string   /*4 - дата постройки дома 01 01 2001*/,
                        double        /*5 - запрашиваемая стоимость*/,
                        std::string   /*6 - телефон продавца*/
                     >;     //-- ОСНОВНОЙ тип элементов --

class realty: list<vt>
{
public:
    using iterator = list<vt>::iterator<value_type>;
    realty() = default;
    realty(std::string d, const std::string &N, const std::initializer_list<list<vt>::value_type> &v);
    realty(std::string d, const std::string &N, const list<vt>& other);
    realty(std::string d, const std::string &N, list<vt>&& other);
    realty(const realty& other) noexcept;
    realty(realty&& other) noexcept;

    void rand();

    void _add_(list<vt>::const_reference v);
    void _change_(const list<vt>::size_type &s, const list<vt>::value_type &v);
    void _delete_(const list<vt>::size_type &s);
    void _delete_repit_();

    list<vt>::value_type find_id(int id);
    list<vt>::value_type binary_search(int id);
    list<vt>::value_type interpolat_search(int id);

    realty find_data(std::string data);

    realty find_commonS(double S);
    realty find_commonS_less(double S);
    realty find_commonS_more(double S);

    realty find_livingS(double S);
    realty find_livingS_less(double S);
    realty find_livingS_more(double S);

    size_type get_s() const noexcept { return get_size(); }
    void _clear() { clear(); }

    iterator HEAD() { return begin(); }
    iterator TAIL() { return end(); }

    std::string toString() noexcept;

private:
    std::string data; // дата создания фирмы
    std::string name; // название конторы

    inline void data_checker(std::string data);

    class id_repit {}; // повтор идентификационного номера
    class data_8 {}; // дата из 8 элементов
};

void sort (realty::iterator b, realty::iterator e);

#endif // REALTY_H
