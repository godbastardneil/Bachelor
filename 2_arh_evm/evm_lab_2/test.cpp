#include "catch.hpp"
#include "long.h"

TEST_CASE("Проверка работы методов класса long", "[long]")
{
    Long l;
    // -- тестовые методы --
    SECTION("Тестироавние инициализации класса long")
    {
        CHECK(l.toString() == "0");
        Long one(0);     CHECK(one.toString() == l.toString());
        Long two(1, 10);       CHECK(two.toString() == "4294967306"); // (2^32)*1+10
        Long three("10");     CHECK(three.toString() == "10");
        Long four(7);    CHECK(four.toString() == "7");
        Long five(4294967295);     CHECK(five.toString() == "4294967295");
//        Long six("18446744073709551615");      CHECK(six.toString() == "18446744073709551615"); // max
        Long seven(2, 1);     CHECK(seven.toString() == "8589934593"); // (2^32)*2+1
        Long eight(4294967297);     CHECK(eight.toString() == "1");
//o        Long nine(4294967295, 0);      CHECK(nine.toString() == six.toString()); // max
        CHECK_THROWS
        ( [&]() {
            Long ten("42949672954294967295123");
        } () );
    }
    SECTION("Методы инкременты и декременты класса long")
    {
        ++l;     CHECK(l.toString() == "1");
        --l;     CHECK(l.toString() == "0");
        CHECK((++l).toString() == "1");
        CHECK((--l).toString() == "0");
        CHECK((l++).toString() == "0");
        CHECK(l.toString() == "1");
        CHECK((l--).toString() == "1");
        CHECK(l.toString() == "0");
    }
    SECTION("Метод сложения класса long")
    {
        Long one(0);
        one += l;                       CHECK(one.toString() == l.toString());
        Long two(1234);
        Long three = two + two;       CHECK(three.toString() == "2468");
        Long five(4294967295);
        five += three;       CHECK(five.toString() == "4294969763");
        Long six(4294967295);
        six += three;       CHECK(six.toString() == five.toString());
        six += five;       CHECK(six.toString() == "8589939526");
    }
    SECTION("Метод вычитания класса long")
    {
        Long one(0);
        one -= l;                       CHECK(one.toString() == l.toString());
        Long two(1234);
        Long three = two - two;       CHECK(three.toString() == one.toString());
        Long five(3709551615);
        five -= three;       CHECK(five.toString() == "3709551615");
    }
    SECTION("Метод деления класса long")
    {
        Long one(54321);
        Long two(4321);
        one /= two;                       CHECK(one.toString() == "12");
        Long four = two / 1;      CHECK(four.toString() == two.toString());
        Long three = one / two;      CHECK(three.toString() == "0");
        CHECK_THROWS
        ( [&]() {
            four = Long("4321") / three;
        } () );
    }
    SECTION("Метод остаток от деления класса long")
    {
        Long one(54321);
        Long two(4321);
        one %= two;                       CHECK(one.toString() == "2469");
        Long three = one % two;      CHECK(three.toString() == "2469");
        Long four = two / 1;      CHECK(four.toString() == two.toString());
        CHECK_THROWS
        ( [&]() {
            four = Long(4321) % (0);
        } () );
    }
    SECTION("Метод умножения класса long")
    {
        Long one(12);
        Long two(4321);
        one *= two;                       CHECK(one.toString() == "51852");
        Long three = (0) * two;      CHECK(three.toString() == "0");
    }
}
