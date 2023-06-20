#include "catch.hpp"
#include "alg.h"

TEST_CASE("Проверка работы длинной арифметики") {

    num n;    // -- нулевой объект нужен всем --

    // - определение чистой виртуальной функции run() класса Test --

    // -- тестовые методы --
    SECTION("Длинная арифметика")   		// -- с оздание и присваивание
    {

        num a = {p, 1};
        num b = {p, 1,5,0};
        num c = {p, 1,0,1};
        CHECK(toString(a) == "+1");
        CHECK(toString(b) == "+ 51");
        CHECK(toString(c) == "+ 101");

        num ar1 = b-a;
        num ar2 = c-b;
        CHECK(((ar1 == ar2) && (ar1[0] == ar2[0])));

        num ost1 = b;
        num geo1 = ost1/a;
        num ost2 = c;
        num geo2 = ost2/b;
        CHECK((((geo1 != geo2) || (geo1[0] != geo2[0])) || ((ost1 != ost2) || (ost1[0] != ost2[0]))));


        a = {p, 3};
        b = {p, 9};
        c = {p, 9,8,7,6,5,4,3,2,1};
        CHECK(toString(a) == "+3");
        CHECK(toString(b) == "+9");
        CHECK(toString(c) == "+ 123 456 789");

        ar1 = b-a;
        ar2 = c-b;
        CHECK(((ar1 != ar2) || (ar1[0] != ar2[0])));

        ost1 = b;
        geo1 = ost1/a;
        ost2 = c;
        geo2 = ost2/b;
        CHECK((((geo1 != geo2) || (geo1[0] != geo2[0])) || ((ost1 != ost2) || (ost1[0] != ost2[0]))));


        a = {m, 9};
        b = {p, 5,8};
        c = {m, 9,6,7};
        CHECK(toString(a) == "-9");
        CHECK(toString(b) == "+ 85");
        CHECK(toString(c) == "- 769");

        ar1 = b-a;
        ar2 = c-b;
        CHECK(((ar1 != ar2) || (ar1[0] != ar2[0])));

        ost1 = b;
        geo1 = ost1/a;
        ost2 = c;
        geo2 = ost2/b;
        CHECK((((geo1 == geo2) && (geo1[0] == geo2[0])) && ((ost1 == ost2) && (ost1[0] == ost2[0]))));

        a = {m, 9};
        b = {m, 5,8};
        c = {m, 9,6,7};
        CHECK(toString(a) == "-9");
        CHECK(toString(b) == "- 85");
        CHECK(toString(c) == "- 769");

        ar1 = b-a;
        ar2 = c-b;
        CHECK(((ar1 != ar2) || (ar1[0] != ar2[0])));

        ost1 = b;
        geo1 = ost1/a;
        ost2 = c;
        geo2 = ost2/b;
        CHECK((((geo1 == geo2) && (geo1[0] == geo2[0])) && ((ost1 == ost2) && (ost1[0] == ost2[0]))));
    }

}
