#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "structure.h"
#include "memory.h"

enum cop: uint8_t // Команды процессора
{
    // Команда остановки
    stop = 0,

    // Команды вывода - зависит от второго регистра
    io = 1,     // 0 ввод int, 1 ввод uint, 2 ввод float, 3 вывод int, 4 вывод uint, 5 вывод float

    // Команды загрузки и сохранения адресного регистра
    load = 2, // r2 - Загрузка адресного регистра --- 0 ввод адреса, 1 ввода значения
    save = 3, // Сохранение адресного регистра в память
    exchange = 4, // Обмен значениями адресных регистров (r1-1), копирование адресных регистров (r1-0)

    /*r1 = r2 + (r1+bias)*/
    // Команды знаковой арифметики
    iAdd = 5, // Сложение
    iSub = 6, // Вычитание
    iMult = 7, // Умножение
    iDiv = 8, // Деление

    // Команды беззнаковой арифметики
    uiAdd = 9, // Сложение
    uiSub = 10, // Вычитание
    uiMult = 11, // Умножение
    uiDiv = 12, // Деление

    // Команды дробной арифметики
    fAdd = 13, // Сложение
    fSub = 14, // Вычитание
    fMult = 15, // Умножение
    fDiv = 16, // Деление

    // Команда безусловного перехода
    uncondJump = 17, // Вид перехода конкретизируется в поле команды

    // Команды перехода
    zfJump = 18, // Переход с проверка флага нуля на присутствие
    sfJump = 19, // Переход с проверка знакового флага на присутствие
    nzfJump = 20, // Переход с проверка флага нуля на отсутсвие
    nsfJump = 21, // Переход с проверка знакового флага на отсутсвие
    callPr = 22, // Вызов подпрограммы
    returnPr = 23 // Возврат из подпрограммы
};

class processor
{
private:
    struct PSW
    {
        uint16_t ip = 0;
        struct FLAGS
        {
            uint8_t sf : 1; // флаг знака, 1 - отрицательный
            uint8_t zf : 1; // флаг нуля, 1 - ноль
            uint16_t rez : 13;
        } __attribute__((packed)) flags;
    } __attribute__((packed));

    CommandType cmd;

    class command *com[128] {nullptr};

public:
    PSW psw;
    memory ram;
    DataType ron[8];

    processor();
    ~processor();

    processor(const processor &) = delete;
    processor(const processor &&) = delete;
    processor& operator=(const processor &) = delete;
    processor& operator=(const processor &&) = delete;


    uint8_t get_cmd_r1() const noexcept { return cmd.cmd.r1; }  // -- получить номер первого регистра -- //
    uint8_t get_cmd_r2() const noexcept { return cmd.cmd.r2; }  // -- получить номер второго регистра -- //
    uint16_t get_cmd_offset() const noexcept { return cmd.cmd.offset; } // -- получить смещение

    void loadcmd() noexcept
    {
        cmd = ram.get_cmd(psw.ip);
    }
    void run () noexcept;
};

#endif // PROCESSOR_H
