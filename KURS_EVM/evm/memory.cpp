#include "memory.h"

#include <type_traits>


DataType memory::get_data(const uint16_t &address) const noexcept
{
    DataType dt;
    for (uint8_t i=0; i<4; ++i) { dt.ui8Type[i] = m[address+i]; }
    return dt;
}
CommandType memory::get_cmd(const uint16_t &address) const noexcept
{
    CommandType cmd;
    for (uint8_t i=0; i<3; ++i) { cmd.ui8Type[i] = m[address+i]; }
    return cmd;
}

void memory::push_memory(DataType &dt, const uint16_t &address) noexcept
{
    for (uint8_t i=0; i<4; ++i) { m[address+i] = dt.ui8Type[i]; }
}
void memory::push_memory(CommandType &cmd, const uint16_t &address) noexcept
{
    for (uint8_t i=0; i<3; ++i) { m[address+i] = cmd.ui8Type[i]; }
}
