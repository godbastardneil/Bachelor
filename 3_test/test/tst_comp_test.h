#ifndef TST_COMP_TEST_H
#define TST_COMP_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <algorithm>

#include "../../3_spo/lab2/VirtualMachine/types.h"
#include "../../3_spo/lab2/VirtualMachine/cpu.h"

using namespace testing;
/*
TEST(comp_test, comp_creator)
{
    CPU comp;
    const uint16_t tmp_ip = 0;

    EXPECT_EQ(comp.PSW.ip, tmp_ip);
}

TEST(comp_test, ip_creator)
{
    CPU comp;
    const uint16_t tmp_ip = 0;

    EXPECT_EQ(comp.PSW.ip, tmp_ip);
}

TEST(comp_test, ip_change)
{
    CPU comp;
    const address beginaddress = 10;
    const address cmdaddress = 12;
    const address endaddress = 12;

    DataType num;
    num.flEl = 15.15;
    comp.memory.push_memory(num, beginaddress);

    DataType cmd1;
    cmd1.anyCommand.cmdAR.opcode = 4;
    cmd1.anyCommand.cmdAR.r1 = 1;
    cmd1.anyCommand.cmdAR.addr = 10;
    comp.memory.push_memory(cmd1, cmdaddress);

    DataType cmde;
    cmde.anyCommand.cmdU.opcode = 0;
    comp.memory.push_memory(cmde, endaddress);
    comp.PSW.ip = cmdaddress;

    comp.run();

    EXPECT_EQ(comp.PSW.ip, endaddress);


    comp.memory.push_memory(cmde, beginaddress);
    comp.PSW.ip = beginaddress;

    comp.run();

    EXPECT_EQ(comp.PSW.ip, beginaddress);
}

TEST(comp_test, ip_end)
{
    CPU comp;
    const address beginaddress = 10;

    DataType cmde;
    cmde.anyCommand.cmdU.opcode = 0;
    comp.memory.push_memory(cmde, beginaddress);
    comp.PSW.ip = beginaddress;

    comp.run();

    EXPECT_EQ(comp.PSW.ip, beginaddress);
}

TEST(comp_test, comp_cmd_mis)
{
    CPU comp;
    const address beginaddress = 10;
    const address endaddress = 11;

    DataType cmdr;
    cmdr.anyCommand.cmdU.opcode = 255;
    comp.memory.push_memory(cmdr, beginaddress);
    comp.PSW.ip = beginaddress;

    DataType cmde;
    cmde.anyCommand.cmdU.opcode = 0;
    comp.memory.push_memory(cmde, endaddress);
    comp.PSW.ip = beginaddress;

    EXPECT_THROW(comp.run(), std::invalid_argument);

}
*/
#endif // TST_COMP_TEST_H
