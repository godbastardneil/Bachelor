#include "client.h"
priority client::getPriorityOperatior(char ch) noexcept
{
    switch(ch)
    {
        case -'-':
            return Uno;
        case '*':
        case '%':
        case '/':
            return High;
        case '+':
        case '-':
            return Mid;
        case '(':
        case ')':
            return Low;
        default:
            return NOop;
    }
}

Exp *client::getVar(char ch, Exp *op1, Exp *op2)
{
    switch(ch)
    {
        case '+' :
            return (new Add(op1, op2));
        case '-' :
            return (new Sub(op1, op2));
        case '*' :
            return (new Mult(op1, op2));
        case '/' :
            return (new Div(op1, op2));
        default:
            return (nullptr);
    }
}

uint32_t client::StrToInteger(const std::string &value, error &err)
{
    try {
        if(value[0] == '0')
        {
            if(value[1] == 'x' || value[1] == 'X' )         //16-ая система
            {
                return stoi(value, nullptr, 16);
            } else if(value[1] == 'b' || value[1] == 'B')   //2-ая система
            {
                return stoi(value, nullptr, 2);
            } else if(value[1] == 'o' || value[1] == 'O')   //8-ая система
            {
                return stoi(value, nullptr, 8);
            } else { return stoi(value, nullptr, 10); }     // Всё остальное 10-ая(в т.ч. с лидирующими нулями)
        }
    } catch(...) { err = illInteger; }

    return stoi(value, nullptr, 10);
}

float client::StrToReal(const std::string &value, error &err)
{
    float res{};
    try {
        res = stof(value);
    }  catch(...) { err = illFloat; }

    return res;
}

client::client(std::string str, context &_ctx, error &e): ctx(_ctx)
{
    str.erase(std::remove_if(str.begin(), str.end(), [](int ch) {
        return std::isspace(ch);
    }), str.end());

    try {
        std::vector<std::string> tokens = lexAnalyze(str);

        std::vector<std::string> OPN = getOPN(tokens);

        buildExpTree(OPN);
    } catch(...) { e = illExpression; }
}

std::vector<std::string> client::lexAnalyze(const std::string &expression)
{
    std::vector<std::string> res;
    int i = 0, n = expression.size();
    std::string curLexem;

    while (i < n)
    {
        char curChar = expression[i];
        if (isalpha(curChar) || curChar == '_')
        {
            do {
                curLexem += curChar; ++i; curChar = expression[i];
            } while ((i < n) && (isalpha(curChar) || isdigit(curChar) || (curChar == '_')));
            res.push_back(curLexem); curLexem = ""; //Если идентификатор
        } else if (isdigit(curChar))
        {
            do {
                curLexem += curChar; ++i; curChar = expression[i];
            } while ((i < n) && (isalpha(curChar) || isdigit(curChar)));
            res.push_back(curLexem); curLexem = "";   //Если число
        } else if (getPriorityOperatior(curChar) != NOop || curChar == LC_Symbol[0])
        {
            res.emplace_back(1, curChar); ++i; //Если операция
        } else { /*throw WrongLexException();*/ } //Всё остальное неверная лексема
    }

    return res;
}

std::vector<std::string> client::getOPN(const std::vector<std::string> &lexStrings)
{

    std::vector<std::string> res;
    std::stack<std::string> opStack;
    bool unary = true;

    for (const auto& elem: lexStrings)
    {
        if (elem == "(")
        {
            opStack.push(elem); //Открывающуюся строку в стек
            unary = true;
        } else if (elem == ")")
        {
            while (!opStack.empty() && opStack.top() != "(")
            {
                res.push_back(opStack.top());   //Операции в строку пока не встретили открывающуюся скобку
                opStack.pop();
            }
            if (!opStack.empty())
            {
                opStack.pop();
                unary = false;
            } else { /*throw WrongRPNConvertException();*/ }  //появление непарной скобки также свидетельствует об ошибке
        } else if (elem.size() == 1 && getPriorityOperatior(elem[0]) != NOop) //Если размер строки 1 и этот элемент операция
        {
            std::string op = elem;
            if (unary && op[0] == '-') op[0] = -op[0];
            while (!opStack.empty() && (getPriorityOperatior(opStack.top()[0]) >= getPriorityOperatior(op[0])))
            {
                res.push_back(opStack.top());
                opStack.pop();
            }
            opStack.push(op);
        } else { res.push_back(elem); }    // Число
    }

    while (!opStack.empty())
    {
        res.push_back(opStack.top());
        opStack.pop();
    }

    return res;
}


#include <iostream>

void client::buildExpTree(const std::vector<std::string> &rpnStrExp)
{
    std::stack<Exp*> calcStack;

    for(const auto& elem: rpnStrExp)
    {
        if (elem.size() == 1 && getPriorityOperatior(elem[0]) != NOop)
        {
            // унарная операция
            if (getPriorityOperatior(elem[0]) == Uno)
            {
                if (!calcStack.empty())
                {
                    Exp* op = calcStack.top(); calcStack.pop();
                    Exp* expr = (new UnaryExp(op));

                    calcStack.push(expr);
                } else { /*throw WrongBuildingTreeException();*/ }
            }
            else // бинарная операция
            {
                if (calcStack.size() > 1)
                {
                    Exp* op1 = calcStack.top(); calcStack.pop();
                    Exp* op2 = calcStack.top(); calcStack.pop();

                    Exp* expr = getVar(elem[0], op1, op2);
                    calcStack.push(expr);
                } else { /*throw WrongBuildingTreeException();*/ }
            }

        } else if (isalpha(elem[0]) || elem == LC_Symbol)
        {
            if (ctx.find(elem) != ctx.end())
            {
                calcStack.push(new ConstExp(ctx[elem]));
            } else { /*throw WrongBuildingTreeException();*/ }
        } else if (isdigit(elem[0]))
        {
            error e = error::noError;
            int value = StrToInteger(elem, e); // Парсим число

            if (e == error::noError)
            {
                calcStack.push(new ConstExp(value));
            } else { /*throw WrongBuildingTreeException();*/ }
        }
    }

    if (calcStack.size() == 1)
    {
        std::unique_ptr<Exp> tmp_ptr(calcStack.top());
        treeExp = move(tmp_ptr);
    } else { /*throw WrongBuildingTreeException();*/ }
}
