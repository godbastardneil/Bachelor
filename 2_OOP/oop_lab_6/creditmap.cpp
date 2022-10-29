#include "creditmap.h"

std::string CreditMap::toString() noexcept
{
    std::string s = "Номер карты: " + number;
    s += "\nФамилия владельца: " + s_name;
    s += "\nДата окончания: " + std::to_string(end_data);
    s += "\nДата последнего снятия: " + std::to_string(last_data);
    s += "\nКоличест во дней после снятия без штрафа: " + std::to_string(days);
    s += "\nПроцент штрафа: " + std::to_string(fine);
    s += "\nЛимит снимаемой суммы: " + money::toString();
    return s;
}
std::ostream &operator<<(std::ostream &t, CreditMap &cm) noexcept { return (t << cm.toString() << std::endl); }

std::istream &operator>>(std::istream &t, CreditMap &cm)
{
    std::string n; // номер карты
    std::string sn; // фамилия владельца
    int ed; // дата окончания
    int ld; // дата последнего снятия
    int d; // количество дней после снятия без штрафа
    double f; // процент штрафа
    money m; // лимит снимаемой суммы
    t >> n >> sn >> ed >> ld >> d >> f >> m;
    cm = CreditMap(m, n, sn, ed, ld, d, f);
    return t;
}

CreditMap operator-(const CreditMap &a, money &m)
{
    CreditMap tmp = a;
    tmp -= m;
    return tmp;
}
CreditMap operator+(const CreditMap &a, money &m) noexcept
{
    CreditMap tmp = a;
    tmp += m;
    return tmp;
}


bool operator==(const CreditMap &a, const CreditMap &b) noexcept { return (a.get_r() == b.get_r()) && (a.get_c() == b.get_c()); }

bool operator!=(const CreditMap &a, const CreditMap &b) noexcept { return !(a == b); }

bool operator<(const CreditMap &a, const CreditMap &b) noexcept { return a.to_cop() < b.to_cop(); }

bool operator>(const CreditMap &a, const CreditMap &b) noexcept { return a.to_cop() > b.to_cop(); }

bool operator<=(const CreditMap &a, const CreditMap &b) noexcept { return !(a>b); }

bool operator>=(const CreditMap &a, const CreditMap &b) noexcept { return !(a<b); }
