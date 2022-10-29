#include "abon.h"

abon::abon(const std::string &I, const std::string &T, const data_type &D, const double &O, const double &P)
{
    if (I.size() > 8) { throw id_8(); }
    if (T.size() > 11) { throw tel_11(); }
    id = I;
    tel = T;
    data = D;
    opl = O;
    tar = P;
}

std::string abon::toString() const noexcept
{
    std::string s = "\n Номер договора: " + id;
    s += "\n Номер телефона: " + tel;
    s += "\n Дата заключения договора: " + std::to_string(std::get<0>(data)) + "д" + std::to_string(std::get<1>(data)) + "м" + std::to_string(std::get<2>(data)) + "г";
    s += "\n Стоимость: " + std::to_string(opl);
    s += "\n Тариф: " + std::to_string(tar);

    return s;
}
