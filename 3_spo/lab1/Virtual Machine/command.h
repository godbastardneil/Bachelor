#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <cmath>
#include "cpu.h"


/*класс команд процессора*/
class Command
{
public:
        virtual void operator() (CPU &processor) noexcept = 0;
        virtual ~Command() = 0;
};


/* --------------------------КОМАНДЫ ВВОДА-ВЫВОДА------------------------- */

/*
 * ввод/вывод целого числа по адресу,
 * команда конкретизируется в первом регистре r1
 */

class Iio : public Command //1
{
public:
    virtual void operator()(CPU &processor) noexcept override final;
};

/*
 * ввод/вывод дробного числа,
 * команда конкретизируется в первом регистре r1
 */
class Fio : public Command //2
{
public:
    virtual void operator()(CPU &processor) noexcept override final;
};

/*
 * ввод/вывод целого/дробного числа из регистра
 * в r1: 0 - ввод, 1 - вывод
 * в r2: 0 - целое, 1 - дробное
 * в r3: номер выводимого регистра
 */
class REGio : public Command //3
{
public:
    virtual void operator()(CPU &processor) noexcept override final;
};


/* ---------------------------КОМАНДА ПЕРЕСЫЛКИ--------------------------- */

// команда загрузки адресного регистра
class Load : public Command //4
{
public:
    virtual void operator()(CPU &processor) noexcept override final;
};

// команда сохранения адресного регистра в память (регистр-память)
class Save : public Command //5
{
public:
    virtual void operator()(CPU &processor) noexcept override final;
};

// копирование/обмен адресных регистров
class Swap : public Command //6
{
public:
    virtual void operator()(CPU &processor) noexcept override final;
};

//команда пересылки память-регистр
class Mov : public Command //7
{
public:
    virtual void operator()(CPU &processor) noexcept override final;
};




        /* --------------------------КОМАНДЫ АРИФМЕТИКИ--------------------------- */

        /* Команды длинной арифметики ([r1] = [r2] $ [r3]). Только в памяти.
         *  Адреса в адресных регистрах. В функцию передаются значения (числа) из памяти.
         *  Результат действий записывается в память по адресу, лежащему в первом регистре команды.
         */

        /* **** ЦЕЛОЧИСЛЕННАЯ АРИФМЕТИКА **** */

        class ArithmInt : public Command
        {
            // команда установки флагов
            void setFlags(CPU &processor) noexcept;

            //вычислительная команда
            virtual int32_t calculation(int parametr1, int parametr2) noexcept = 0;

        public:
            virtual void operator()(CPU &processor) noexcept override final;
        };

class AddI : public ArithmInt //8
{
    virtual int calculation(int parametr1, int parametr2) noexcept override final
    {
        return parametr1 + parametr2;
    }
};
class SubI: public ArithmInt //9
{
    virtual int calculation(int parametr1, int parametr2) noexcept override final
    {
        return parametr1 - parametr2;
    }
};
class MultI : public ArithmInt //10
{
    virtual int calculation(int parametr1, int parametr2) noexcept override final
    {
        return parametr1 * parametr2;
    }
};
class DivI : public ArithmInt //11
{
    virtual int calculation(int parametr1, int parametr2) noexcept override final
    {
        return parametr1 / parametr2;
    }
};

        /* **** КОМАНДЫ ДРОБНОЙ АРИФМЕТИКИ **** */

        class ArithmFLong : public Command
        {
            //команда установки флагов
            void setFlags(CPU &processor) noexcept;

            virtual float calculation(float parametr1, float parametr2) noexcept = 0;

        public:
            virtual void operator()(CPU &processor) noexcept override final;
        };
class AddF : public ArithmFLong //12
{
    virtual float calculation(float parametr1, float parametr2) noexcept override final
    {
        return parametr1 + parametr2;
    }
};
class SubF: public ArithmFLong //13
{
    virtual float calculation(float parametr1, float parametr2) noexcept override final
    {
        return parametr1 - parametr2;
    }
};
class MultF : public ArithmFLong //14
{
    virtual float calculation(float parametr1, float parametr2) noexcept override final
    {
        return parametr1 * parametr2;
    }
};
class DivF : public ArithmFLong //15
{
    virtual float calculation(float parametr1, float parametr2) noexcept override final
    {
        return parametr1 / parametr2;
    }
};




        /* --------------------------АДРЕСНАЯ АРИФМЕТИКА-------------------------- */

        /*
         * Команды адресной арифметики. Только в адресных регистрах. Используется
         * формат команды загрузки адресного регистра, в r1 - номер регистра, в поле
         * адреса - адрес
         */
        class ArithmAddress : public Command
        {
            virtual address calculation(address address1, address address2) noexcept = 0;
        public:
            virtual void operator()(CPU &processor) noexcept override final;
        };
class AddA : public ArithmAddress //16
{
    virtual address calculation(address address1, address address2) noexcept override final
    {
        return address1 + address2;
    }
};

class SubA: public ArithmAddress //17
{
    virtual address calculation(address address1, address address2) noexcept override final
    {
        return address1 - address2;
    }
};


        /* ------------------АДРЕСНАЯ АРИФМЕТИКА СО СМЕЩЕНИЕМ--------------------- */

        /*
         * Адресная арифметика со смещением
         * сложение/вычитание адреса в регистре и смещения в команде
         */

        class ArithmOffset : public Command
        {
            virtual address calculation(address addressBase, address replace) noexcept = 0;
        public:
            virtual void operator()(CPU &processor) noexcept override final;
        };
//команда сложение адреса и целого смещения
class AddO : public ArithmOffset //18
{
    virtual address calculation(address addressBase, address replace) noexcept override final
    {
        return addressBase + replace;
    }
};
//вычитание адреса и целого смещения
class SubO : public ArithmOffset //19
{
    virtual address calculation(address addressBase, address replace) noexcept override final
    {
        return addressBase - replace;
    }
};



        /* --------------------------КОМАНДЫ ПЕРЕХОДОВ---------------------------- */

        //класс команд переходов
        class Jump : public Command
        {
            // команда условного перехода

            virtual void jumpTo (CPU &processor) noexcept = 0;

        public:
            void go_to(CPU &processor) noexcept;
            virtual void operator()(CPU &processor) noexcept override final;
            void forwardJ(CPU &processor);
            void forwardIndJ(CPU &processor);
            void forwardIndRegJ (CPU &processor);
            void relativeJ(CPU &processor);
        };


// переход к подпрограмме
class Call : public Jump //20
{
    virtual void jumpTo(CPU &processor) noexcept override;
};
// возврат из подпрограммы
class Return : public Jump //21
{
    virtual void jumpTo(CPU &processor) noexcept override;
};

//команда безусловного перехода (без проверки флагов)
class UJump : public Jump //22
{
    virtual void jumpTo(CPU &processor) noexcept override;
};

//условный переход с проверкой флага нуля
class ZFJump : public Jump //23
{
    virtual void jumpTo(CPU &processor) noexcept override;
};
class NOTZFJump : public Jump //24
{
    virtual void jumpTo(CPU &processor) noexcept override;
};

//условный переход с проверкой знакового флага
class SFJump : public Jump //25
{
    virtual void jumpTo(CPU &processor) noexcept override;
};
class NOTSFJump : public Jump //26
{
    virtual void jumpTo(CPU &processor) noexcept override;
};


#endif // COMMAND_H
