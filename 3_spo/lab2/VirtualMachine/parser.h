#ifndef PARSER_H
#define PARSER_H

#include "types.h"

#include <sstream>
#include <array>

class parser
{
    using Handler = std::function<state(const std::string&, const size_t, Operator&, std::string&)>;
    std::array<std::array<Handler, TCsize>, Ssize-1> TStates = {};


    static state ToStart(const std::string& str, size_t i, Operator &oper, std::string &tempStr) noexcept;
    static state ToWaitOper(const std::string& str, size_t i, Operator &oper, std::string &tempStr) noexcept;
    static state BlankToArg(const std::string& str, size_t i, Operator &oper, std::string &tempStr) noexcept;


    static state ErrToEnd(const std::string& str, size_t i, Operator &oper, std::string &tempStr) noexcept;
    static state NoColon(const std::string& str, size_t i, Operator &oper, std::string &tempStr) noexcept;

    static state ToEnd(const std::string& str, size_t i, Operator &oper, std::string &tempStr) noexcept;

    static state ToLabelOrOper(const std::string& str, size_t i, Operator &oper, std::string &tempStr) noexcept;
    static state ToLabel(const std::string& str, size_t i, Operator &oper, std::string &tempStr) noexcept;
    static state ToOper(const std::string& str, size_t i, Operator &oper, std::string &tempStr) noexcept;
    static state ToArg(const std::string& str, size_t i, Operator &oper, std::string &tempStr) noexcept;

    static state OperToArg(const std::string& str, size_t i, Operator &oper, std::string &tempStr) noexcept;
    static state OperToEnd(const std::string& str, size_t i, Operator &oper, std::string &tempStr) noexcept;
    static state LabelToWaitOper(const std::string& str, size_t i, Operator &oper, std::string &tempStr) noexcept;
    static state LabelToEnd(const std::string& str, size_t i, Operator &oper, std::string &tempStr) noexcept;
    static state ArgToEnd(const std::string& str, size_t i, Operator &oper, std::string &tempStr) noexcept;


    typechar getSymbolType(char c) const;
    void init_TStates();
public:
    parser();

    Operator parseOperator(std::string& str);
};
;
#endif // PARSER_H
