#ifndef ABONENT_H
#define ABONENT_H

#include "list.h"
#include <random>

// -- типы --
using data_type = std::tuple<uint8_t, uint8_t, uint>;
using vt = std::tuple<
                        std::string  /*0 - номер договора*/,
                        std::string  /*1 - телефон*/,
                        data_type /*2 - дата заключения договора 01 01 2001*/,
                        double    /*3 - оплата за установку*/,
                        double    /*4 - тариф помесячный*/
                     >; //-- ОСНОВНОЙ тип элементов --

class abonent: public list<vt>
{
public:
    void value_check(const_reference val, const int &i);

    abonent() = default;
    abonent(const data_type &d, const std::string &O, const std::string &U, const std::initializer_list<value_type> &v);
    abonent(const data_type &d, const std::string &O, const std::string &U, list& other);
    abonent(const data_type &d, const std::string &O, const std::string &U, list&& other);
    abonent(const abonent& other) noexcept;
    abonent(abonent&& other) noexcept;

    virtual ~abonent() {  };
    void _add_(const_reference v);
    void _delete_(const size_type &s);
    void _change_(const size_type &i, const_reference v);

    value_type find_id(const std::string &id);
    abonent find_tele(const std::string &tele);
    abonent find_tarif(const double &S);
    abonent find_tarif_less(const double &S);
    abonent find_tarif_more(const double &S);


    std::string toString() noexcept;
private:
    std::string oper; // фамилия оператора
    std::string uprav; // управляющего списком
    data_type data = data_type(01, 01, 1901); // дата создания

    class id_repit {}; // повтор идентификационного номера
    class id_8 {};
    class tel_11 {};
};

#endif // ABONENT_H
