#ifndef ABONENT_H
#define ABONENT_H

#include "list.h"
#include <random>

class abonent: public list
{
public:
    inline void id_checker(const std::string &id, const int &i) const;

    abonent() = default;
    abonent(const data_type &d, const std::string &O, const std::string &U, const std::initializer_list<value_type> &v);
    abonent(const data_type &d, const std::string &O, const std::string &U, const list& other);
    abonent(const data_type &d, const std::string &O, const std::string &U, list&& other);
    abonent(const abonent& other) noexcept;
    abonent(abonent&& other) noexcept;

    void rand();

    void _add_(const value_type &v);
    void _delete_(const size_type &s);
    void _change_(const size_type &i, const value_type &v);

    iterator find_id(std::string id);

    list find_tele(std::string tele);

    list find_tarif(double S);
    list find_tarif_less(double S);
    list find_tarif_more(double S);

    std::string toString() const noexcept;

private:
    std::string oper; // фамилия оператора
    std::string uprav; // управляющего списком
    data_type data = data_type(01, 01, 1901); // дата создания

    class id_repit {}; // повтор идентификационного номера
};

#endif // ABONENT_H
