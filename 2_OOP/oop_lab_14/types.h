#ifndef TYPES_H
#define TYPES_H

#include <iostream>
#include <tuple>
#include <string>
#include <sstream>

// -- типы --

using data_type = std::tuple<uint8_t, uint8_t, uint>;
using value_type = std::tuple<  std::string  /*0 - номер договора*/,
                                std::string  /*1 - телефон*/,
                                data_type /*2 - дата заключения договора 01 01 2001*/,
                                double    /*3 - оплата за установку*/,
                                double    /*4 - тариф помесячный*/

                             >; //-- ОСНОВНОЙ тип элементов --
using size_type = size_t;
using reference = value_type&;
using const_reference = const value_type&;

#endif // TYPES_H
