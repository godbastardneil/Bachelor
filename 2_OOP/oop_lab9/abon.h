#ifndef ABON_H
#define ABON_H

#include <iostream>
#include <tuple>
#include <sstream>
#include <string>

#include "object.h"

using data_type = std::tuple<uint8_t, uint8_t, uint>;

class abon: public object
{
public:
    abon() = default;
    explicit abon(const std::string &I, const std::string &T, const data_type &D, const double &O, const double &P);
    ~abon()
    {
        id.clear();
        tel.clear();
        std::get<0>(data) = std::get<1>(data) = std::get<2>(data) = 0;
        opl = tar = 0;
    }

    std::string get_id() const noexcept { return id; }
    void set_id(const std::string &I) { id = I; }

    std::string get_tel() const noexcept { return tel; }
    void set_tel(const std::string &T) { tel = T; }

    data_type get_data() const noexcept { return data; }
    void set_tel(const data_type &D) { data = D; }

    double get_opl() const noexcept { return opl; }
    void set_opl(const double &O) { opl = O; }

    double get_tar() const noexcept { return tar; }
    void set_tar(const double &P) { opl = P; }

    std::string toString() const noexcept;

private:
    std::string id = "00000000"; // 8 символьный номер договора
    std::string tel= "77777777777"; //  11 символьный номер телефона
    data_type data = data_type(01, 01, 1901); // дата заключение договора
    double opl = 0; // оплата за установку
    double tar = 0; // тариф помесячный

    class zero_size {}; // размер 0

    class id_8 {}; // номер договора из 8 элементов
    class tel_11 {}; // номер из 11 элементов
};

#endif // ABON_H
