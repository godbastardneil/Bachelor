#include "catch.hpp"
#include "creditmap.h"

TEST_CASE("Проверка работы методов класса rational", "[creditmap]")
{
    CreditMap cm0;

    // -- тестовые методы --
    SECTION("Тестироавние инициализации класса creditmap")
    {
        std::string s = "Номер карты: 000000";
                    s += "\nФамилия владельца: user";
                    s += "\nДата окончания: 0";
                    s += "\nДата последнего снятия: 0";
                    s += "\nКоличест во дней после снятия без штрафа: 0";
                    s += "\nПроцент штрафа: 0.000000";
                    s += "\nЛимит снимаемой суммы: 0,00 руб.";
        CHECK(cm0.toString() == s);
        CreditMap cm1(money(500, 50), "123456", "Neil", 30, 0, 30, 0.0);
        std::string s2 = "Номер карты: 123456";
                    s2 += "\nФамилия владельца: Neil";
                    s2 += "\nДата окончания: 30";
                    s2 += "\nДата последнего снятия: 0";
                    s2 += "\nКоличест во дней после снятия без штрафа: 30";
                    s2 += "\nПроцент штрафа: 0.000000";
                    s2 += "\nЛимит снимаемой суммы: 500,50 руб.";
        CHECK(cm1.toString() == s2);
        CHECK(cm1.toString() != cm0.toString());
        CHECK_THROWS
        ( [&]() {
            CreditMap c2(money(500, 150), "000000", "user", 0, 0, 0, 0);
        } () );
    }
    SECTION("Метод Уменьшения лимита снятия")       // -- тестирование вычитания
    {
        CreditMap cm1 (money(1000, 0), "000000", "user", 0, 0, 0, 0);
        money m(500, 0);
        CreditMap cm2 = cm1 - m;
        std::string s = "Номер карты: 000000";
                    s += "\nФамилия владельца: user";
                    s += "\nДата окончания: 0";
                    s += "\nДата последнего снятия: 0";
                    s += "\nКоличест во дней после снятия без штрафа: 0";
                    s += "\nПроцент штрафа: 0.000000";
                    s += "\nЛимит снимаемой суммы: 500,00 руб.";
        CHECK(cm2.toString() != cm1.toString());
        CHECK(cm2.toString() == s);
        money m1(0, 0);
        CreditMap cm3 = cm2 - m1;
        CHECK(cm3.toString() == cm2.toString());
        money m2(1000, 0);
        CHECK_THROWS
        ( [&]() {
            CreditMap cm4 = cm3 - m2;
        } () );
    }
    SECTION("Метод Увеличения лимита снятия")       // -- тестирование сложения
    {
        CreditMap cm1 (money(1000, 0), "000000", "user", 0, 0, 0, 0);
        money m(500, 0);
        CreditMap cm2 = cm1 + m;
        std::string s = "Номер карты: 000000";
                    s += "\nФамилия владельца: user";
                    s += "\nДата окончания: 0";
                    s += "\nДата последнего снятия: 0";
                    s += "\nКоличест во дней после снятия без штрафа: 0";
                    s += "\nПроцент штрафа: 0.000000";
                    s += "\nЛимит снимаемой суммы: 1500,00 руб.";
        CHECK(cm2.toString() != cm1.toString());
        CHECK(cm2.toString() == s);
        money m1(0, 0);
        CreditMap cm3 = cm2 + m1;
        CHECK(cm3.toString() == cm2.toString());
    }
    SECTION("Методы сравнения кредитных карт по лимиту снятия")       // -- тестирование сложения
    {
        CreditMap cm1 (money(1000, 0), "000000", "user", 0, 0, 0, 0);
        CreditMap cm2 (money(1000, 0), "000000", "user", 0, 0, 0, 0);
        CreditMap cm3 (money(1500, 0), "000000", "user", 0, 0, 0, 0);
        CreditMap cm4 (money( 500, 0), "000000", "user", 0, 0, 0, 0);

        CHECK(cm1 == cm2);
        CHECK(cm1 <= cm2);
        CHECK(cm1 >= cm2);
        CHECK(cm1 != cm4);
        CHECK(cm1 < cm3);
        CHECK(cm1 <= cm3);
        CHECK(cm1 != cm4);
        CHECK(cm1 > cm4);
        CHECK(cm1 >= cm4);

        CHECK(cm2 != cm3);
        CHECK(cm2 < cm3);
        CHECK(cm2 <= cm3);
        CHECK(cm2 > cm4);
        CHECK(cm2 >= cm4);

        CHECK(cm3 != cm4);
        CHECK(cm3 > cm4);
        CHECK(cm3 >= cm4);
    }
}
