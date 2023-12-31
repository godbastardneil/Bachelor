﻿#ifndef CPU_H
#define CPU_H

#include "memory.h"


/* коды операций */
enum opcode
{
    /* Команда остановки */
    stop = 0,

    /* Команды ввода-вывода */

    iio = 1,         // Ввод-вывод целого числа (ввод: r1-0, вывод: r1-1)
    fio = 2,         // Ввод-вывод вещественного числа (ввод: r1-0, вывод: r1-1)
    regio = 3,       // Ввод-вывод числа из регистра

    /* Команды загрузки и сохранения адресного регистра */
    load = 4,        // Загрузка адресного регистра
    save = 5,        // Сохранение адресного регистра в память
    swap = 6,        // Обмен значениями адресных регистров (r1-1), копирование адресных регистров (r1-0)
    mov = 7,         // Пересылка память-регистр

    /* Команды целочисленной арифметики */
    addI = 8,        // Сложение
    subI = 9,        // Вычитание
    multI = 10,      // Умножение
    divI = 11,       // Деление

    /* Команды дробной арифметики */
    addF = 12,       // Сложение
    SubF = 13,       // Вычитание
    multF = 14,      // Умножение
    divF = 15,       // Деление

    /* Команды адресной арифметики */
    addSh = 16,      // Сложение адресов
    subSh = 17,      // Вычитание адресов
    addShNum = 18,   // Сложение адреса и смещения
    subShNum = 19,   // Вычитания адреса и смещения

    /* Команды перехода */
    call = 20,       // Переход к подпрограмме
    ret = 21,        // Возврат из подпрограммы

    /* Команда безусловного перехода */
    uncondjump = 22,

    /* Команды условного перехода*/
    zfjump = 23,      // Переход с проверка флага нуля
    NOTzfjump = 24,   // Переход с проверкой инвертированного флага нуля
    sfjump = 25,      // Переход с проверка знакового флага
    NOTsfjump = 26,   // Переход с проверкой инвертированного флага знака
};

class CPU
{
    #pragma pack(1) // Используется для выравнивания битов

    // регистр состояния процессора,
    struct ProgrammStateWord
    {
        uint16_t ip = 0;    // Адрес выполняемой команды
        struct FLAGS
        {
            uint8_t sf : 1; // флаг знака, 1 - отрицательный
            uint8_t zf : 1; // флаг нуля, 1 - ноль
            uint16_t rez : 13;
        } __attribute__((packed)) flags;
    };
    #pragma pack(0)

    // текущая выполняемая команда процессора
    CommandType command;

    // команды процессора, КОП-8 бит => 2^8 команд
    class Command *com[256] = {nullptr};

public:

    // флаги состояния процессора и текущий адрес IP
    ProgrammStateWord PSW;

    //память процессора, состоит из слов по 32 бита, размер адреса - 16 бит
    Memory memory;

    // адресные регистры - 256 шт. по 16 бит
    address addressRegister[256] = {};

    CPU();
    ~CPU() {}

    // Получить КОП
    addressReg get_cmdU_opcode () const noexcept
    { return command.cmdU.opcode; }

    // получить первый регистр команды
    addressReg get_cmd_r1() const noexcept
    { return command.cmdU.r1; }

    // получить второй регистр команды
    addressReg get_cmdU_r2() const noexcept
    { return command.cmdU.r2; }

    // получить третий регистр команды
    addressReg get_cmdU_r3() const noexcept
    { return command.cmdU.r3; }

    /*
     * получение атрибута команды загрузки адресного регистра
     * возвращается значение константного поля команды
     */
    address get_cmdAR_address() const noexcept
    { return command.cmdAR.addr; }

    // сброс флагов и обнуление адресных регистров
    void reset() noexcept
    {
        PSW.flags.zf = 0;
        PSW.flags.sf = 0;
        PSW.ip = 0;
        for(uint16_t i = 0; i < 256; ++i) { addressRegister[i] = 0; }
    }

    // запуска процессора
    void run() noexcept;
};
#endif  //CPU_H
