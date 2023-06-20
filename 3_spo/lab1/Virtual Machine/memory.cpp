#include "memory.h"

#include <iostream>

void Memory::push_memory(DataType &usedType, const uint16_t &address)
{
    memory[address] = usedType.uintEl;
}

DataType Memory::pop_memory(const uint16_t &address)
{
    DataType neededData;
    neededData.uintEl = memory[address];
    return neededData;
}

