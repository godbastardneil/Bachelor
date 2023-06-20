#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <cinttypes>

struct Command_struct // структура команды процессора
{
    uint16_t r1 : 3; // первый номер регистра
    uint16_t r2 : 3; // второй номер регистра
    uint16_t offset : 10; // смещение (константа)
    uint8_t cop : 8; // код операции
} __attribute__((packed));

union DataType
{
    int32_t Int;
    uint32_t UInt;
    float Float;
    uint8_t ui8Type[4];
};

union CommandType
{
    Command_struct cmd;
    uint8_t ui8Type[3];
};

#endif // STRUCTURE_H
