#include "cpu.h"
#include "command.h"

CPU::CPU()
{   
    /* Остановка выполнения программы */
    com[stop] = nullptr;

    /* Команды ввода-вывода */
    com[iio] = new class Iio();                 // Ввод-вывод целого числа
    com[fio] = new class Fio();                 // Ввод-вывод вещественного числа
    com[regio] = new class REGio();             // Ввод-вывод числа из регистра

    /* Команды загрузки адресного регистра */
    com[load] = new class Load();               // Сохранение адреса из команды в регистр
    com[save] = new class Save();               // Сохранение адреса из адресного регистра в память
    com[swap] = new class Swap();              // Обмен/копирование адресов адресных регистров
    com[mov] = new class Mov();                 // Пересылка из памяти в регистр

    /* Команды арифметики */
    /* Целочисленная арифметики */
    com[addI] = new class AddI();           // Сложение
    com[subI] = new class SubI();           // Вычитание
    com[multI] = new class MultI();         // Умножение
    com[divI] = new class DivI();           // Деление

    /* Дробная арифметики */
    com[addF] = new class AddF();           // Сложение
    com[SubF] = new class SubF();          // Вычитание
    com[multF] = new class MultF();         // Умножение
    com[divF] = new class DivF();           // Деление

    /* Команды адресной арифметики */
    com[addSh] = new class AddA();          // Сложение
    com[subSh] = new class SubA();          // Вычитание
    com[addShNum] = new class AddO();    // Сложение адреса и смещения
    com[subShNum] = new class SubO();    // Вычитание адреса и смещения

    /* Команды переходов */
    com[call] = new class Call();               // Вызов подпрограммы
    com[ret] = new class Return();              // Возврат из подпрограммы

    com[uncondjump] = new class UJump();        // Безусловный переход

    com[zfjump] = new class ZFJump();           // Переход с проверкой флага нуля
    com[NOTzfjump] = new class NOTZFJump();     // Переход с проверкой инвертированного флага нуля
    com[sfjump] = new class SFJump();           // Переход с проверкой флага знака
    com[NOTsfjump] = new class NOTSFJump();     // Переход с проверкой инвертированного знакового флага
}

// функция запуска процессора
void CPU::run()
{
    command = memory.pop_memory(PSW.ip).anyCommand; // загрузка команды процессора
    while(command.cmdU.opcode != stop)
    {
        if (com[command.cmdU.opcode])
        {
            com[command.cmdU.opcode]->operator()(*this);

            ++PSW.ip;

            command = memory.pop_memory(PSW.ip).anyCommand;
        } else { throw std::invalid_argument("not operation code"); }
    }
}
