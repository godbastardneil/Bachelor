#include "catch.hpp"
#include "rational.h"

TEST_CASE("Проверка работы методов класса rational", "[rational]")
{
    rational p;

    // -- тестовые методы --
    SECTION("Тестироавние инициализации класса rational")
    {
        CHECK(p.toString() == "(1, 1)");
        rational two(1, 1);     CHECK(two.toString() == p.toString());
        rational three(2, 1);     CHECK(three.toString() != two.toString());
        rational three2(2, 1);     CHECK(three.toString() == three2.toString());
        CHECK_THROWS
        ( [&]() {
            rational four(2, 0);
        } () );
    }
    // (a, b) + (c, d) = (a * d + b * c, b * d)
    SECTION("Метод Сложения")       // -- тестирование сложения
    {
        rational one;
        one += p;                       CHECK(one.toString() == "(2, 1)");
        rational two = one + one;       CHECK(two.toString() == "(4, 1)");
        two = one + rational(1,4);      CHECK(two.toString() == "(9, 4)");
        two += rational(2, 3);          CHECK(two.toString() == "(35, 12)");
    }
    // (a, b) / (c, d) = (a * d, b * c)
    SECTION("Метод Деления")       // -- тестирование деления
    {
        rational one;
        one /= p;                       CHECK(one.toString() == "(1, 1)");
        rational two = one / one;       CHECK(two.toString() == "(1, 1)");
        two = one / rational(1,4);      CHECK(two.toString() == "(4, 1)");
        two = one / rational(3,4);      CHECK(two.toString() == "(4, 3)");
        two /= rational(2, 3);          CHECK(two.toString() == "(12, 6)");
    }
    //(a, b) * (c, d) = (a * c, b * d)
    SECTION("Метод Умножения")       // -- тестирование умножения
    {
        rational one;
        one *= p;                       CHECK(one.toString() == "(1, 1)");
        rational two = one * one;       CHECK(two.toString() == "(1, 1)");
        two = one * rational(2,4);      CHECK(two.toString() == "(2, 4)");
        two = rational(2,4) * rational(3,4);      CHECK(two.toString() == "(6, 16)");
        two *= rational(2, 1);          CHECK(two.toString() == "(12, 16)");
    }
    //(a, b) – (c, d) = (a * d – b * c, b * d)
    SECTION("Метод Вычитания")       // -- тестирование вычитания
    {
        rational one;
        one -= p;                       CHECK(one.toString() == "(0, 1)");
        rational two = one - p;       CHECK(two.toString() == "(-1, 1)");
        two =  rational(-1,1) - rational(1,4);      CHECK(two.toString() == "(-5, 4)");
        two -= rational(2, 3);          CHECK(two.toString() == "(-23, 12)");
    }
}
