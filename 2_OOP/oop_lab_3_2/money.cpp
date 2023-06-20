#include "money.h"

std::istream& operator>>(std::istream& t, money &m)
{
    unsigned long long R;
    unsigned char C;
    t >> R >> C;
    m = money(R, C);
    return t;
}

std::string money::toString() noexcept {
    std::string s;
    s += std::to_string(r) + ",";
    if(c<10) { s += '0'; }
    s += std::to_string(c) + " руб.";
    return s;
}
std::ostream& operator<<(std::ostream& t, money &m) noexcept { return (t << m.toString() << std::endl); }

money& money::operator+=(const money &b) noexcept
{
    double l = (to_cop() + b.to_cop());
    r = unsigned(l)/100;
    c = u_char(l - r*100);
    return *this;
}
money operator+(const money &a, const money &b) noexcept
{
    money tmp = a;
    tmp += b;
    return tmp;
}

money& money::operator-=(const money &b)
{
    double l = (to_cop() - b.to_cop());
    if (l<0) {
        throw less_then_0(); // исключение
    } else {
        r = unsigned(l)/100;
        c = u_char(l - r*100);
    }
    return *this;
}
money operator-(const money &a, const money &b)
{
    money tmp = a;
    tmp -= b;
    return tmp;
}

double money::operator/(const money &b) noexcept
{
    return to_cop()/b.to_cop();
}

double money::operator/(const double &b) noexcept
{
    return to_cop()/(b);
}

money &money::operator*=(const double &b) noexcept
{
    u_long umnoch = u_long(to_cop()*b);
    r = umnoch/100;
    c = umnoch%100;
    return *this;
}


bool operator==(const money &a, const money &b) noexcept { return (a.r == b.r) && (a.c == b.c); }

bool operator!=(const money &a, const money &b) noexcept { return !(a == b); }

bool operator<(const money &a, const money &b) noexcept { return a.to_cop() < b.to_cop(); }

bool operator>(const money &a, const money &b) noexcept { return a.to_cop() > b.to_cop(); }

bool operator<=(const money &a, const money &b) noexcept { return !(a>b); }

bool operator>=(const money &a, const money &b) noexcept { return !(a<b); }
