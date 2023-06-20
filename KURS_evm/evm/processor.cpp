#include "processor.h"
#include "command.h"

processor::processor()
{
    com[stop] = nullptr; // Остановка выполнения программы

    /* Команды ввода-вывода */
    com[io] = new class io;

    /* Команды загрузки адресного регистра */
    com[load] = new class load(); // Сохранение адреса из команды в регистр
    com[Save] = new class Save(); // Сохранение адреса из адресного регистра в память
    // Загрузка в память по адресу, указанному в команде, значения по адресу из адресного регистра
    com[swap] = new class swap(); // Обмен/копирование адресов адресных регистров

    /* Команды арифметики */
    /* знаковая арифметики */
    com[iAdd] = new class iAdd(); // Сложение
    com[iSub] = new class iSub(); // Вычитание
    com[iMult] = new class iMult(); // Умножение
    com[iDiv] = new class iDiv(); // Деление

    /* беззнаковая арифметики */
    com[uiAdd] = new class uiAdd(); // Сложение
    com[uiSub] = new class uiSub(); // Вычитание
    com[uiMult] = new class uiMult(); // Умножение
    com[uiDiv] = new class uiDiv(); // Деление

    /* дробная арифметики */
    com[fAdd] = new class fAdd(); // Сложение
    com[fSub] = new class fSub(); // Вычитание
    com[fMult] = new class fMult(); // Умножение
    com[fDiv] = new class fDiv(); // Деление

    /* Команды переходов */
    com[UJump] = new class UJump(); // Безусловный переход
    com[zfJump] = new class zfJump(); // Переход с проверкой флага нуля
    com[sfJump] = new class sfJump(); // Переход с проверкой флага знака
    com[nzfJump] = new class nzfJump(); // Переход с проверкой флага нуля
    com[nsfJump] = new class nsfJump(); // Переход с проверкой флага знака
    com[callPr] = new class callPr(); // Вызов подпрограммы
    com[returnPr] = new class returnPr(); // Возврат из подпрограммы
}

processor::~processor()
{
    for (command* &tmp: com)
    {
        delete tmp;
        tmp = nullptr;
    }
}

void processor::run() noexcept
{
    loadcmd(); // -- загружаем из памяти команду
    while ((cmd.cmd.cop) != stop)
    {
        com[(cmd.cmd.cop)]->operator()(*this);
        psw.ip += sizeof (cmd);
        loadcmd(); // -- загружаем из памяти команду
    }
}
