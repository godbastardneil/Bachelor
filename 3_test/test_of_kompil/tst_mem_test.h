#ifndef TST_MEM_TEST_H
#define TST_MEM_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <algorithm>

#include "../../3_spo/lab2/VirtualMachine/types.h"
#include "../../3_spo/lab2/VirtualMachine/memory.h"

using namespace testing;

TEST(mem_test, mem_creator)
{
    Memory mem;

    EXPECT_TRUE(mem.get_memory());
}

TEST(mem_test, push_pop_int)
{
    Memory mem;

    address addr = 100;
    DataType int_data;
    int_data.intEl = -1000;

    mem.push_memory(int_data, addr);


    for (size_t i=0; i<sizeof(int_data); ++i)
    {
        EXPECT_EQ(mem.pop_memory(addr).b[i], int_data.b[i]);
    }
}

TEST(mem_test, push_pop_uint)
{
    Memory mem;

    address addr = 100;
    DataType uint_data;
    uint_data.uintEl = 1000;

    mem.push_memory(uint_data, addr);


    for (size_t i=0; i<sizeof(uint_data); ++i)
    {
        EXPECT_EQ(mem.pop_memory(addr).b[i], uint_data.b[i]);
    }
}

TEST(mem_test, push_pop_fl)
{
    Memory mem;

    address addr = 100;
    DataType fl_data;
    fl_data.flEl = 1000.05;

    mem.push_memory(fl_data, addr);


    for (size_t i=0; i<sizeof(fl_data); ++i)
    {
        EXPECT_EQ(mem.pop_memory(addr).b[i], fl_data.b[i]);
    }
}

TEST(mem_test, push_pop_addr)
{
    Memory mem;

    address addr = 100;
    DataType addr_data;
    addr_data.addr = 1000;

    mem.push_memory(addr_data, addr);


    for (size_t i=0; i<sizeof(addr_data); ++i)
    {
        EXPECT_EQ(mem.pop_memory(addr).b[i], addr_data.b[i]);
    }
}

TEST(mem_test, push_pop_cmdU)
{
    Memory mem;

    address addr = 100;
    DataType cmdU_data;
    cmdU_data.anyCommand.cmdU.opcode = 1;
    cmdU_data.anyCommand.cmdU.r1 = 1;
    cmdU_data.anyCommand.cmdU.r2 = 2;
    cmdU_data.anyCommand.cmdU.r3 = 3;

    mem.push_memory(cmdU_data, addr);


    for (size_t i=0; i<sizeof(cmdU_data); ++i)
    {
        EXPECT_EQ(mem.pop_memory(addr).b[i], cmdU_data.b[i]);
    }
}

TEST(mem_test, push_pop_cmdAR)
{
    Memory mem;

    address addr = 100;
    DataType cmdAR_data;
    cmdAR_data.anyCommand.cmdAR.opcode = 1;
    cmdAR_data.anyCommand.cmdAR.r1 = 1;
    cmdAR_data.anyCommand.cmdAR.addr = 50;

    mem.push_memory(cmdAR_data, addr);


    for (size_t i=0; i<sizeof(cmdAR_data); ++i)
    {
        EXPECT_EQ(mem.pop_memory(addr).b[i], cmdAR_data.b[i]);
    }
}


#endif // TST_MEM_TEST_H
