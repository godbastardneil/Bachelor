#ifndef TEST_H
#define TEST_H

#include "money.h"
#include "unittest.h"

using namespace UnitTest;         // -- чтобы не писать полные имена --

// -- в тестовых методах пишутся вызовы макроса check() --
class test: public uTest
{
    money m;    // -- нулевой объект нужен всем --
public:

    // - определение чистой виртуальной функции run() класса Test --
    void run() override                  // -- вызов тестовых методв --
    {
        testCreate();		// -- тест конструкторов и присваивания
        testAdd();			// -- тест сложения
        testMin();     		// -- тестирование вычитания
        testDelMM();        // -- тестирование деления money / money
        testDelMd(); 		// -- тестирование деления money / double
        testUmno();     	// -- тестирование деления money * double
        testCompare();		// -- тест сравнения
    }
    // -- тестовые методы --
    void testCreate()   		// -- создание и присваивание
    {
        money two;           check(m == two);
                             check(two.toString() == "0,00 руб.");
        money d0(12, 34);    check(d0.toString() == "12,34 руб.");
        money dd0(56);       check(dd0.toString() == "56,00 руб.");
        try {
            money d1(12, 134);
            fail();
        } catch (money::more_then_99) { success(); }
        try { // 1 -- ошибка - будет просто 0,16 руб. -- то есть не будет
            money dd1(0, 16);
            fail();
        } catch (money::more_then_99) { success(); }
    }
    void testAdd()       		// -- тестирование сложения
    {
        money one;
        one += money{1, 1};       check(one.toString() == "1,01 руб.");
        money two = one + one;    check(two.toString() == "2,02 руб.");
        two = one + money{3, 3};  check(two.toString() == "4,04 руб.");
        two += money{0, 66};      check(two.toString() == "5,10 руб."); // 2 -- ошибка - должно быть 4,70
        two += money{5};          check(two.toString() == "9,70 руб.");
    }
    void testMin()       		// -- тестирование вычитания
    {
        money one {5, 5};
        one -= money{1, 1};       check(one.toString() == "4,04 руб.");
        money two = one - one;    check(two.toString() == "0,00 руб.");
        two = one - money{1, 1};  check(two.toString() == "3,03 руб.");
        two -= money{1, 3};     check(two.toString() == "2,01 руб."); // 3 -- ошибка - должно быть 2,00
        try {
            two = one - money{1}; // two = 3,04
            success();
        } catch (money::less_then_0) {
            fail();
        }
        try {
            two -= money{3, 5}; // two = -0,01
            fail();
        } catch (money::less_then_0) {
            success();
        }
        try {
            two = one - money{5, 4}; // two = -1,00
            fail();
        } catch (money::less_then_0) {
            success();
        }
    }
    void testDelMM()       		// -- тестирование деления money / money
    {
        money one {5, 5};
        double d = one / money{1, 1};           check(d == 5.00);
        d = one / money{5, 5};                  check(fabs(d - 1.1) < 0.001); // 4 -- ошибка - должно быть 100
        d = money{1, 1} / one;                  check(fabs(d - 0.2) < 0.001);
        d = one / money{0, 20};                 check(d == 25.25);
        d = money{0, 20} / money(0, 20);        check(d == 1.00);
    }
    void testDelMd()       		// -- тестирование деления money / double
    {
        money one {5, 5};
        double d = one / 1.01;          check(d == 500.0);
        d = one / 5.05;                 check(d == 101.0); // 5 -- ошибка - должно быть 1.00
        d = money{1, 1} / 5.05;         check(d == 20.0);
        d = one / 0.20;                 check(d == 2525.0);
        d = money{0, 20} / 0.20;        check(d == 100.0);
    }
    void testUmno()       		// -- тестирование деления money * double
    {
        money one {5, 5};
        one *= 4;                 check(one.toString() == "20,20 руб.");
        one = money(1, 1);
        one *= 1.5;               check(one.toString() == "1,51 руб.");
        one *= 10;                check(one.toString() == "15,01 руб."); // 6 -- ошибка - должно быть 15,10
        one *= 0.56;              check(one.toString() == "8,45 руб.");
        one *= 1.56;              check(one.toString() == "13,18 руб.");
    }
    void testCompare()    		// -- проверка сравнения
    {
        money a{1, 1};
        money b{1, 11};
        money c{1, 11};
        money d{11, 1};

        check(a < b);
        check(a < c);
        check(a < d);
        check(a > b);       // 7 -- ошибка --
        check(a > c);       // 8 -- ошибка --
        check(a > d);       // 9 -- ошибка --
        check(a == b);      // 10 -- ошибка --
        check(a == c);      // 11 -- ошибка --
        check(a == d);      // 12 -- ошибка --
        check(a <= b);
        check(a <= c);
        check(a <= d);
        check(a >= b);      // 13 -- ошибка --
        check(a >= c);      // 14 -- ошибка --
        check(a >= d);      // 15 -- ошибка --

        check(b < c);       // 16 -- ошибка --
        check(b < d);
        check(b > c);       // 17 -- ошибка --
        check(b > d);       // 18 -- ошибка --
        check(b == c);
        check(b == d);      // 19 -- ошибка --
        check(b <= c);
        check(b <= d);
        check(b >= c);
        check(b >= d);       // 20 -- ошибка --

        check(c < d);
        check(c > d);       // 21 -- ошибка --
        check(c == d);      // 22 -- ошибка --
        check(c <= d);
        check(c >= d);       // 23 -- ошибка --
    }
};

#endif // TEST_H
