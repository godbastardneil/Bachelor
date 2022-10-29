#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>

#include "structure.h"

class memory
{
private:
    uint8_t *m; // char *m

public:
    memory() { m = new uint8_t [65536]; }
    ~memory() { delete [] m; }

    memory(const memory &) = delete;
    memory(const memory &&) = delete;
    memory& operator=(const memory &) = delete;
    memory& operator=(const memory &&) = delete;

    // Получение информации по заданному адресу
    DataType get_data (const uint16_t &address) const noexcept;
    CommandType get_cmd (const uint16_t &address) const noexcept;
     // Загрузка информации в память
    void push_memory (DataType &dt, const uint16_t &address) noexcept;
    void push_memory (CommandType &cmd, const uint16_t &address) noexcept;
};

#endif // MEMORY_H
