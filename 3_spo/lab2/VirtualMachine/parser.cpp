#include "parser.h"

typechar parser::getSymbolType(char c) const
{
    if (std::isspace(c)) { return Blank; }
    if (std::isdigit(c)) { return Digit; }
    if (std::isalpha(c)) { return Id; }
    if (c == ':') { return Colon; }
    if (c == ';') { return Comment; }
    if (c == '_') { return Underline; }
    return Other;
}

void parser::init_TStates()
{
   TStates = {{
        /*                 Пробел      Двоеточие        Коммент     Цифра      Идентификатор   Подчеркивание   Любой     */
        /* Start */       {ToStart,    ErrToEnd,        ToEnd,      ErrToEnd,  ToLabelOrOper,  ToLabel,        ErrToEnd},
        /* LabelOrOper */ {OperToArg,  LabelToWaitOper, OperToEnd,  ToLabel,   ToLabelOrOper,  ToLabel,        ErrToEnd},
        /* Label */       {NoColon,    LabelToWaitOper, NoColon,    ToLabel,   ToLabel,        ToLabel,        ErrToEnd},
        /* WaitOper */    {ToWaitOper, ErrToEnd,        ToEnd,      ErrToEnd,  ToOper,         ErrToEnd,       ErrToEnd},
        /* Oper */        {OperToArg,  ErrToEnd,        OperToEnd,  ErrToEnd,  ToOper,         ErrToEnd,       ErrToEnd},
        /* Arg */         {BlankToArg, ErrToEnd,        ArgToEnd,   ToArg,     ToArg,          ErrToEnd,       ToArg}
    }};

}

parser::parser() { init_TStates(); }

Operator parser::parseOperator(std::string &str)
{
    Operator oper = {};
    std::string tempStr;

    state s = Start;
    size_t i = 0;
    size_t strLen = str.length();
    while( (s != End) && (i < strLen) )
    {
        typechar t = getSymbolType(str[i]);
        s = TStates[s][t](str,i,oper,tempStr);
        ++i;
    }
    if (s != End)
    {
        // проверка состояния при выходе (если закончилась строка до End)
        if (s == CodeOperations || s == LabelOrOper)
        {
            oper.code = tempStr;
        } else if (s == Arg)
        {
            oper.arguments.push_back(tempStr);
        } else if (s == Label)
        {
            oper.err = error::noColon;
            oper.work = false;  // обрабатывать не требуется
            oper.comment = str;	// вся строка в коммент
        }
    }
    return oper;

}

// переход без действия
state parser::ToStart(const std::string&, size_t, Operator &, std::string &) noexcept
{
    return Start;
}
state parser::ToWaitOper(const std::string&, size_t, Operator&, std::string&) noexcept
{
    return WaitingOperations;
}
state parser::BlankToArg(const std::string&, size_t, Operator&, std::string&) noexcept
{
    return Arg;
}

state parser::ErrToEnd(const std::string& str, size_t i, Operator& oper, std::string&) noexcept
{
    oper.err = illSymbol;
    oper.work = false;
    oper.comment = str.substr(i);
    return End;
}
state parser::NoColon(const std::string& str, size_t i, Operator& oper, std::string&) noexcept
{
    oper.err = noColon;
    oper.work = false;
    oper.comment = str.substr(i);
    return End;
}
// переход в конец из-за комментария в событиях Wait
state parser::ToEnd(const std::string& str, size_t i, Operator& oper, std::string&) noexcept
{
    oper.work = false;
    oper.comment = str.substr(i);
    return End;
}
// переходы с добавлением символа во временную строку
state parser::ToLabelOrOper(const std::string& str, size_t i, Operator&, std::string &tempStr) noexcept
{
    tempStr += str[i];
    return LabelOrOper;
}

state parser::ToLabel(const std::string& str, size_t i, Operator&, std::string &tempStr) noexcept
{
    tempStr += str[i];
    return Label;
}

state parser::ToOper(const std::string& str, size_t i, Operator&, std::string &tempStr) noexcept
{
    tempStr += str[i];
    return CodeOperations;
}

state parser::ToArg(const std::string& str, size_t i, Operator&, std::string &tempStr) noexcept
{
    tempStr += str[i];
    return Arg;
}
// переходы с сохранением строки в оператор
state parser::OperToArg(const std::string&, size_t, Operator& oper, std::string &tempStr) noexcept
{
    oper.code = tempStr;
    tempStr.clear();
    return Arg;
}

state parser::OperToEnd(const std::string& str, size_t i, Operator& oper, std::string &tempStr) noexcept
{
    oper.code = tempStr;
    oper.comment = str.substr(i);
    tempStr.clear();
    return End;
}

state parser::LabelToWaitOper(const std::string&, size_t, Operator& oper, std::string &tempStr) noexcept
{
    oper.label = tempStr;
    tempStr.clear();
    return WaitingOperations;
}

state parser::LabelToEnd(const std::string& str, size_t i, Operator& oper, std::string &tempStr) noexcept
{
    oper.label = tempStr;
    oper.comment = str.substr(i);
    tempStr.clear();
    return End;
}

state parser::ArgToEnd(const std::string& str, size_t i, Operator& oper, std::string &tempStr) noexcept
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(tempStr);
    while (std::getline(tokenStream, token, ',')) { tokens.push_back(token); }

    oper.arguments = tokens;
    oper.comment = str.substr(i);
    tempStr.clear();
    return End;
}
