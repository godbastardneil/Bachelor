#ifndef ALG_H
#define ALG_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using num = std::vector<uint8_t>;

enum sign { p, m }; // p - плюс, m - минус

/*
    Представление числа в векторе: старший разряд - знак числа, m - "-", p - "+"
    После разряда числа, цифры числа расположены в обратном порядке.
    Пример: Строка = -1234, Представление в векторе: m 4 3 2 1
    Пример: Строка = 4321, Представление в векторе: p 1 2 3 4
*/


void sokr(num &v) // Удаление лишних нулей, находящиеся в старшем разряде, например: 1 1 2 3 4 0 0 0
{
    while (std::find(v.end()-1, v.end(), 0) != v.end()) {
        v.pop_back();
    }
}

void fromString (std::string &s, num &v) { // перевод из строки в вектор
    if (s[0] == '-') {
        v.push_back(m);
        s.erase(s.begin());
    } else {
        v.push_back(p);
        if (s[0] == '+') { s.erase(s.begin()); }
    }
    size_t n = s.length()-1;
    while (n > 0) {
        v.push_back(uint8_t(s[n] - '0'));
        n--;
    }
    sokr(v);
}
std::string toString (const num &v) {
    size_t n = v.size();
    std::string s(n+n/3, ' ');
    if (v[0] == m) {
        s[0] = '-';
    } else { s[0] = '+'; }
    for (size_t i=1, j=s.size()-1; i<n; ++i, --j) {
        s[j] = char(v[i] + '0');
        if ((i)%3 == 0) { --j; }
        std::cout << v[i];
    }
    return s;
}

std::ostream& operator<<(std::ostream& t, const num &v) noexcept // вывод длинного числа
{
    return (t << " Число: " + toString(v) << std::endl);
}
std::istream& operator>>(std::istream& t, num &v) noexcept // ввод
{
    v.clear();
    std::string s;
    t >> s;
    fromString(s, v);
    return t;
}

//-----сравнение по модулю----- ( без сравнения разряда со знаком)
bool operator==(const num &c, const num &v) noexcept
{
    size_t n = c.size();
    if (n != v.size()) {
        return false;
    } else {
        for (size_t i=n-1; i>0; --i) {
            if (c[i]!=v[i]) { return false; }
        }
        return true;
    }
}
bool operator!=(const num &c, const num &v) noexcept { return !(c == v); }
bool operator>(const num &c, const num &v) noexcept
{
    size_t n = c.size();
    if (n > v.size()) {
        return true;
    } else if (n < v.size()) {
        return false;
    } else {
        for (size_t i=n-1; i>0; --i) {
            if (c[i]>v[i]) {
                return true;
            } else if (c[i]<v[i]) { return false; }
        }
        return false;
    }
}
bool operator>=(const num &c, const num &v) noexcept { return ((c>v) || (c==v)); }


void operator++(num &v) noexcept
{
    size_t i=1;
    v[i]++;
    size_t n = v.size()-1;
    while ((v[i]>9) && (i<n)) {
        v[i+1] += v[i]/10;
        v[i] = v[i]%10;
        i++;
    }
    if (v[n]>9) {
        v.push_back(v[n]/10);
        v[n] %= 10;
    }
    sokr(v);
}
void dopcode(num &v) noexcept  // перевод в дополнительный код
{
    size_t n = v.size();
    for (size_t i=1; i<n; i++) { v[i] = 9-v[i]; }
    ++v;
}

// += для вычетания
// a не по ссылке, потому что нужно сделать копию, которую я буду изменять по меере необходимости при сложении
void operator+=(num &tmp, num a) noexcept
{
    size_t n = tmp.size(), p = a.size();
    size_t k;
    if (n>p) {
        k = n-p;
        for (size_t i=0; i<k; i++) { a.push_back(0); }
    } else if (n<p) {
        k = p-n;
        for (size_t i=0; i<k; i++) { tmp.push_back(0); }
    }

    if  (a[0] != tmp[0]) {
        if (a[0] == m) { dopcode(a); }
        if (tmp[0] == m) { dopcode(tmp); }
    }

    n = tmp.size()-1;
    for (size_t i=1; i<n; i++) {
        tmp[i] += a[i];
        tmp[i+1] += tmp[i]/10;
        tmp[i] = tmp[i]%10;
    }
    tmp[n] += a[n];
    if (tmp[n]>9) {
        tmp.push_back(tmp[n]/10);
        tmp[n] %= 10;
    }
}

num operator-(const num &b, num a) noexcept
{
    if ((b == a) && (a[0] == b[0])) { return num{p, 0}; }
    num tmp = b;
    a[0] = m - a[0];

    tmp += a;
    if ((a > b) && (a[0] != b[0])) { tmp[0] = m - tmp[0]; }
    if ((tmp.size() > b.size()) && (a[0] != tmp[0])) { tmp.pop_back(); }
    if ((tmp[0] == m) && !(a >= b) && (a[0] != b[0])) { dopcode(tmp); }
    sokr(tmp);

    return tmp;
}


num operator/(num &b, num a) noexcept
{
    if (b == a) {
        b = {p, 0};
        if (a[0] == b[0]){
            return num{p, 1};
        } else { return num{m, 1}; }
    }
    num tmp {p, 0};
    if (b[0] != a[0]) { tmp[0] = m; }
    b[0] = p;
    a[0] = p;
    while (b>=a) {
        b = b - a;
        ++tmp;
    }
    return tmp;
}

#endif // ALG_H
