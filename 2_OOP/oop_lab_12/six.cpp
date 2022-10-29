#include "six.h"
#include "binary.h"
#include "twelve.h"

std::string six::Operator_dymamic_cast(const number &n)
{
    if (const six *prs = dynamic_cast<const six*>(&n))
    {  // правый аргумент типа S; обработка варианта "S-S"
        return "S-S";
    } else if (const twelve *prt = dynamic_cast<const twelve*>(&n))
    { // правый аргумент типа T; обработка варианта "S-T"
        return "S-T";
    } else if (const binary *prb = dynamic_cast<const binary*>(&n))
    { // правый аргумент типа B; обработка варианта "S-B"
        return "S-B";
    } else { throw error(); }
}
std::string six::Operator_typeid(const number &n)
{
    if (typeid(six) == typeid(n))
    {  // правый аргумент типа S; обработка варианта "S-S"
        return "S-S";
    } else if (typeid(twelve) == typeid(n))
    { // правый аргумент типа T; обработка варианта "S-T"
        return "S-T";
    } else if (typeid(binary) == typeid(n))
    { // правый аргумент типа B; обработка варианта "S-B"
        return "S-B";
    } else { throw error(); }
}
std::string six::Operator_virtual(const number &n) const
{
    return n.Operator_virtual(*this);
}
std::string six::Operator_virtual(const binary&) const { return "S-B"; }
std::string six::Operator_virtual(const twelve&) const { return "S-T"; }
std::string six::Operator_virtual(const six&) const { return "S-S"; }
