#include "catch.hpp"
#include "money.h"

TEST_CASE("Проверка работы методов класса money", "[money]") {

    money m;    // -- нулевой объект нужен всем --

    // - определение чистой виртуальной функции run() класса Test --

    // -- тестовые методы --
    SECTION("Инициализация переменных класса money")   		// -- создание и присваивание
    {
        money two;           CHECK(m == two);
                             CHECK(two.toString() == "0,00 руб.");
        money d0(12, 34);    CHECK(d0.toString() == "12,34 руб.");
        money dd0(56);       CHECK(dd0.toString() == "56,00 руб.");
        CHECK_THROWS
        ( [&]() {
            money d1(12, 134);
        } () );
        CHECK_THROWS // 1 -- ошибка -- будет просто 0,16 - не должно выводить исключение, по этому выведется ошибка
        ( [&]() {
            money dd1(1, 16);
        } () );
    }
    SECTION("Метод Сложения")       // -- тестирование сложения
    {
        money one;
        one += money{1, 1};       CHECK(one.toString() == "1,01 руб.");
        money two = one + one;    CHECK(two.toString() == "2,02 руб.");
        two = one + money{3, 3};  CHECK(two.toString() == "4,04 руб.");
        two += money{0, 66};      CHECK(two.toString() == "5,10 руб."); // 2 -- ошибка - должно быть 4,70
        two += money{5};          CHECK(two.toString() == "9,70 руб.");
    }
    SECTION("Метод Вычитания")       // -- тестирование вычитания
    {
        money one {5, 5};
        one -= money{1, 1};       CHECK(one.toString() == "4,04 руб.");
        money two = one - one;    CHECK(two.toString() == "0,00 руб.");
        two = one - money{1, 1};  CHECK(two.toString() == "3,03 руб.");
        two -= money{1, 3};     CHECK(two.toString() == "2,01 руб."); // 3 -- ошибка - должно быть 2,00

        CHECK_THROWS // 4 -- ошибка - не должно выводить исключение, по этому выведется ошибка
        ( [&]() {
            money one{4, 4};
            two = one - money{1};
        } () );

        CHECK_THROWS
        ( [&]() {
            two -= money{3, 5};
        } () );

        CHECK_THROWS
        ( [&]() {
            two = one - money{5, 4};
        } () );

    }
    SECTION("Метод Деления money / money")       // -- тестирование деления money / money
    {
        money one {5, 5};
        double d = one / money{1, 1};           CHECK(d == 5.00);
        d = one / money{5, 5};                  CHECK(fabs(d - 1.1) < 0.001); // 5 -- ошибка - должно быть 1.00
        d = money{1, 1} / one;                  CHECK(fabs(d - 0.2) < 0.001);
        d = one / money{0, 20};                 CHECK(d == 25.25);
        d = money{0, 20} / money(0, 20);        CHECK(d == 1.00);
    }
    SECTION("Метод Деления money / double")       // -- тестирование деления money / double
    {
        money one {5, 5};
        double d = one / 1.01;          CHECK(d == 500.0);
        d = one / 5.05;                 CHECK(d == 101.0); // 6 -- ошибка - должно быть 1.00
        d = money{1, 1} / 5.05;         CHECK(d == 20.0);
        d = one / 0.20;                 CHECK(d == 2525.0);
        d = money{0, 20} / 0.20;        CHECK(d == 100.0);
    }
    SECTION("Метод Деления money * double")       // -- тестирование деления money * double
    {
        money one {5, 5};
        one *= 4;                 CHECK(one.toString() == "20,20 руб.");
        one = money(1, 1);
        one *= 1.5;               CHECK(one.toString() == "1,51 руб.");
        one *= 10;                CHECK(one.toString() == "15,01 руб."); // 7 -- ошибка - должно быть 15,10
        one *= 0.56;              CHECK(one.toString() == "8,45 руб.");
        one *= 1.56;              CHECK(one.toString() == "13,18 руб.");
    }
    SECTION("Методы Сравнения")       // -- проверка сравнения
    {
        money a{1, 1};
        money b{1, 11};
        money c{1, 11};
        money d{11, 1};

        CHECK(a < b);
        CHECK(a < c);
        CHECK(a < d);
        CHECK(a > b);       // 8 -- ошибка --
        CHECK(a > c);       // 9 -- ошибка --
        CHECK(a > d);       // 10 -- ошибка --
        CHECK(a == b);      // 11 -- ошибка --
        CHECK(a == c);      // 12 -- ошибка --
        CHECK(a == d);      // 13 -- ошибка --
        CHECK(a <= b);
        CHECK(a <= c);
        CHECK(a <= d);
        CHECK(a >= b);      // 14 -- ошибка --
        CHECK(a >= c);      // 15 -- ошибка --
        CHECK(a >= d);      // 16 -- ошибка --

        CHECK(b < c);       // 17 -- ошибка --
        CHECK(b < d);
        CHECK(b > c);       // 18 -- ошибка --
        CHECK(b > d);       // 19 -- ошибка --
        CHECK(b == c);
        CHECK(b == d);      // 20 -- ошибка --
        CHECK(b <= c);
        CHECK(b <= d);
        CHECK(b >= c);
        CHECK(b >= d);       // 21 -- ошибка --

        CHECK(c < d);
        CHECK(c > d);       // 22 -- ошибка --
        CHECK(c == d);      // 23 -- ошибка --
        CHECK(c <= d);
        CHECK(c >= d);       // 24 -- ошибка --
    }
}
