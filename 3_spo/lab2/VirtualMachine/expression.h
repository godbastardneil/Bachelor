
#ifndef CONTEXT_H
#define CONTEXT_H

#include "types.h"

#include <memory>

class Exp
{
public:
    virtual uint32_t value(context&) = 0;
    virtual ~Exp() {};
};

class VarExp: public Exp
{
    std::string val;
public:
    explicit VarExp(std::string name) { val = std::move(name); }
    uint32_t value(context &con) override { return con[val]; }
};

class ConstExp: public Exp
{
    uint32_t val;
public:
    explicit ConstExp(uint32_t value): val(value) {};
    uint32_t value(context &) { return val; }

};

class MathExp: public Exp
{
    Exp *op1;
    Exp *op2;
public:
    MathExp(Exp *oper1, Exp *oper2): op1(oper1), op2(oper2) {}

    uint32_t value(context &) override {}

    uint32_t get_op1(context &con) { return op1->value(con); }
    uint32_t get_op2(context &con) { return op2->value(con); }
};


class Add: public MathExp
{
public:
    Add(Exp *op1, Exp *op2): MathExp(op1, op2) {}
    uint32_t value(context &con) override { return get_op1(con) + get_op2(con); }
};
class Sub: public MathExp
{
public:
    Sub(Exp *op1, Exp *op2): MathExp(op1, op2) {}
    uint32_t value(context &con) override { return get_op1(con) - get_op2(con); }
};
class Mult: public MathExp
{
public:
    Mult(Exp *op1, Exp *op2): MathExp(op1, op2) {}
    uint32_t value(context &con) override { return get_op1(con) * get_op2(con); }
};
class Div: public MathExp
{
public:
    Div(Exp *op1, Exp *op2): MathExp(op1, op2) {}
    uint32_t value(context &con) override { return get_op1(con) / get_op2(con); }
};
class Mod: public MathExp
{
public:
    Mod(Exp *op1, Exp *op2): MathExp(op1, op2) {}
    uint32_t value(context &con) override { return get_op1(con) % get_op2(con); }
};

class UnaryExp: public Exp
{
    Exp *oper;
public:
    UnaryExp(Exp *operand): oper(operand) {};
    uint32_t value(context &con) override { return -oper->value(con); }

};
#endif // CONTEXT_H
