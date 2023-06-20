#include "catch.hpp"
#include "octal.h"
#include "bitstring.h"

TEST_CASE("Проверка работы методов класса octal", "[octal]")
{
    octal o(1, 0);
    // -- тестовые методы --
    SECTION("Тестироавние инициализации класса octal")
    {
        CHECK(o.toString() == "0");
        octal one(1, 0);     CHECK(one.toString() == o.toString());
        octal two(o);       CHECK(two.toString() == one.toString());
        octal three(5);     CHECK(three.toString() == "0");
        octal four(1, 7);    CHECK(four.toString() == "7");
        octal five(5, 7);     CHECK(five.toString() == "7 7 7 7 7");
        octal six("7654321");      CHECK(six.toString() == "7 6 5 4 3 2 1");
        octal seven("1232342341535654734523");     CHECK(seven.toString() == "1 2 3 2 3 4 2 3 4 1 5 3 5 6 5 4 7 3 4 5 2 3");
        CHECK_THROWS
        ( [&]() {
            octal eight(1, 9);
        } () );
        CHECK_THROWS
        ( [&]() {
            octal nine(5, 9);
        } () );
        CHECK_THROWS
        ( [&]() {
            octal ten("12398945678");
        } () );
    }
    SECTION("Метод сложения класса octal")
    {
        octal one(1, 0);
        one += o;                       CHECK(one.toString() == "0");
        octal two("1234");
        octal three = two + two;       CHECK(three.toString() == "2 4 7 0");
        octal fourteen("14");
        octal four = one + octal("14");      CHECK(four.toString() == "1 4");
        four += two;          CHECK(four.toString() == "1 2 5 0");
        four += octal("7500");         CHECK(four.toString() == "1 0 7 5 0");

        octal five("15136");
        five += octal("4321");         CHECK(five.toString() == "2 1 4 5 7");
    }
    SECTION("Метод вычитания класса octal")
    {
        octal one(1, 0);
        one -= o;                       CHECK(one.toString() == "0");
        octal two("4321");
        octal three = two - two;       CHECK(three.toString() == one.toString());
        octal fourty("41");
        octal four = two - fourty;      CHECK(four.toString() == "4 2 6 0");
        four -= one;          CHECK(four.toString() == "4 2 6 0");
        octal five = octal("13320") - octal("6777");         CHECK(five.toString() == two.toString());
        CHECK_THROWS
        ( [&]() {
            five -= octal("7500");
        } () );
        CHECK_THROWS
        ( [&]() {
            octal six = octal("4321") - octal("40221");
        } () );
    }
    SECTION("Метод деления класса octal")
    {
        octal one("54321");
        octal two("4321");
        one /= two;                       CHECK(one.toString() == "1 2");
        octal three = one / two;      CHECK(three.toString() == "0");
        CHECK_THROWS
        ( [&]() {
            octal four = octal("4321") / three;
        } () );
    }
    SECTION("Метод деления c остатком класса octal")
    {
        octal one("54321");
        octal two("4321");
//        one %= two;                       CHECK(one.toString() == "2 4 7");
//        octal three = one % two;      CHECK(three.toString() == "2 4 7");
//        CHECK_THROWS
//        ( [&]() {
//            octal four = octal("4321") % octal(1, 0);
//        } () );
    }
    SECTION("Метод умножения класса octal")
    {
        octal one("12");
        octal two("4321");
        one *= two;                       CHECK(one.toString() == "5 4 0 5 2");
        octal three = octal(1, 0) * two;      CHECK(three.toString() == "0");
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
