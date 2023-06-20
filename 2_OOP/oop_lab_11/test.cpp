#include "catch.hpp"
#include "twelve.h"
#include "bitstring.h"

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
        twelve fourteen("14");
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

TEST_CASE("Проверка работы методов класса bitstring", "[bitstring]")
{
    bitstring b(8, 0);
    // -- тестовые методы --
    SECTION("Тестироавние инициализации класса bitstring")
    {
        CHECK(b.toString() == "0 0 0 0 0 0 0 0");
        bitstring one("00000000");      CHECK(one.toString() == b.toString());
        bitstring two(8);     CHECK(two.toString() == one.toString());
        bitstring three(one);     CHECK(three.toString() == two.toString());
        bitstring four("10101010");      CHECK(four.toString() == "1 0 1 0 1 0 1 0");
        bitstring five(8, 1);     CHECK(five.toString() == "1 1 1 1 1 1 1 1");
        CHECK(five.toString() != four.toString());
        CHECK(five.toString() != three.toString());
        CHECK(four.toString() != three.toString());
        CHECK_THROWS
        ( [&]() {
            bitstring ("2222");
        } () );
        CHECK_THROWS
        ( [&]() {
            bitstring (1, 5);
        } () );
    }
    SECTION("Метод И класса bitstring")
    {
        bitstring one("00000000");
        one &= b;       CHECK(one.toString() == "0 0 0 0 0 0 0 0");
        bitstring two("11111111");
        bitstring three = one & two;       CHECK(three.toString() == "0 0 0 0 0 0 0 0");
        bitstring four("10101010");
        four &= two;       CHECK(four.toString() == "1 0 1 0 1 0 1 0");
        bitstring five("01010101");
        five &= four;       CHECK(five.toString() == "0 0 0 0 0 0 0 0");
        bitstring six("10100101");
        bitstring seven = four & six;       CHECK(seven.toString() == "1 0 1 0 0 0 0 0");
        bitstring eight("01011010");
        bitstring nine = four & eight;       CHECK(nine.toString() == "0 0 0 0 1 0 1 0");
    }
    SECTION("Метод ИЛИ класса bitstring")
    {
        bitstring one("00000000");
        one |= b;       CHECK(one.toString() == "0 0 0 0 0 0 0 0");
        bitstring two("11111111");
        bitstring three = one | two;       CHECK(three.toString() == "1 1 1 1 1 1 1 1");
        bitstring four("10101010");
        two |= four;       CHECK(two.toString() == "1 1 1 1 1 1 1 1");
        bitstring five("01010101");
        five |= four;       CHECK(five.toString() == "1 1 1 1 1 1 1 1");
        bitstring six = four | one;       CHECK(six.toString() == "1 0 1 0 1 0 1 0");
    }
    SECTION("Метод НЕ класса bitstring")
    {
        bitstring one = ~b;     CHECK(one.toString() == "1 1 1 1 1 1 1 1");
        bitstring two = ~one;       CHECK(two.toString() == b.toString());
        bitstring three("10101010");
        bitstring four = ~three;       CHECK(four.toString() == "0 1 0 1 0 1 0 1");
        bitstring five = ~four;       CHECK(five.toString() == three.toString());
    }
    SECTION("Методы смещения вправо и влево класса bitstring")
    {
        bitstring one = b << 2;         CHECK(one.toString() == "0 0 0 0 0 0 0 0 0 0");
        bitstring two("10101010");
        two <<= 4;         CHECK(two.toString() == "1 0 1 0 1 0 1 0 0 0 0 0");
        two >>= 4;         CHECK(two.toString() == "0 0 0 0 1 0 1 0 1 0 1 0 0 0 0 0");
        two <<= 2;         CHECK(two.toString() == "0 0 0 0 1 0 1 0 1 0 1 0 0 0 0 0 0 0");
        bitstring three = bitstring("11111111") >> 5;         CHECK(three.toString() == "0 0 0 0 0 1 1 1 1 1 1 1 1");
    }
}
