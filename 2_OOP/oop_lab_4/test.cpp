#include "catch.hpp"
#include "payment.h"

TEST_CASE("Проверка работы методов класса payment", "[payment]") {

    payment p;

    // -- тестовые методы --
    SECTION("Тестироавние класса payment")
    {
        std::string s = "\nФамилия: worker"
                        "\nОклад: 100,00 руб."
                        "\nНадбавка: 0,00 руб." // 0% набдавок
                        "\nНачислено: 100,00 руб."
                        "\nПенсионные отчисления: 1,00 руб." // 1%
                        "\nПодоходный налог: 12,87 руб." // 13%от 99 рублей (начислено - пенсия)
                        "\nУдержано: 13,87 руб." // подоходный + пенсия
                        "\nСумма, выдаваемая на руки: 86,13 руб." // начислено - удержено
                        "\nКоличество рабочих дней: 1"
                        "\nКоличество отработанных дней: 1";
        CHECK(p.toString() == s);
        s = "\nФамилия: FFF"
            "\nОклад: 1000,00 руб."
            "\nНадбавка: 100,00 руб." // 10% набдавок
            "\nНачислено: 1100,00 руб."
            "\nПенсионные отчисления: 11,00 руб." // 1%
            "\nПодоходный налог: 141,57 руб." // 13%от 1089 рублей (начислено - пенсия)
            "\nУдержано: 152,57 руб." // подоходный + пенсия
            "\nСумма, выдаваемая на руки: 947,43 руб." // начислено - удержено
            "\nКоличество рабочих дней: 30"
            "\nКоличество отработанных дней: 30";
        payment two{"FFF", 10, 30, 30, 1000};        CHECK(two.toString() == s);
        CHECK(two != p); // сревнение по окладу
        CHECK(two.toString() != p.toString()); // сравнение по всему

        p.set_sum(1000); // изменение оклада
        CHECK(two == p); // сревнение по окладу
        CHECK(two.toString() != p.toString()); // сравнение по всему

        p.set_allowance(10); // изменение процента
        CHECK(two.get_allowance() == p.get_allowance()); // сревнение по надбавкам
        CHECK(two.toString() != p.toString()); // сравнение по всему, не совпадет из-за разных имен и количества дней
         // сравнение по всему, совпадет из-за одинакового соотношения дней
        CHECK(((p.get_sum() == two.get_sum())
               && (p.get_allowance() == two.get_allowance())
               && (p.get_final_sum() == two.get_final_sum())
               && (p.get_income_tax() == two.get_income_tax())
               && (p.get_accrued_sum() == two.get_accrued_sum())
               && (p.get_witheld_sum() == two.get_witheld_sum())));

        // все так же как и у two только отработал меньше
        payment three{"FFF", 10, 30, 20, 1000};
        CHECK(two.toString() != three.toString()); // сравнение по всему
    }
}
