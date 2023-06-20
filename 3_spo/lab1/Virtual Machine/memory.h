#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"
#include <limits>
#include <memory>
#include <cstddef>

class Memory
{
    static constexpr size_t memsize = std::numeric_limits<address>::max()+1;
    std::unique_ptr<MemoryData[]> memory;


public:
    Memory() { memory = std::make_unique<MemoryData[]>(memsize); }

    // команда загрузки информации type в память по адрессу address
    void push_memory (DataType &type, const address &address);

    // возврат значения по данному адрес уaddress
    DataType pop_memory (const address &address);
};
#endif // MEMORY_H
