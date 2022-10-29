#include "payment.h"

std::string payment::toString() noexcept
{
    std::string s;
    s = "\nФамилия: " + name +
    "\nОклад: " + sum.toString() +
    "\nНадбавка: " + allowance.toString() +
    "\nНачислено: " + accrued_sum.toString() +
    "\nПенсионные отчисления: " + pension.toString() +
    "\nПодоходный налог: " + income_tax.toString() +
    "\nУдержано: " + witheld_sum.toString() +
    "\nСумма, выдаваемая на руки: " + final_sum.toString() +
    "\nКоличество рабочих дней: " + std::to_string(work_days) +
    "\nКоличество отработанных дней: " + std::to_string(days_developed);
    return s;
}


std::istream& operator>>(std::istream& t, payment &p)
{
    std::string n;
    money s;
    double out_allowance;
    uint8_t out_work_days, out_days_developed;

        std::cout << "\nВведите фамилию: ";
        t >> n;
        std::cout << "\nВведите величину оклада: ";
        t >> s;
        do {
            std::cout << "\nПроцент надбавки: ";
            t >> out_allowance;
        } while (out_allowance < 0);
        std::cout << "\nВведите количество рабочих дней: ";
        t >> out_work_days;
        std::cout << "\nВведите количество отработанных дней: ";
        t >> out_days_developed;

    p = payment(n, out_allowance, out_work_days, out_days_developed, s);
    return t;
}

std::ostream& operator<<(std::ostream& t, payment &p) noexcept { return (t << p.toString() << std::endl); }

// Изменение оклада
void payment::set_sum(const money &s) { sum = s; init(); }
void payment::set_sum(unsigned long long R, unsigned char C) { sum = money{R, C}; init(); }

// Изменение надбавки
void payment::set_allowance(const double &new_allowance)
{
    if(new_allowance < 0) {
        throw "\nПроцент надбавки не может быть отрицательным";
    }
    percent = new_allowance/100;
    init();
}

// Расчёт надбавки
money payment::finding_allowance() noexcept { return sum*(percent); }

// Расчёт начисленной суммы
money payment::finding_accrued_sum() noexcept { return sum*(days_developed/work_days) + allowance; }

// Расчёт суммы пенсионных отчислений
money payment::finding_pension() noexcept { return accrued_sum*(percent_of_pension); }

// Расчёт суммы подоходного налога
money payment::finding_income_tax() noexcept { return ((accrued_sum - pension)*percent_of_income_tax); }

// Вычисление удержанной суммы
money payment::finding_witheld_sum() noexcept { return income_tax + pension; }

// Вычисление суммы, выдаваемой на руки
money payment::finding_final_sum() noexcept { return accrued_sum - witheld_sum; }


// сравнение по окладу
bool operator==(const payment &a, const payment &b) noexcept { return a.sum == b.sum; }

bool operator!=(const payment &a, const payment &b) noexcept { return !(a == b); }

bool operator<(const payment &a, const payment &b) noexcept { return a.sum < b.sum; }

bool operator>(const payment &a, const payment &b) noexcept { return a.sum > b.sum; }

bool operator<=(const payment &a, const payment &b) noexcept { return !(a>b); }

bool operator>=(const payment &a, const payment &b) noexcept { return !(a<b); }
