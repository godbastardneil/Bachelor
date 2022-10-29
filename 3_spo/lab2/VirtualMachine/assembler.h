#ifndef ASSEMBLER_H
#define ASSEMBLER_H


#include "types.h"
#include "client.h"
#include "parser.h"

#include <fstream>
#include <map>

class assembler
{
    std::vector<Operator> program; // операторы программы
    std::map<std::string, Handle> THandle; // тоблица операций
    context TNames; // таблица меток

    parser par;

    template <typename T>
    static prefix PrefixByType();

    bool isExistErr();

    void init();

    template <typename T>
    static void defDat(Operator &op, context &ctx);
    template <typename T>
    static void memDat(Operator &op, context &ctx);

    static void HandleFunc(Operator &oper, context &ctx);
    static void AddressFunc(Operator &oper, context &ctx);

    // директивы
    static void equ(Operator &op, context &ctx);
    static void proc(Operator &op, context &ctx);
    static void endp(Operator &op, context &ctx);
    static void org(Operator &op, context &ctx);
    static void end(Operator &op, context &ctx);

    // обработка метки из оператора
    void LabelDo(Operator &oper);

    // первый проход строки
    void firstPass(Operator& oper);

    // второй проход по всей программе
    void secondPass();
public:
    assembler(const std::string &fname);

    void bin(const std::string &fname);
};

#endif // ASSEMBLER_H
