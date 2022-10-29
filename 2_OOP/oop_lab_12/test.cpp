#include "catch.hpp"
#include "twelve.h"
#include "six.h"
#include "binary.h"

TEST_CASE("Проверка работы методов класса twelve", "[twelve]")
{
    twelve o(1, 0);
    // -- тестовые методы --
    SECTION("Тестироавние инициализации класса twelve")
    {
        CHECK(o.toString() == "0");
        twelve one(1, 0);     CHECK(one.toString() == o.toString());
        twelve two(o);       CHECK(two.toString() == one.toString());
        twelve three(5);     CHECK(three.toString() == "0");
        twelve four(1, 11);    CHECK(four.toString() == "11");
        twelve five(5, 11);     CHECK(five.toString() == "11 11 11 11 11");
        twelve six("1211321");      CHECK(six.toString() == "1 2 1 1 3 2 1");
        twelve seven("1232342341535654734523");     CHECK(seven.toString() == "1 2 3 2 3 4 2 3 4 1 5 3 5 6 5 4 7 3 4 5 2 3");

        twelve eight({11, 11, 3, 2, 1});      CHECK(eight.toString() == "11 11 3 2 1");
        twelve nine({11, 3, 2, 3, 4, 2, 3, 4, 10, 5, 3, 5, 6, 5, 10, 7, 3, 4, 5, 2, 11});     CHECK(nine.toString() == "11 3 2 3 4 2 3 4 10 5 3 5 6 5 10 7 3 4 5 2 11");
        CHECK_THROWS
        ( [&]() {
            twelve ten(1, 13);
        } () );
        CHECK_THROWS
        ( [&]() {
            twelve eleven(5, 12);
        } () );
        CHECK_THROWS
        ( [&]() {
            twelve tw({12, 11, 3, 2, 1});
        } () );
    }
    SECTION("Метод сложения класса twelve")
    {
        twelve one(1, 0);
        one += o;                       CHECK(one.toString() == "0");
        twelve two("3456");
        twelve three = two + two;       CHECK(three.toString() == "6 8 11 0");
        twelve four = one + twelve({1, 11});      CHECK(four.toString() == "1 11");
        four += two;          CHECK(four.toString() == "3 4 7 5");
        four += twelve("19548");         CHECK(four.toString() == "2 0 10 0 1");

        twelve five("15136");
        five += twelve("9876");         CHECK(five.toString() == "2 2 9 11 0");
    }
    SECTION("Метод вычитания класса twelve")
    {
        twelve one(1, 0);
        one -= o;                       CHECK(one.toString() == "0");
        twelve two("4321");
        twelve three = two - two;       CHECK(three.toString() == one.toString());
        twelve fourty("41");
        twelve four = two - fourty;     CHECK(four.toString() == "4 2 10 0");
        four -= one;          CHECK(four.toString() == "4 2 10 0");
        twelve five = twelve("13320") - twelve({10, 11, 11, 11});         CHECK(five.toString() == two.toString());
        CHECK_THROWS
        ( [&]() {
            five -= twelve("7500");
        } () );
        CHECK_THROWS
        ( [&]() {
            twelve six = twelve("4321") - twelve("40221");
        } () );
    }
    SECTION("Метод деления класса twelve")
    {
        twelve one("54321");
        twelve two("4321");
        one /= two;                     CHECK(one.toString() == "1 3");
        twelve three = one / one;       CHECK(three.toString() == "1");
        three /= two;                   CHECK(three.toString() == "0");
        CHECK_THROWS
        ( [&]() {
            two /= three;
        } () );
    }
    SECTION("Метод деления c остатком класса twelve")
    {
        twelve one("54321");
        twelve two("4321");
        one %= two;                       CHECK(one.toString() == "3 6 10");
        twelve three = one % two;      CHECK(three.toString() == "3 6 10");
        CHECK_THROWS
        ( [&]() {
            two %= twelve(1, 0);
        } () );
    }
    SECTION("Метод умножения класса twelve")
    {
        twelve one("12");
        twelve two("4321");
        one *= two;                       CHECK(one.toString() == "4 11 8 5 2");
        two *= one;                       CHECK(two.toString() == "1 9 2 7 2 4 0 9 2");
        twelve three = twelve(1, 0) * two;      CHECK(three.toString() == "0");
    }
}

TEST_CASE("Проверка работы методов класса six", "[six]")
{
    six o(1, 0);
    // -- тестовые методы --
    SECTION("Тестироавние инициализации класса six")
    {
        CHECK(o.toString() == "0");
        six one(1, 0);     CHECK(one.toString() == o.toString());
        six two(o);       CHECK(two.toString() == one.toString());
        six three(5);     CHECK(three.toString() == "0");
        six four(1, 5);    CHECK(four.toString() == "5");
        six five(5, 5);     CHECK(five.toString() == "5 5 5 5 5");
        six SIX("1211321");      CHECK(SIX.toString() == "1 2 1 1 3 2 1");
        six seven("1232342341535254534523");     CHECK(seven.toString() == "1 2 3 2 3 4 2 3 4 1 5 3 5 2 5 4 5 3 4 5 2 3");

        six eight({5, 5, 3, 2, 1});      CHECK(eight.toString() == "5 5 3 2 1");
        six nine({5, 3, 2, 3, 4, 2, 3, 4, 4, 5, 3, 5, 5, 5, 4, 5, 3, 4, 5, 2, 5});     CHECK(nine.toString() == "5 3 2 3 4 2 3 4 4 5 3 5 5 5 4 5 3 4 5 2 5");
        CHECK_THROWS
        ( [&]() {
            six ten(1, 6);
        } () );
        CHECK_THROWS
        ( [&]() {
            six eleven(5, 6);
        } () );
        CHECK_THROWS
        ( [&]() {
            six tw({6, 5, 3, 2, 1});
        } () );
    }
    SECTION("Метод сложения класса six")
    {
        six one(1, 0);
        one += o;                       CHECK(one.toString() == "0");
        six two("3453");
        six three = two + two;       CHECK(three.toString() == "1 1 3 5 0");
        six four = one + six({1, 5});      CHECK(four.toString() == "1 5");
        four += two;          CHECK(four.toString() == "3 5 1 2");
        four += six("13542");         CHECK(four.toString() == "2 1 4 5 4");

        six five("15135");
        five += six("5555");         CHECK(five.toString() == "2 5 1 3 4");
    }
    SECTION("Метод вычитания класса six")
    {
        six one(1, 0);
        one -= o;                       CHECK(one.toString() == "0");
        six two("4321");
        six three = two - two;       CHECK(three.toString() == one.toString());
        six fourty("41");
        six four = two - fourty;     CHECK(four.toString() == "4 2 4 0");
        four -= one;          CHECK(four.toString() == "4 2 4 0");
        six five = six("13320") - six({5, 5, 5, 5});         CHECK(five.toString() == two.toString());
        CHECK_THROWS
        ( [&]() {
            five -= six("5500");
        } () );
        CHECK_THROWS
        ( [&]() {
            six SIX = six("4321") - six("40221");
        } () );
    }
    SECTION("Метод деления класса six")
    {
        six one("554321");
        six two("4321");
        one /= two;                     CHECK(one.toString() == "1 1 5");
        six three = one / one;       CHECK(three.toString() == "1");
        three /= two;                   CHECK(three.toString() == "0");
        CHECK_THROWS
        ( [&]() {
            two /= three;
        } () );
    }
    SECTION("Метод деления c остатком класса six")
    {
        six one("554321");
        six two("4321");
        one %= two;                       CHECK(one.toString() == "1 2 2");
        six three = one % two;      CHECK(three.toString() == "1 2 2");
        CHECK_THROWS
        ( [&]() {
            two %= six(1, 0);
        } () );
    }
    SECTION("Метод умножения класса six")
    {
        six one("12");
        six two("4321");
        one *= two;                       CHECK(one.toString() == "1 0 0 2 5 2");
        two *= one;                       CHECK(two.toString() == "4 3 4 2 1 0 1 3 2");
        six three = six(1, 0) * two;      CHECK(three.toString() == "0");
    }
}

TEST_CASE("Проверка работы методов класса binary", "[binary]")
{
    binary o(1, 0);
    // -- тестовые методы --
    SECTION("Тестироавние инициализации класса binary")
    {
        CHECK(o.toString() == "0");
        binary one(1, 0);     CHECK(one.toString() == o.toString());
        binary two(o);       CHECK(two.toString() == one.toString());
        binary three(5);     CHECK(three.toString() == "0");
        binary four(1, 1);    CHECK(four.toString() == "1");
        binary five(5, 1);     CHECK(five.toString() == "1 1 1 1 1");
        binary six("1011001");      CHECK(six.toString() == "1 0 1 1 0 0 1");
        binary seven("1010101010111000110");     CHECK(seven.toString() == "1 0 1 0 1 0 1 0 1 0 1 1 1 0 0 0 1 1 0");

        binary eight({1, 0, 1, 0, 1});      CHECK(eight.toString() == "1 0 1 0 1");
        binary nine({1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1});     CHECK(nine.toString() == "1 1 0 1 1 1 0 0 0 0 1 1 1");
        CHECK_THROWS
        ( [&]() {
            binary ten(1, 2);
        } () );
        CHECK_THROWS
        ( [&]() {
            binary eleven(5, 2);
        } () );
        CHECK_THROWS
        ( [&]() {
            binary tw({6, 5, 3, 2, 1});
        } () );
    }
    SECTION("Метод сложения класса binary")
    {
        binary one(1, 0);
        one += o;                       CHECK(one.toString() == "0");
        binary two("1010");
        binary three = two + two;       CHECK(three.toString() == "1 0 1 0 0");
        binary four = two + six(2, 1);      CHECK(four.toString() == "1 1 0 1");
        four += two;          CHECK(four.toString() == "1 0 1 1 1");
        four += six("1000");         CHECK(four.toString() == "1 1 1 1 1 1");

        binary five("111111");
        five += binary("9876");         CHECK(five.toString() == "1 1 1 1 1 1 0");
    }
    SECTION("Метод вычитания класса binary")
    {
        binary one(1, 0);
        one -= o;                       CHECK(one.toString() == "0");
        binary two("1111");
        binary three = two - two;       CHECK(three.toString() == one.toString());
        binary fourty("11");
        binary four = two - fourty;     CHECK(four.toString() == "1 1 0 0");
        four -= one;          CHECK(four.toString() == "1 1 0 0");
        binary five = binary("1111111") - binary({1, 1, 1, 0, 0, 0, 0});         CHECK(five.toString() == two.toString());
        CHECK_THROWS
        ( [&]() {
            five -= binary("11111");
        } () );
        CHECK_THROWS
        ( [&]() {
            binary six = binary("1111") - binary("11111");
        } () );
    }
    SECTION("Метод деления класса binary")
    {
        binary one("11111");
        binary two("1000");
        one /= two;                     CHECK(one.toString() == "1 1");
        binary three = one / one;       CHECK(three.toString() == "1");
        three /= two;                   CHECK(three.toString() == "0");
        CHECK_THROWS
        ( [&]() {
            two /= three;
        } () );
    }
    SECTION("Метод деления c остатком класса binary")
    {
        binary one("11111");
        binary two("1000");
        one %= two;                       CHECK(one.toString() == "1 1 1");
        binary three = one % two;      CHECK(three.toString() == "1 1 1");
        CHECK_THROWS
        ( [&]() {
            two %= binary(1, 0);
        } () );
    }
    SECTION("Метод умножения класса binary")
    {
        binary one("11");
        binary two("1110");
        one *= two;                       CHECK(one.toString() == "1 0 1 0 1 0");
        two *= one;                       CHECK(two.toString() == "1 0 0 1 0 0 1 1 0 0");
        binary three = binary(1, 0) * two;      CHECK(three.toString() == "0");
    }
}

TEST_CASE("Проверка работы методов класса six", "[six]")
{
    six o(1, 0);
    // -- тестовые методы --
    SECTION("Тестироавние инициализации класса six")
    {
        CHECK(o.toString() == "0");
        six one(1, 0);     CHECK(one.toString() == o.toString());
        six two(o);       CHECK(two.toString() == one.toString());
        six three(5);     CHECK(three.toString() == "0");
        six four(1, 5);    CHECK(four.toString() == "5");
        six five(5, 5);     CHECK(five.toString() == "5 5 5 5 5");
        six SIX("1211321");      CHECK(SIX.toString() == "1 2 1 1 3 2 1");
        six seven("1232342341535254534523");     CHECK(seven.toString() == "1 2 3 2 3 4 2 3 4 1 5 3 5 2 5 4 5 3 4 5 2 3");

        six eight({5, 5, 3, 2, 1});      CHECK(eight.toString() == "5 5 3 2 1");
        six nine({5, 3, 2, 3, 4, 2, 3, 4, 4, 5, 3, 5, 5, 5, 4, 5, 3, 4, 5, 2, 5});     CHECK(nine.toString() == "5 3 2 3 4 2 3 4 4 5 3 5 5 5 4 5 3 4 5 2 5");
        CHECK_THROWS
        ( [&]() {
            six ten(1, 6);
        } () );
        CHECK_THROWS
        ( [&]() {
            six eleven(5, 6);
        } () );
        CHECK_THROWS
        ( [&]() {
            six tw({6, 5, 3, 2, 1});
        } () );
    }
    SECTION("Метод сложения класса six")
    {
        six one(1, 0);
        one += o;                       CHECK(one.toString() == "0");
        six two("3453");
        six three = two + two;       CHECK(three.toString() == "1 1 3 5 0");
        six four = one + six({1, 5});      CHECK(four.toString() == "1 5");
        four += two;          CHECK(four.toString() == "3 5 1 2");
        four += six("13542");         CHECK(four.toString() == "2 1 4 5 4");

        six five("15135");
        five += six("5555");         CHECK(five.toString() == "2 5 1 3 4");
    }
    SECTION("Метод вычитания класса six")
    {
        six one(1, 0);
        one -= o;                       CHECK(one.toString() == "0");
        six two("4321");
        six three = two - two;       CHECK(three.toString() == one.toString());
        six fourty("41");
        six four = two - fourty;     CHECK(four.toString() == "4 2 4 0");
        four -= one;          CHECK(four.toString() == "4 2 4 0");
        six five = six("13320") - six({5, 5, 5, 5});         CHECK(five.toString() == two.toString());
        CHECK_THROWS
        ( [&]() {
            five -= six("5500");
        } () );
        CHECK_THROWS
        ( [&]() {
            six SIX = six("4321") - six("40221");
        } () );
    }
    SECTION("Метод деления класса six")
    {
        six one("554321");
        six two("4321");
        one /= two;                     CHECK(one.toString() == "1 1 5");
        six three = one / one;       CHECK(three.toString() == "1");
        three /= two;                   CHECK(three.toString() == "0");
        CHECK_THROWS
        ( [&]() {
            two /= three;
        } () );
    }
    SECTION("Метод деления c остатком класса six")
    {
        six one("554321");
        six two("4321");
        one %= two;                       CHECK(one.toString() == "1 2 2");
        six three = one % two;      CHECK(three.toString() == "1 2 2");
        CHECK_THROWS
        ( [&]() {
            two %= six(1, 0);
        } () );
    }
    SECTION("Метод умножения класса six")
    {
        six one("12");
        six two("4321");
        one *= two;                       CHECK(one.toString() == "1 0 0 2 5 2");
        two *= one;                       CHECK(two.toString() == "4 3 4 2 1 0 1 3 2");
        six three = six(1, 0) * two;      CHECK(three.toString() == "0");
    }
}

TEST_CASE("Проверка работы методов мультиметодов", "[mult]")
{
    binary b;
    twelve t;
    six s;
    // -- тестовые методы --
    SECTION("dynamic cast")
    {
        CHECK(b.Operator_dymamic_cast(b) == "B-B");
        CHECK(b.Operator_dymamic_cast(t) == "B-T");
        CHECK(b.Operator_dymamic_cast(s) == "B-S");

        CHECK(t.Operator_dymamic_cast(t) == "T-T");
        CHECK(t.Operator_dymamic_cast(b) == "T-B");
        CHECK(t.Operator_dymamic_cast(s) == "T-S");

        CHECK(s.Operator_dymamic_cast(s) == "S-S");
        CHECK(s.Operator_dymamic_cast(t) == "S-T");
        CHECK(s.Operator_dymamic_cast(b) == "S-B");
    }
    SECTION("typeid")
    {
        CHECK(b.Operator_typeid(b) == "B-B");
        CHECK(b.Operator_typeid(t) == "B-T");
        CHECK(b.Operator_typeid(s) == "B-S");

        CHECK(t.Operator_typeid(t) == "T-T");
        CHECK(t.Operator_typeid(b) == "T-B");
        CHECK(t.Operator_typeid(s) == "T-S");

        CHECK(s.Operator_typeid(s) == "S-S");
        CHECK(s.Operator_typeid(t) == "S-T");
        CHECK(s.Operator_typeid(b) == "S-B");
    }
    SECTION("virtual")
    {
        CHECK(b.Operator_virtual(b) == "B-B");
        CHECK(b.Operator_virtual(t) == "B-T");
        CHECK(b.Operator_virtual(s) == "B-S");

        CHECK(t.Operator_virtual(t) == "T-T");
        CHECK(t.Operator_virtual(b) == "T-B");
        CHECK(t.Operator_virtual(s) == "T-S");

        CHECK(s.Operator_virtual(s) == "S-S");
        CHECK(s.Operator_virtual(t) == "S-T");
        CHECK(s.Operator_virtual(b) == "S-B");
    }
}
