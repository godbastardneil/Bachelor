#ifndef CREDITMAP_H
#define CREDITMAP_H

#include "money.h"

class CreditMap : private money // лимит снимаемой суммы
{
private:
    std::string number; // номер карты
    std::string s_name; // фамилия владельца
    int end_data; // дата окончания
    int last_data; // дата последнего снятия
    int days; // количество дней после снятия без штрафа
    double fine; // процент штрафа

public:
    CreditMap() noexcept: money(0, 0)
    {
        number = "000000";
        s_name = "user";
        end_data = 0;
        last_data = 0;
        days = 0;
        fine = 0;
    }
    CreditMap(const money &m, const std::string & n, const std::string &sn, int ed, int ld, int d, const double &f): money(m)
    {
        number = n;
        s_name = sn;
        end_data = ed;
        last_data = ld;
        days = d;
        fine = f;
    }
    std::string toString() noexcept; // перевод в string // вывод

    void change_ed(int ed) { end_data += ed; } // изменить дату окончания на ed
    void change_ld(int ld) { last_data += ld; } // изменить дату окончания на ld
    void change_f(double f) { fine += f; } // начислить штраф


    friend std::ostream &operator<<(std::ostream& t, CreditMap &cm) noexcept;
    friend std::istream &operator>>(std::istream& t, CreditMap &cm);

    friend CreditMap operator-(const CreditMap &a, money &m); // стнять сумму b
    friend CreditMap operator+(const CreditMap &a, money &m) noexcept; // положить сумму b

    /* функции сравнения */
    friend bool operator==(const CreditMap &a, const CreditMap &b) noexcept;
    friend bool operator!=(const CreditMap &a, const CreditMap &b) noexcept;
    friend bool operator<(const CreditMap &a, const CreditMap &b) noexcept;
    friend bool operator>(const CreditMap &a, const CreditMap &b) noexcept;
    friend bool operator<=(const CreditMap &a, const CreditMap &b) noexcept;
    friend bool operator>=(const CreditMap &a, const CreditMap &b) noexcept;
};

#endif // CREDITMAP_H
