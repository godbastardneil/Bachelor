#ifndef ABONENT_H
#define ABONENT_H

#include "list.h"

class abonent: public list
{
public:
    void value_check(const_reference val, const int &i);

    abonent() = default;
    abonent(const data_type &d, const std::string &O, const std::string &U, const std::initializer_list<value_type> &v);
    abonent(const data_type &d, const std::string &O, const std::string &U, const list& other);
    abonent(const data_type &d, const std::string &O, const std::string &U, list&& other);
    abonent(const abonent& other) noexcept;
    abonent(abonent&& other) noexcept;

    void _add_(const_reference v);
    void _delete_(const size_type &s);
    void _change_(const size_type &i, const_reference v);

    value_type find_id(const std::string &id);

    list find_tele(const std::string &tele);

    list find_tarif(const double &S);
    list find_tarif_less(const double &S);
    list find_tarif_more(const double &S);

    std::string toString() const noexcept;

private:
    std::string oper; // фамилия оператора
    std::string uprav; // управляющего списком
    data_type data = data_type(01, 01, 1901); // дата создания

    class id_repit {}; // повтор идентификационного номера
    class id_8 {};
    class tel_11 {};
};

#endif // ABONENT_H
