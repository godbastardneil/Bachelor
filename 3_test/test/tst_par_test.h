#ifndef TST_PAR_TEST_H
#define TST_PAR_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <algorithm>

#include "../../3_spo/lab2/VirtualMachine/types.h"
#include "../../3_spo/lab2/VirtualMachine/parser.h"
/*
struct Operator
{
    bool work = true;                   // подлежит ли обработке
    address lc = 0;                     // смещение - счетчик размещения
    std::vector<byte> binary;           // двоичная команда
    uint16_t number = 0;                // номер исходной строки
    std::string label;                  // метка оператора
    std::string code;                   // код операции или директивы
    std::vector<std::string> arguments; // поле аргументов
    std::string comment;                // комметарий (для листинга)
    error err = error::noError;      // номер ошибки
}
*/
using namespace testing;

class parsing_test : public ::testing::TestWithParam<std::vector<std::string>> {};
INSTANTIATE_TEST_SUITE_P(Instantiation, parsing_test, ::testing::Values(
                             std::vector{"org 10			; устанавливаю адрес на 10", "; устанавливаю адрес на 10", ""},
                             std::vector{"v1: int 150 		; (10) = 150", "; (10) = 150", "v1"},
                             std::vector{"v2: int 15  		; (11) = 15", "; (11) = 15", "v2"},
                             std::vector{"v3: int 15		; (12) = 15", "; (12) = 15", "v3"},
                             std::vector{"start: Call 5, 200	; вызов подпрограммы по адресу 200", "; вызов подпрограммы по адресу 200", "start"},
                             std::vector{"REGio 1, 0, 1		; вывод int [1] = 135--------------", "; вывод int [1] = 135--------------", ""},
                             std::vector{"org 200", "", ""},
                             std::vector{"Load 1, v1		; загрузка (10) в [1] = 150", "; загрузка (10) в [1] = 150", ""},
                             std::vector{"Load 2, v2		; загрузка (11) в [2] = 15", "; загрузка (11) в [2] = 15", ""},
                             std::vector{"SubI 1, 1, 2		; [1] = [1] - [2] = 150 - 15 = 150 - 15 = 135", "; [1] = [1] - [2] = 150 - 15 = 150 - 15 = 135", ""},
                             std::vector{"Ret 5, 0		; возврат по адрессу хранящемуся в [5]", "; возврат по адрессу хранящемуся в [5]", ""},
                             std::vector{"end start", "", ""}
                             ));

TEST_P(parsing_test, parsing)
{
    parser par;
    Operator oper;   // разобранный оператор
    std::vector<std::string> param = GetParam();
    std::string str = param[0];

    oper = par.parseOperator(str);

    EXPECT_EQ(oper.comment, param[2]);
    EXPECT_EQ(oper.label, param[3]);
}

#endif // TST_PAR_TEST_H
