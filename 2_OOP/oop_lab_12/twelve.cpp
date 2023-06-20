#include "twelve.h"
#include "binary.h"
#include "six.h"

std::string twelve::Operator_dymamic_cast(const number &n)
{
    if (const twelve *prt = dynamic_cast<const twelve*>(&n))
    { // правый аргумент типа T; обработка варианта "T-T"
        return "T-T";
    } else if (const six *prs = dynamic_cast<const six*>(&n))
    {  // правый аргумент типа S; обработка варианта "T-S"
        return "T-S";
    } else if (const binary *prb = dynamic_cast<const binary*>(&n))
    { // правый аргумент типа B; обработка варианта "T-B"
        return "T-B";
    } else { throw error(); }
}
std::string twelve::Operator_typeid(const number &n)
{
    if (typeid(twelve) == typeid(n))
    { // правый аргумент типа T; обработка варианта "T-T"
        return "T-T";
    } else if (typeid(six) == typeid(n))
    {  // правый аргумент типа S; обработка варианта "T-S"
        return "T-S";
    } else if (typeid(binary) == typeid(n))
    { // правый аргумент типа B; обработка варианта "T-B"
        return "T-B";
    } else { throw error(); }
}
std::string twelve::Operator_virtual(const number &n) const
{
    return n.Operator_virtual(*this);
}
std::string twelve::Operator_virtual(const binary&) const { return "T-B"; }
std::string twelve::Operator_virtual(const six&) const { return "T-S"; }
std::string twelve::Operator_virtual(const twelve&) const { return "T-T"; }
