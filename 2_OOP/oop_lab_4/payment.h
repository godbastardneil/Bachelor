#ifndef PAYMENT_H
#define PAYMENT_H

#include <iostream>
#include <string>

class payment
{

private:
    class money
    {
    private:
        unsigned long long r;
        unsigned char c;
    public:
        class less_then_0 {}; // исключение меньше 0
        class more_then_99 {}; // исключение введено копеек больше, чем 99

        money() noexcept: r(0), c(0) {}
        money(unsigned long long R, unsigned char C=0) // Init
        {
            if (C > 99) { throw more_then_99(); }
            r = R;
            c = C;
        }

        std::string toString() noexcept; // перевод в string // вывод

        void set_c (const unsigned char &C)
        {
            if (C > 99) { throw more_then_99();}
            c = C;
        }
        void set_r (const unsigned long long  &R) noexcept { r = R; } // ввод r

        double to_cop () const noexcept { return (double(r)*100 + c); }

        money& operator+=(const money &b) noexcept; // сложение с присваиванием

        money& operator-=(const money &b); // вычитание с присваиванием

        double operator/(const money &b) noexcept; // деление на money
        double operator/(const double &b) noexcept; // деление на число

        money& operator*=(const double &b) noexcept; // умножение с присваиванием
        money& operator*=(const money &b) noexcept; // умножение с присваиванием


        friend std::istream& operator>>(std::istream& t, money &m);

        friend std::ostream& operator<<(std::ostream& t, money &m) noexcept;

        friend money operator+(const money &a, const money &b) noexcept; // сложение
        friend money operator-(const money &a, const money &b); // вычитание, может быть исключение less_then_0
        friend money operator*(const money &a, const double &b) noexcept; // умножение
        friend money operator*(const money &a, const money &b) noexcept; // умножение

        /* функции сравнения */
        friend bool operator==(const money &a, const money &b) noexcept;
        friend bool operator!=(const money &a, const money &b) noexcept;
        friend bool operator<(const money &a, const money &b) noexcept;
        friend bool operator>(const money &a, const money &b) noexcept;
        friend bool operator<=(const money &a, const money &b) noexcept;
        friend bool operator>=(const money &a, const money &b) noexcept;
    };
    std::string name; // Фамилия
    money sum,  // Оклад
          allowance, // Сумма надбавки
          accrued_sum, // Начисленная сумма
          witheld_sum, // Всего удержано
          final_sum, // Сумма, выдаваемая на руки
          income_tax, // Удержания НДФЛ
          pension; // Пенсионные отчисления
    double percent; // Процент надбавки
    uint8_t work_days, // Рабочие дни
        days_developed; // Отработанные дни
    double percent_of_pension = 0.01, // Процент пенсионных отчислений
           percent_of_income_tax = 0.13; // Процент НДФЛ

    friend double operator/(const money &a, const money &b) noexcept; // деление на money
    friend double operator/(const money &a, const double &b) noexcept; // деление на число

    friend std::istream& operator>>(std::istream& t, money &m); // ввод
    friend std::ostream& operator<<(std::ostream& t, money &m) noexcept; // вывод
    friend money operator+(const money &a, const money &b) noexcept; // сложение
    friend money operator-(const money &a, const money &b); // вычитание, может быть исключение less_then_0
    friend money operator*(const money &a, const double &b) noexcept; // умножение
    friend money operator*(const money &a, const money &b) noexcept; // умножение
    friend unsigned short int ocr(const double &b) noexcept;

    /* функции сравнения */
    friend bool operator==(const money &a, const money &b) noexcept;
    friend bool operator!=(const money &a, const money &b) noexcept;
    friend bool operator<(const money &a, const money &b) noexcept;
    friend bool operator>(const money &a, const money &b) noexcept;
    friend bool operator<=(const money &a, const money &b) noexcept;
    friend bool operator>=(const money &a, const money &b) noexcept;
public:
    void init() noexcept
    {
        allowance = finding_allowance();
        accrued_sum = finding_accrued_sum();
        pension = finding_pension();
        income_tax = finding_income_tax();
        witheld_sum = finding_witheld_sum();
        final_sum = finding_final_sum();
    }
    payment() noexcept
    {
        name = "worker";
        percent = 0;
        work_days = 1;
        days_developed = 1;
        sum = money{100, 0};
        init();
    }
    // имя, процент подбавки, рабочие дни, отработанные дни, оклад в money
    payment(const std::string &n, const double &p, const uint8_t &wd, const uint8_t &dd, const money &s) noexcept
    {
        name = n;
        percent = p/100;
        work_days = wd;
        days_developed = dd;
        sum = s;
        init();
    }
    // имя, процент подбавки, рабочие дни, отработанные дни, оклад в рублях и копейках
    payment(const std::string &n, const double &p, const uint8_t &wd, const uint8_t &dd, unsigned long long R, unsigned char C=0) noexcept
    {
        name = n;
        percent = p/100;
        work_days = wd;
        days_developed = dd;
        sum = money(R, C);
        init();
    }
    friend std::istream& operator>>(std::istream& t, payment &p);

    std::string toString() noexcept;
    friend std::ostream& operator<<(std::ostream& t, payment &p) noexcept;

    void set_sum(const money &s); // Изменение оклада
    void set_sum(unsigned long long R, unsigned char C=0); // Изменение оклада
    void set_allowance(const double &new_allowance); // Изменение надбавки

    money get_sum() { return sum; } // вывод оклада
    money get_allowance() { return allowance; } // вывод надбавки
    money get_accrued_sum() { return accrued_sum; } // вывод начисленых
    money get_witheld_sum() { return witheld_sum; } // вывод удерженых
    money get_final_sum() { return final_sum; } // вывод Сумма, выдаваемая на руки
    money get_income_tax() { return income_tax; } // вывод Удержания НДФЛ

    money finding_allowance() noexcept; // Расчёт суммы начислений

    money finding_accrued_sum() noexcept; // Расчёт суммы пенсионных отчислений

    money finding_pension() noexcept; // Расчёт подоходного налога

    money finding_income_tax() noexcept; // Расчёт удержанной суммы

    money finding_witheld_sum() noexcept; // Сумма, выдаваемая на руки

    money finding_final_sum() noexcept; // Сравнение окладов

    /* функции сравнения по окладу*/
    friend bool operator==(const payment &a, const payment &b) noexcept;
    friend bool operator!=(const payment &a, const payment &b) noexcept;
    friend bool operator<(const payment &a, const payment &b) noexcept;
    friend bool operator>(const payment &a, const payment &b) noexcept;
    friend bool operator<=(const payment &a, const payment &b) noexcept;
};


#endif // PAYMENT_H
