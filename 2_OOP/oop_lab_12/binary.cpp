#include "binary.h"
#include "six.h"
#include "twelve.h"

std::string binary::Operator_dymamic_cast(const number &n)
{
    if (const binary *prb = dynamic_cast<const binary*>(&n))
    { // правый аргумент типа B; обработка варианта "B-B"
        return "B-B";
    } else if (const six *prs = dynamic_cast<const six*>(&n))
    {  // правый аргумент типа S; обработка варианта "B-S"
        return "B-S";
    } else if (const twelve *prt = dynamic_cast<const twelve*>(&n))
    { // правый аргумент типа T; обработка варианта "B-T"
        return "B-T";
    } else  { throw error(); }
}
std::string binary::Operator_typeid(const number &n)
{
    if (typeid(binary) == typeid(n))
    { // правый аргумент типа B; обработка варианта "B-B"
        return "B-B";
    } else if (typeid(six) == typeid(n))
    {  // правый аргумент типа S; обработка варианта "B-S"
        return "B-S";
    } else if (typeid(twelve) == typeid(n))
    { // правый аргумент типа T; обработка варианта "B-T"
        return "B-T";
    }  else { throw error(); }
}
std::string binary::Operator_virtual(const number &n) const
{
    return n.Operator_virtual(*this);
}
std::string binary::Operator_virtual(const twelve&) const { return "B-T"; }
std::string binary::Operator_virtual(const six&) const { return "B-S"; }
std::string binary::Operator_virtual(const binary&) const { return "B-B"; }
