#ifndef CLIENT_H
#define CLIENT_H

#include "expression.h"

#include <stack>
#include <memory>

class client
{
    std::unique_ptr<Exp> treeExp;
    context ctx;

    priority getPriorityOperatior(char ch) noexcept;
    Exp* getVar(char ch, Exp* op1, Exp* op2);                                   // Возвращает указатель с операцией
    std::vector<std::string> lexAnalyze(const std::string &expression);         // Разбиение строки на лексемы
    std::vector<std::string> getOPN(const std::vector<std::string> &lexStrings);// Получение обратной польской нотации

    void buildExpTree(const std::vector<std::string> &rpnStrExp);               // Построение дерева в _treeExp

public:
    client(std::string str, context &_ctx, error &e);
    uint32_t Execute() { return treeExp->value(ctx); }                          // Вычислить

    static uint32_t StrToInteger(const std::string& value, error& err);
    static float StrToReal(const std::string& value, error& err);
};

#endif // CLIENT_H
