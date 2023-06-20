#include "assembler.h"

#include <iostream>


template<typename T>
prefix assembler::PrefixByType()
{
    if(typeid(T) == typeid(int))
    {
        return prefix::Integer;
    } else { return prefix::Real; }
}

bool assembler::isExistErr()
{
    for (const Operator &var: program)
    {
        if(var.err != noError) { return true; }
    }
    return false;
}
assembler::assembler(const std::string &fname)
{
    init();                 //Иницциализация таблиц
    //Ассемблерный код
    std::ifstream file(fname);

    uint16_t line = 0;

    std::string str; // читаемая строка программы
    Operator oper;   // разобранный оператор

    while (getline(file, str) && oper.code != "end")
    {
        if (!str.empty())
        {
            oper = par.parseOperator(str);
            oper.number = ++line;
            firstPass(oper);
            program.push_back(oper);
        }
    }
    if (oper.code != "end")
    {
        oper = {};
        oper.work = false;
        oper.err = noEnd;
        oper.number = ++line;
        program.push_back(oper);
    }
    file.close();
    if (!isExistErr()) { secondPass(); }
}

void assembler::init()
{
    TNames[LC_Symbol] = 0;

    THandle["int"] = {defDat<int>, nop, 1};
    THandle["float"] = {defDat<float>, nop, 1};
    THandle["memint"] = {memDat<int>, nop, 1};
    THandle["memfloat"] = {memDat<float>, nop, 1};

    THandle["equ"] = {equ, nop, 1, false};
    THandle["proc"] = {proc, nop, 1};
    THandle["endp"] = {endp, nop, 1, false};
    THandle["org"] = {org, nop, 1, false};
    THandle["end"] = {end, nop, 1, false};

    THandle["Iio"] = {AddressFunc, iio, 2}; // 2
    THandle["Fio"] = {AddressFunc, fio, 2}; // 2
    THandle["REGio"] = {HandleFunc, regio, 3}; // 3

    THandle["Load"] = {AddressFunc, load, 2}; // 2
    THandle["Save"] = {AddressFunc, subI, 2}; // 2
    THandle["Swap"] = {HandleFunc, swap, 3}; // 3
    THandle["Mov"] = {AddressFunc, mov, 2}; // 2

    THandle["AddI"] = {HandleFunc, addI, 3}; // 3
    THandle["SubI"] = {HandleFunc, subI, 3}; // 3
    THandle["MultI"] = {HandleFunc, multI, 3}; // 3
    THandle["DivI"] = {HandleFunc, divI, 3}; // 3

    THandle["AddF"] = {HandleFunc, addF, 3}; // 3
    THandle["SubF"] = {HandleFunc, SubF, 3}; // 3
    THandle["MultF"] = {HandleFunc, multF, 3}; // 3
    THandle["DivF"] = {HandleFunc, divF, 3}; // 3

    THandle["AddA"] = {HandleFunc, addF, 3}; // 3
    THandle["SubA"] = {HandleFunc, SubF, 3}; // 3
    THandle["AddO"] = {HandleFunc, multF, 3}; // 3
    THandle["SubO"] = {HandleFunc, divF, 3}; // 3

    THandle["Call"] = {AddressFunc, call, 2}; // 2
    THandle["Ret"] = {AddressFunc, ret, 2}; // 2
    THandle["UJump"] = {AddressFunc, uncondjump, 2}; // 2
    THandle["ZFJump"] = {AddressFunc, zfjump, 2}; // 2
    THandle["NOTZFJump"] = {AddressFunc, NOTzfjump, 2}; // 2
    THandle["SFJump"] = {AddressFunc, sfjump, 2}; // 2
    THandle["NOTSFJump"] = {AddressFunc, NOTsfjump, 2}; // 2
}

void assembler::firstPass(Operator &oper)
{
    oper.lc = TNames[LC_Symbol];
    if (!oper.code.empty())
    {
        const auto cmd = THandle.find(oper.code);
        if (cmd != THandle.end())
        {
            const Handle t = cmd->second;
            if (t.work) { LabelDo(oper); }

            if (t.code == nop) // директива
            {
                oper.work = false;
                t.func(oper, TNames);
            } else { ++TNames[LC_Symbol]; } // команда
        } else
        {
            oper.err = illOperation;
            oper.work = false;
        }

    } else if (!oper.label.empty()) { LabelDo(oper); }
}

void assembler::LabelDo(Operator &oper)
{
    const auto label = oper.label;
    if (!label.empty())
    {
        if (TNames.find(label) == TNames.end())
        {
            auto lowerLabel = label;

            if (THandle.find(lowerLabel) == THandle.end())
            {
                TNames[label] = TNames[LC_Symbol];
            } else
            {
                oper.err = illLabel;
                oper.work = false;
            }
        } else
        {
            oper.err = reuseLabel;
            oper.work = false;
        }
    }
}

void assembler::HandleFunc(Operator &op, context &ctx)
{
    if (op.arguments.size())
    {
        for (const auto &var: op.arguments)
        {
            error err = noError;
            client calc(var, ctx, err);

            DataType d{};
            if (err == noError)
            {
                d.uintEl = calc.Execute();

                for (size_t i=0; i<sizeof(uint8_t); ++i) { op.binary.push_back(d.b[i]); }
            } else { op.err = illExpression; }
        }
    } else { op.err = illCountArgument; }
}

void assembler::AddressFunc(Operator &op, context &ctx)
{
    if (op.arguments.size())
    {
        for (size_t i=0; i<op.arguments.size()-1; ++i)
        {
            error err = noError;
            client calc(op.arguments[i], ctx, err);

            DataType d{};
            if (err == noError)
            {
                d.uintEl = calc.Execute();

                for (size_t i=0; i<sizeof(uint8_t); ++i) { op.binary.push_back(d.b[i]); }
            } else { op.err = illExpression; }
        }
        error err = noError;
        client calc(op.arguments[op.arguments.size()-1], ctx, err);

        DataType d{};
        if (err == noError)
        {
            d.uintEl = calc.Execute();

            for (size_t i=0; i<sizeof(uint16_t); ++i) { op.binary.push_back(d.b[i]); }
        } else { op.err = illExpression; }
    } else { op.err = illCountArgument; }
}

void assembler::equ(Operator &op, context &ctx)
{
    if(!op.label.empty())
    {
        error isError = noError;
        client mcLient(op.arguments[0], ctx, isError);
        if (isError == error::noError)
        {
            ctx[op.label] =  mcLient.Execute();
        } else { op.err = isError; }
    } else { op.err = noLabel; }
}

void assembler::proc(Operator &op, context &)
{
    if (op.label.empty())
    {
        op.err = noLabel;
    } else if (!op.arguments.empty()) { op.err = illCountArgument; }
}

void assembler::endp(Operator &op, context &ctx)
{
    if (op.arguments.size() != 1)
    {
        op.err = illCountArgument;
    } else if (ctx.find(op.arguments[0]) == ctx.end()) { op.err = undLabel; }
}

void assembler::org(Operator &op, context &ctx)
{
    if (op.arguments.size() == 1)
    {
        // вычисляем число из аргумента операции, число ограничиваем размером памяти ВМ
        // так как org устанавливает LC
        error isError = noError;
        client mcLient(op.arguments[0], ctx, isError);

        if (isError == noError)
        {
            DataType d;
            d.uintEl = mcLient.Execute();
            op.binary.push_back(LoadAddress);

            // транслируем адрес
            for (size_t i=0; i<sizeof(address); ++i) { op.binary.push_back(d.b[i]); }

            // меняем счетик размещения
            ctx[LC_Symbol] = d.addr;
        }
    } else { op.err = illCountArgument; }
}

void assembler::end(Operator &op, context &ctx)
{
    if (op.arguments.size() == 1)
    {
        error isError = noError;
        client mcLient(op.arguments[0], ctx, isError);

        if (isError == noError)
        {
            DataType d;
            d.uintEl = mcLient.Execute();
            op.binary.push_back(EndPr);

            // транслируем адрес
            for (size_t i=0; i<sizeof(address); ++i) { op.binary.push_back(d.b[i]); }

            // меняем счетик размещения
            ctx[LC_Symbol] += 1;
        }
    } else { op.err = illCountArgument; }
}

template<typename T>
void assembler::defDat(Operator &op, context &ctx)
{
    auto prefix = PrefixByType<T>();
    error err;
    for (const auto& el: op.arguments)
    {
        err = noError;
        DataType d{};
        if (prefix == prefix::Real)
        {
            std::string str = el;
            float current = client::StrToReal(str, err);
            d.flEl = current;
        } else
        {
            client calc(el, ctx, err);
            d.intEl = calc.Execute();
        }

        if (err == noError)
        {
            op.binary.push_back(prefix);
            for (size_t i=0; i<sizeof(T); ++i) { op.binary.push_back(d.b[i]); }
        } else { op.err = err; }
        ctx[LC_Symbol] += 1;
    }
}


template<typename T>
void assembler::memDat(Operator &op, context &ctx)
{
    if (!op.arguments.empty())
    {
        error expression = noError;
        client calc(op.arguments[0], ctx, expression);
        uint32_t counter = calc.Execute();
        if (expression == noError)
        {
            prefix prefix = PrefixByType<T>();
            for (uint32_t i=0; i<counter; ++i)
            {
                op.binary.push_back(prefix);
                for (size_t j=0; j<sizeof(T); ++j) { op.binary.push_back(0); }
            }
        } else { op.err = expression; }
        ctx[LC_Symbol] += 1;
    } else { op.err = illCountArgument; }
}

void assembler::secondPass()
{
    for (auto& oper: program)
    {
        if (oper.work)    //Директивы и пр. не обрабатываем
        {
            //Сборка команды
            Handle cmd = THandle[oper.code];
            TNames[LC_Symbol] = oper.lc;

            if (cmd.arg_size == 3)
            {
                oper.binary.push_back(prefix::Cmd);
            } else { oper.binary.push_back(prefix::Initreg); }
            oper.binary.push_back(cmd.code);

            cmd.func(oper, TNames);
            oper.work = false;
        }
    }
}


void assembler::bin(const std::string &fname)
{
    std::ofstream file(fname, std::ios::binary);
    if (file)
    {
        for (const auto &oper: program)
        {
            for (size_t i=0; i<oper.binary.size(); ++i)
            {
                file << oper.binary[i];
            }
        }
    }
    file.close();
}
