#include "catch.hpp"
#include "abonent.h"
#include "stack.h"

TEST_CASE("Проверка работы методов класса abonent", "[abonent]")
{
    // -- тестовые методы --
    SECTION("Тестироавние инициализации класса abonent")
    {
        abonent zero;
        CHECK(zero.toString() == "Фамилия оператора: \n Управляющий списоком: \n Дата создания: 1д1м1901г\n\nНет информации");

        std::string s = "Фамилия оператора: Neil\n Управляющий списоком: Ruslan\n Дата создания: 1д1м1999г\n";
        s += "\n Номер договора: 12345678";
        s += "\n Номер телефона: 89996014435";
        s += "\n Дата заключения договора: 1д1м2000г";
        s += "\n Стоимость: 50.000000";
        s += "\n Тариф: 1.000000";
        abonent r1(data_type(1, 1, 1999), "Neil", "Ruslan", {value_type("12345678", "89996014435", data_type(1, 1, 2000), 50, 1)});
        CHECK(r1.toString() == s);
        list a ({value_type("12345678", "89996014435", data_type(1, 1, 2000), 50, 1)});
        abonent r2(data_type(1, 1, 1999), "Neil", "Ruslan", a);
        CHECK(r2.toString() == s);

        CHECK_THROWS
        ( [&]() {
            abonent r4(data_type(1, 1, 1999), "Neil", "Ruslan", {value_type("0123456789", "89996014435", data_type(1, 1, 2000), 50, 1)});
        } () );
        CHECK_THROWS
        ( [&]() {
            abonent r5(data_type(1, 1, 1999), "Neil", "Ruslan", {value_type("12345678", "899960144356", data_type(1, 1, 2000), 50, 1)});
        } () );
    }
   SECTION("Методы abonent")
    {
        value_type v0("12345678", "89996014435", data_type(1, 1, 2000), 50, 1);
        abonent r1(data_type(1, 1, 1999), "Neil", "Ruslan", {v0});
        value_type v1("12345679", "89996014435", data_type(1, 1, 2000), 50, 1);

        r1._add_(v1);
        std::string s = "Фамилия оператора: Neil\n Управляющий списоком: Ruslan\n Дата создания: 1д1м1999г\n";
        s += "\n Номер договора: 12345678";
        s += "\n Номер телефона: 89996014435";
        s += "\n Дата заключения договора: 1д1м2000г";
        s += "\n Стоимость: 50.000000";
        s += "\n Тариф: 1.000000";
        s += "\n Номер договора: 12345679";
        s += "\n Номер телефона: 89996014435";
        s += "\n Дата заключения договора: 1д1м2000г";
        s += "\n Стоимость: 50.000000";
        s += "\n Тариф: 1.000000";

        CHECK(r1.toString() == s);

        r1._delete_(0);
        s = "Фамилия оператора: Neil\n Управляющий списоком: Ruslan\n Дата создания: 1д1м1999г\n";
        s += "\n Номер договора: 12345679";
        s += "\n Номер телефона: 89996014435";
        s += "\n Дата заключения договора: 1д1м2000г";
        s += "\n Стоимость: 50.000000";
        s += "\n Тариф: 1.000000";
        CHECK(r1.toString() == s);

        r1._add_(v0);
        s += "\n Номер договора: 12345678";
        s += "\n Номер телефона: 89996014435";
        s += "\n Дата заключения договора: 1д1м2000г";
        s += "\n Стоимость: 50.000000";
        s += "\n Тариф: 1.000000";
        CHECK(r1.toString() == s);

        value_type v2("12345679", "89996014436", data_type(1, 1, 2020), 100, 0);
        r1._change_(0, v2);
        s = "Фамилия оператора: Neil\n Управляющий списоком: Ruslan\n Дата создания: 1д1м1999г\n";
        s += "\n Номер договора: 12345679";
        s += "\n Номер телефона: 89996014436";
        s += "\n Дата заключения договора: 1д1м2020г";
        s += "\n Стоимость: 100.000000";
        s += "\n Тариф: 0.000000";
        s += "\n Номер договора: 12345678";
        s += "\n Номер телефона: 89996014435";
        s += "\n Дата заключения договора: 1д1м2000г";
        s += "\n Стоимость: 50.000000";
        s += "\n Тариф: 1.000000";
        CHECK(r1.toString() == s);

        CHECK_THROWS
        ( [&]() {
            r1._change_(1, v2);
        } () );
        CHECK_THROWS
        ( [&]() {
            r1._add_(v1);
        } () );
    }
    SECTION("Методы abonent")
    {
        value_type v1("12345678", "89996014436", data_type(1, 2, 2000), 50, 3);
        value_type v2("12345679", "89996014430", data_type(1, 1, 2020), 10, 2);
        value_type v3("12345680", "89996014437", data_type(1, 2, 2020), 150, 1);
        value_type v4("12345681", "89996014431", data_type(1, 1, 2120), 50, 2);

        abonent zero(data_type(1, 1, 1999), "Neil", "Ruslan", {v1, v2/*, v3, v4*/});

        CHECK(list({zero.find_id("12345678")}).to_String() == list({v1}).to_String());

        CHECK(zero.find_tele("89996014450").to_String() == "\nНет информации");
        CHECK(zero.find_tele("89996014437").to_String() == list({v3}).to_String());
        CHECK(zero.find_tarif(3).to_String() == list({v1}).to_String());
        CHECK(zero.find_tarif_less(3).to_String() == list({v2, v3, v4}).to_String());
        CHECK(zero.find_tarif_more(2).to_String() == list({v1}).to_String());
    }
}

TEST_CASE("Проверка работы методов класса stack", "[stack]")
{
    SECTION("Тест создания и присваивания") // -- создание и присваивание --
    {
        stack s1; CHECK(s1.get_size() == 0); CHECK(s1.empty());

        value_type v1("12345678", "89996014436", data_type(1, 2, 2000), 50, 3);
        value_type v2("12345679", "89996014430", data_type(1, 1, 2020), 10, 2);
        value_type v3("12345680", "89996014437", data_type(1, 2, 2020), 150, 1);

        s1.push(v1);
        CHECK(s1.top() == v1);

        s1.pop();
        CHECK(s1.get_size() == 0);

        s1.push(v2);
        CHECK(s1.top() == v2);
    }
}
