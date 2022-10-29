#ifndef TYPES_H
#define TYPES_H

#include <cinttypes>

using address = uint16_t;    // адрес памяти

using addressReg = uint8_t;  // номер адресного регистра

using MemoryData = uint32_t; // значение из памяти


struct Command_struct // структура команды процессора
{
    uint8_t opcode;         // Код операции
    addressReg r1;          // Первый номер регистра (хранит адрес результата выполненной операции)
    addressReg r2;          // Второй номер регистра
    addressReg r3;          // Третий номер регистра
};


struct Address_struct // структура команды загрузки адресного регистра
{
    uint8_t opcode;         // Код операции
    uint8_t r1;             // Номер загружаемого регистра
    address addr;           // Адрес, который будет загружен в регистр
};


union CommandType // типы доступных команд
{
    Command_struct cmdU;    // Обычная команда
    Address_struct cmdAR;   // Команда загрузки адресного регистра
};


union DataType // используемые типы данных
{
    uint32_t uintEl;        // Целое беззнаковое число
    int32_t intEl;          // Целое знаковое число
    float flEl;             // Знаковое дробное число
    CommandType anyCommand; // Команда любого вида
    address addr;           // Адрес 16 бит
};

#endif // TYPES_H
