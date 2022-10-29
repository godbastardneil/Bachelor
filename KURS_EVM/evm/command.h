#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <cmath>
#include "processor.h"

class command
{
public:
    virtual void operator() (processor &cpu) noexcept = 0;
    virtual ~command() {}
};


/* ------------------------ Команда ввода-вывода --------------------------- */

class io : public command
{
public:
    virtual void operator()(processor &processor) noexcept override final;
};

/* ----------------- Команды управления адресным регистром ----------------- */
// Загрузка адресного регистра
class load : public command
{
public:
    virtual void operator()(processor &processor) noexcept override final;
};

// Сохранения адреса из адресного регистра в память
class save : public command
{
public:
    virtual void operator()(processor &processor) noexcept override final;
};

// Обмен значениями между адресными регистрами
class exchange : public command
{
public:
    virtual void operator()(processor &processor) noexcept override final;
};

/* ------------------------- Арифметические команды ------------------------ */

/* --------------------- Команды знаковой целой арифметики ---------- */
        class iMath : public command
        {
            // Команда установки флагов
            void setFlags(processor &processor) noexcept;

            // Вычислительная команда
            virtual int calculation(const int &f, const int &s) noexcept = 0;
        public:
            virtual void operator()(processor &processor) noexcept override final;
        };

// Команда сложения
class iAdd : public iMath
{
    virtual int calculation(const int &f, const int &s) noexcept override final { return f + s; }
};

// Команда вычитания
class iSub: public iMath
{
    virtual int calculation(const int &f, const int &s) noexcept override final { return f - s; }
};

// Команда умножения
class iMult : public iMath
{
    virtual int calculation(const int &f, const int &s) noexcept override final { return f * s; }
};

// Команда деления
class iDiv : public iMath
{
    virtual int calculation(const int &f, const int &s) noexcept override final { return f / s; }
};

/* --------------------- Команды беззнаковой целой арифметики ---------- */
        class uiMath : public command
        {
            // Команда установки флагов
            void setFlags(processor &processor) noexcept;

            // Вычислительная команда
            virtual unsigned int calculation(const unsigned int &f, const unsigned int &s) noexcept = 0;
        public:
            virtual void operator()(processor &processor) noexcept override final;
        };

// Команда сложения
class uiAdd : public uiMath
{
virtual unsigned int calculation(const unsigned int &f, const unsigned int &s) noexcept override final { return f + s; }
};

// Команда вычитания
class uiSub: public uiMath
{
virtual unsigned int calculation(const unsigned int &f, const unsigned int &s) noexcept override final { return f - s; }
};

// Команда умножения
class uiMult : public uiMath
{
virtual unsigned int calculation(const unsigned int &f, const unsigned int &s) noexcept override final { return f * s; }
};

// Команда деления
class uiDiv : public uiMath
{
virtual unsigned int calculation(const unsigned int &f, const unsigned int &s) noexcept override final { return f / s; }
};

/* --------------------- Команды дробной арифметики ----------------- */
        class fMath : public command
        {
            // Команда установки флагов
            void setFlags(processor &processor) noexcept;

            // Вычислительная команда
            virtual float calculation(const float &f, const float &s) noexcept = 0;
        public:
            virtual void operator()(processor &processor) noexcept override final;
        };

// Команда сложения
class fAdd : public fMath
{
    virtual float calculation(const float &f, const float &s) noexcept override final { return f + s; }
};

// Команда вычитания
class fSub : public fMath
{
    virtual float calculation(const float &f, const float &s) noexcept override final { return f - s; }
};

// Команда умножения
class fMult : public fMath
{
    virtual float calculation(const float &f, const float &s) noexcept override final { return f * s; }
};

// Команда деления
class fDiv : public fMath
{
    virtual float calculation(const float &f, const float &s) noexcept override final { return f / s; }
};


/* --------------------------- Команды  переходов ---------------------------- */

        class Jump : public command
        {
            virtual void jumpTo(processor &processor) noexcept = 0;
        public:
            void go_to(processor &processor) noexcept;
            virtual void operator()(processor &processor) noexcept override final;
        };

// Безусловный переход
class uncondJump : public Jump
{
    virtual void jumpTo(processor &processor) noexcept override;
};

// Условный переход с проверкой флага нуля на присутствие
class zfJump : public Jump
{
    virtual void jumpTo(processor &processor) noexcept override;
};

// Условный переход с проверкой знакового флага на присутствие
class sfJump : public Jump
{
    virtual void jumpTo(processor &processor) noexcept override;
};

// Условный переход с проверкой флага нуля на отсутсвие
class nzfJump : public Jump
{
    virtual void jumpTo(processor &processor) noexcept override;
};

// Условный переход с проверкой знакового флага на отсутсвие
class nsfJump : public Jump
{
    virtual void jumpTo(processor &processor) noexcept override;
};

// Команда перехода к подпрограмме
class callPr : public Jump
{
    virtual void jumpTo(processor &processor) noexcept override;
};

// Команда возврата из подпрограммы
class returnPr : public Jump
{
    virtual void jumpTo(processor &processor) noexcept override;
};

#endif // COMMAND_H
