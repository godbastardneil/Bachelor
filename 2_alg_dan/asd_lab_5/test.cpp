﻿#include "catch.hpp"
#include "realty.h"

TEST_CASE("Проверка работы методов класса tree", "[tree]")
{
    // -- тестовые методы --
    SECTION("Тестироавние инициализации класса tree")
    {
        tree zero;
        CHECK(zero.to_string() == "");

        tree::data_t dt(12345678, tree::value_t(1, 100, 50, 10, 10, 2010, 100000, "89996014435"));
        tree::data_t dt1(12345679, tree::value_t(1, 100, 50, 10, 10, 2010, 100000, "89996014435"));
        tree::data_t dt2(12345680, tree::value_t(1, 100, 50, 10, 10, 2010, 100000, "89996014435"));
        tree t1(dt);
        CHECK(t1.to_string() == "12345678 1 100.000000 50.000000 10102010 100000.000000 89996014435\n");

        tree t2({dt, dt1, dt2});
        CHECK(t2.to_string() == "12345678 1 100.000000 50.000000 10102010 100000.000000 89996014435\n12345679 1 100.000000 50.000000 10102010 100000.000000 89996014435\n12345680 1 100.000000 50.000000 10102010 100000.000000 89996014435\n");

        CHECK_THROWS
        ( [&]() {
            tree r4({dt, dt});
        } () );
        CHECK_THROWS
        ( [&]() {
            tree r5({tree::data_t(123456789, tree::value_t(1, 100, 50, 10, 10, 2010, 100000, "89996014435"))});
        } () );
    }
    SECTION("Методы tree")
    {
        tree::data_t dt0(12345678, tree::value_t(1, 100, 50, 10, 10, 2010, 100000, "89996014435"));
        tree::data_t dt1(12345679, tree::value_t(2, 101, 51, 11, 11, 2011, 100001, "89996014436"));
        tree::data_t dt2(12345680, tree::value_t(3, 102, 52, 12, 12, 2012, 100002, "89996014437"));
        tree t1({dt0});

        t1.insert(dt1);
        std::string s = "12345678 1 100.000000 50.000000 10102010 100000.000000 89996014435\n";
        s += "12345679 2 101.000000 51.000000 11112011 100001.000000 89996014436\n";
        CHECK(t1.to_string() == s);

        t1.erase(12345679);
        s = "12345678 1 100.000000 50.000000 10102010 100000.000000 89996014435\n";
        CHECK(t1.to_string() == s);

        t1.insert(dt2);
        s = "12345678 1 100.000000 50.000000 10102010 100000.000000 89996014435\n";
        s += "12345680 3 102.000000 52.000000 12122012 100002.000000 89996014437\n";
        CHECK(t1.to_string() == s);

        t1.insert(dt1);
        s = "12345678 1 100.000000 50.000000 10102010 100000.000000 89996014435\n";
        s += "12345680 3 102.000000 52.000000 12122012 100002.000000 89996014437\n";
        s += "12345679 2 101.000000 51.000000 11112011 100001.000000 89996014436\n";
        CHECK(t1.to_string() == s);

        t1.erase(12345680);
        s = "12345678 1 100.000000 50.000000 10102010 100000.000000 89996014435\n";
        s += "12345679 2 101.000000 51.000000 11112011 100001.000000 89996014436\n";
        CHECK(t1.to_string() == s);

        tree::data_t dt3(12345679, tree::value_t(1, 2000, 1000, 20, 12, 2020, 50000, "89996033333"));
        t1.replace(std::get<0>(dt3), std::get<1>(dt3));
        s = "12345678 1 100.000000 50.000000 10102010 100000.000000 89996014435\n";
        s += "12345679 1 2000.000000 1000.000000 20122020 50000.000000 89996033333\n";
        CHECK(t1.to_string() == s);

        t1.clear();
        CHECK(t1.to_string() == "");
        CHECK(t1.empty());
    }
    SECTION("Методы tree")
    {
        tree::data_t dt0(12345678, tree::value_t(1, 100, 50, 10, 10, 2010, 100000, "89996014435"));
        tree::data_t dt1(12345679, tree::value_t(2, 101, 51, 11, 11, 2011, 100001, "89996014436"));
        tree::data_t dt2(12345680, tree::value_t(3, 102, 52, 12, 12, 2012, 100002, "89996014437"));
        tree t1({dt0, dt1, dt2});
        CHECK(t1.to_string() == tree({dt0, dt1, dt2}).to_string());

        tree::data_t dt3(12345681, tree::value_t(1, 100, 50, 10, 10, 2010, 100000, "89996014435"));
        tree::data_t dt4(12345682, tree::value_t(2, 101, 51, 11, 11, 2011, 100001, "89996014436"));
        tree::data_t dt5(12345683, tree::value_t(3, 102, 52, 12, 12, 2012, 100002, "89996014437"));
        tree t2({dt3, dt4, dt5});
        CHECK(t2.to_string() == tree({dt3, dt4, dt5}).to_string());

//        t1.include(t1.get_root());
//        CHECK(t1.to_string() == tree({dt0, dt1, dt2, dt3, dt4, dt5}).to_string());
    }
}
TEST_CASE("Проверка работы методов класса realty", "[realty]")
{
    // -- тестовые методы --
    SECTION("Тестироавние инициализации класса realty")
    {
        realty zero;
        CHECK(zero.toString() == "Контора: \n Дата создания: \n\n Нет Информации");

        std::string s = "Контора: Neil\n Дата создания: 01012001\n12345678 1 100.000000 50.000000 10102010 100000.000000 89996014435\n";
        tree::data_t dt(12345678, tree::value_t(1, 100, 50, 10, 10, 2010, 100000, "89996014435"));

        realty r1("01012001", "Neil", {dt});
        CHECK(r1.toString() == s);

        tree a ({dt});
        realty r2("01012001", "Neil", a);
        CHECK(r2.toString() == s);

        CHECK_THROWS
        ( [&]() {
            realty r3("010120010", "Neil", {dt});
        } () );
        CHECK_THROWS
        ( [&]() {
            realty r4("01012001", "Neil", {dt, dt});
        } () );
        CHECK_THROWS
        ( [&]() {
            realty r5("01012001", "Neil", {tree::data_t(123456789, tree::value_t(1, 100, 50, 10, 10, 2010, 100000, "89996014435"))});
        } () );
    }
    SECTION("Методы realty")
    {
        tree::data_t dt0(12345678, tree::value_t(1, 100, 50, 10, 10, 2010, 100000, "89996014435"));
        tree::data_t dt1(12345679, tree::value_t(2, 101, 51, 11, 11, 2011, 100001, "89996014436"));
        tree::data_t dt2(12345680, tree::value_t(3, 102, 52, 12, 12, 2012, 100002, "89996014437"));
        realty r1("01012001", "Neil", {dt0});

        r1._add_(dt1);
        std::string s = "Контора: Neil\n Дата создания: 01012001\n12345678 1 100.000000 50.000000 10102010 100000.000000 89996014435\n";
        s += "12345679 2 101.000000 51.000000 11112011 100001.000000 89996014436\n";
        CHECK(r1.toString() == s);

        r1._delete_(12345679);
        s = "Контора: Neil\n Дата создания: 01012001\n12345678 1 100.000000 50.000000 10102010 100000.000000 89996014435\n";
        CHECK(r1.toString() == s);

        r1._add_(dt2);
        s = "Контора: Neil\n Дата создания: 01012001\n12345678 1 100.000000 50.000000 10102010 100000.000000 89996014435\n";
        s += "12345680 3 102.000000 52.000000 12122012 100002.000000 89996014437\n";
        CHECK(r1.toString() == s);

        r1._add_(dt1);
        s = "Контора: Neil\n Дата создания: 01012001\n12345678 1 100.000000 50.000000 10102010 100000.000000 89996014435\n";
        s += "12345680 3 102.000000 52.000000 12122012 100002.000000 89996014437\n";
        s += "12345679 2 101.000000 51.000000 11112011 100001.000000 89996014436\n";
        CHECK(r1.toString() == s);

        r1._delete_(12345680);
        s = "Контора: Neil\n Дата создания: 01012001\n12345678 1 100.000000 50.000000 10102010 100000.000000 89996014435\n";
        s += "12345679 2 101.000000 51.000000 11112011 100001.000000 89996014436\n";
        CHECK(r1.toString() == s);

        tree::data_t dt3(12345679, tree::value_t(1, 2000, 1000, 20, 12, 2020, 50000, "89996033333"));
        r1._change_(std::get<0>(dt3), std::get<1>(dt3));
        s = "Контора: Neil\n Дата создания: 01012001\n12345678 1 100.000000 50.000000 10102010 100000.000000 89996014435\n";
        s += "12345679 1 2000.000000 1000.000000 20122020 50000.000000 89996033333\n";
        CHECK(r1.toString() == s);
    }
    SECTION("Методы realty")
    {
        realty zero;
        int id = 12345678;
        realty::data_t dt0(id, tree::value_t(1, 100, 50, 10, 10, 2010, 100000, "89996014435"));
        realty::data_t dt1(id+1, tree::value_t(2, 101, 51, 11, 11, 2011, 100001, "89996014436"));
        realty::data_t dt2(id+2, tree::value_t(3, 102, 52, 12, 12, 2012, 100002, "89996014437"));
        realty::data_t dt3(id+3, tree::value_t(4, 103, 53, 13, 13, 2013, 100003, "89996014438"));

        zero._add_(dt0);
        zero._add_(dt1);
        zero._add_(dt2);
        zero._add_(dt3);

        realty::value_t f = zero.find_id(id);

        CHECK(realty("", "", {tree::data_t(id, zero.find_id(id))}).toString() == realty("", "", {realty::data_t(id, f)}).toString());

        CHECK(zero.get_s() == 4);

        zero._clear();
        CHECK(zero.get_s() == 0);
    }
}
