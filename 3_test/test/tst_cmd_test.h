#ifndef TST_CMD_TEST_H
#define TST_CMD_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <algorithm>

#include "../../3_spo/lab2/VirtualMachine/types.h"
#include "../../3_spo/lab2/VirtualMachine/cpu.h"
#include "../../3_spo/lab2/VirtualMachine/command.h"

using namespace testing;
/*
TEST(cmd_test, cmd_load)
{
    CPU comp;
    const address beginaddress = 10;
    const address cmdaddress = 11;
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

    EXPECT_EQ(comp.memory.pop_memory(comp.addressRegister[cmd1.anyCommand.cmdAR.r1]).flEl, num.flEl);
}

TEST(cmd_test, cmd_save)
{
    CPU comp;
    const address beginaddress = 10;
    const address cmd1address = 11;
    const address cmd2address = 12;
    const address endaddress = 13;

    DataType num;
    num.uintEl = 15;
    comp.memory.push_memory(num, beginaddress);

    DataType cmd1;
    cmd1.anyCommand.cmdAR.opcode = 4;
    cmd1.anyCommand.cmdAR.r1 = 1;
    cmd1.anyCommand.cmdAR.addr = 10;
    comp.memory.push_memory(cmd1, cmd1address);

    DataType cmd2;
    cmd2.anyCommand.cmdAR.opcode = 5;
    cmd2.anyCommand.cmdAR.r1 = 1;
    cmd2.anyCommand.cmdAR.addr = 11;
    comp.memory.push_memory(cmd2, cmd2address);

    DataType cmde;
    cmde.anyCommand.cmdU.opcode = 0;
    comp.memory.push_memory(cmde, endaddress);
    comp.PSW.ip = cmd1address;

    comp.run();

    EXPECT_EQ(comp.memory.pop_memory(cmd2.anyCommand.cmdAR.addr).uintEl, cmd1.anyCommand.cmdAR.addr);
}

TEST(cmd_test, cmd_swap)
{
    CPU comp;
    const address beginaddress = 10;
    const address cmd1address = 12;
    const address cmd2address = 13;
    const address cmd3address = 14;
    const address endaddress = 15;

    DataType num1;
    num1.uintEl = 150;
    comp.memory.push_memory(num1, beginaddress);
    DataType num2;
    num2.uintEl = 250;
    comp.memory.push_memory(num2, beginaddress+1);

    DataType cmd1;
    cmd1.anyCommand.cmdAR.opcode = 4;
    cmd1.anyCommand.cmdAR.r1 = 1;
    cmd1.anyCommand.cmdAR.addr = 10;
    comp.memory.push_memory(cmd1, cmd1address);

    DataType cmd2;
    cmd2.anyCommand.cmdAR.opcode = 4;
    cmd2.anyCommand.cmdAR.r1 = 2;
    cmd2.anyCommand.cmdAR.addr = 11;
    comp.memory.push_memory(cmd2, cmd2address);

    DataType cmd3;
    cmd3.anyCommand.cmdAR.opcode = 6;
    cmd3.anyCommand.cmdU.r1 = 1;
    cmd3.anyCommand.cmdU.r2 = cmd1.anyCommand.cmdAR.r1;
    cmd3.anyCommand.cmdU.r3 = cmd2.anyCommand.cmdAR.r1;
    comp.memory.push_memory(cmd3, cmd3address);

    DataType cmde;
    cmde.anyCommand.cmdU.opcode = 0;
    comp.memory.push_memory(cmde, endaddress);
    comp.PSW.ip = cmd1address;

    comp.run();

    EXPECT_EQ(comp.memory.pop_memory(comp.addressRegister[cmd3.anyCommand.cmdU.r2]).uintEl, num2.uintEl);
    EXPECT_EQ(comp.memory.pop_memory(comp.addressRegister[cmd3.anyCommand.cmdU.r3]).uintEl, num1.uintEl);
}

TEST(cmd_test, cmd_move)
{
    CPU comp;
    const address beginaddress = 10;
    const address cmd1address = 11;
    const address cmd2address = 12;
    const address cmd3address = 13;
    const address endaddress = 14;
    const address saveaddress = 100;

    DataType num;
    num.uintEl = 15;
    comp.memory.push_memory(num, beginaddress);

    DataType cmd1;
    cmd1.anyCommand.cmdAR.opcode = 4;
    cmd1.anyCommand.cmdAR.r1 = 1;
    cmd1.anyCommand.cmdAR.addr = beginaddress;
    comp.memory.push_memory(cmd1, cmd1address);

    DataType cmd2;
    cmd2.anyCommand.cmdAR.opcode = 5;
    cmd2.anyCommand.cmdAR.r1 = cmd1.anyCommand.cmdAR.r1;
    cmd2.anyCommand.cmdAR.addr = saveaddress;
    comp.memory.push_memory(cmd2, cmd2address);

    DataType cmd3;
    cmd3.anyCommand.cmdAR.opcode = 7;
    cmd3.anyCommand.cmdAR.r1 = cmd1.anyCommand.cmdAR.r1;
    cmd3.anyCommand.cmdAR.addr = cmd2.anyCommand.cmdAR.addr;
    comp.memory.push_memory(cmd3, cmd3address);

    DataType cmde;
    cmde.anyCommand.cmdU.opcode = 0;
    comp.memory.push_memory(cmde, endaddress);
    comp.PSW.ip = cmd1address;

    comp.run();

    EXPECT_EQ(comp.memory.pop_memory(comp.addressRegister[cmd1.anyCommand.cmdAR.r1]).uintEl, num.uintEl);

}

class cmd_test_int_math : public ::testing::TestWithParam<std::pair<int32_t, int32_t>> {};
class cmd_test_int_math_del : public ::testing::TestWithParam<std::pair<int32_t, int32_t>> {};

class cmd_test_uint_math : public ::testing::TestWithParam<std::pair<int32_t, int32_t>> {};
class cmd_test_uint_math_del : public ::testing::TestWithParam<std::pair<int32_t, int32_t>> {};

class cmd_test_float_math : public ::testing::TestWithParam<std::pair<float, float>> {};

INSTANTIATE_TEST_SUITE_P(Instantiation, cmd_test_int_math, ::testing::Values(
                             std::make_pair(30, -30),
                             std::make_pair(30, -15),
                             std::make_pair(30, 0),
                             std::make_pair(30, 15),
                             std::make_pair(30, 30),
                             std::make_pair(15, -30),
                             std::make_pair(15, -15),
                             std::make_pair(15, 0),
                             std::make_pair(15, 15),
                             std::make_pair(15, 30),
                             std::make_pair(0, -30),
                             std::make_pair(0, -15),
                             std::make_pair(0, 0),
                             std::make_pair(0, 15),
                             std::make_pair(0, 30),
                             std::make_pair(15, -30),
                             std::make_pair(15, -15),
                             std::make_pair(15, 0),
                             std::make_pair(15, 15),
                             std::make_pair(15, 30),
                             std::make_pair(30, -30),
                             std::make_pair(30, -15),
                             std::make_pair(30, 0),
                             std::make_pair(30, 15),
                             std::make_pair(30, 30)
                             ));
INSTANTIATE_TEST_SUITE_P(Instantiation, cmd_test_int_math_del, ::testing::Values(
                             std::make_pair(30, -30),
                             std::make_pair(30, -15),
                             std::make_pair(30, 15),
                             std::make_pair(30, 30),
                             std::make_pair(15, -30),
                             std::make_pair(15, -15),
                             std::make_pair(15, 15),
                             std::make_pair(15, 30),
                             std::make_pair(0, -30),
                             std::make_pair(0, -15),
                             std::make_pair(0, 15),
                             std::make_pair(0, 30),
                             std::make_pair(15, -30),
                             std::make_pair(15, -15),
                             std::make_pair(15, 15),
                             std::make_pair(15, 30),
                             std::make_pair(30, -30),
                             std::make_pair(30, -15),
                             std::make_pair(30, 15),
                             std::make_pair(30, 30)
                             ));


INSTANTIATE_TEST_SUITE_P(Instantiation, cmd_test_float_math, ::testing::Values(
                             std::make_pair(30.3, -30.3),
                             std::make_pair(30.3, -15.15),
                             std::make_pair(30.3, 0.001),
                             std::make_pair(30.3, 15.15),
                             std::make_pair(30.3, 30.3),
                             std::make_pair(15.15, -30.3),
                             std::make_pair(15.15, -15.15),
                             std::make_pair(15.15, 0.001),
                             std::make_pair(15.15, 15.15),
                             std::make_pair(15.15, 30.3),
                             std::make_pair(0.001, -30.3),
                             std::make_pair(0.001, -15.15),
                             std::make_pair(0.001, 0.001),
                             std::make_pair(0.001, 15.15),
                             std::make_pair(0.001, 30.3),
                             std::make_pair(15.15, -30.3),
                             std::make_pair(15.15, -15.15),
                             std::make_pair(15.15, 0.001),
                             std::make_pair(15.15, 15.15),
                             std::make_pair(15.15, 30.3),
                             std::make_pair(30.3, -30.3),
                             std::make_pair(30.3, -15.15),
                             std::make_pair(30.3, 0.001),
                             std::make_pair(30.3, 15.15),
                             std::make_pair(30.3, 30.3)
                             ));

uint8_t do_program (CPU &comp, const uint8_t oper, DataType &num1, DataType &num2)
{

    const address firstaddress = 10;
    const address secondaddress = 11;
    const address cmd1address = 12;
    const address cmd2address = 13;
    const address cmd3address = 14;
    const address pluaddress = 15;
    const address endaddress = 16;

    comp.memory.push_memory(num1, firstaddress);
    comp.memory.push_memory(num2, secondaddress);

    DataType cmd1;
    cmd1.anyCommand.cmdAR.opcode = 4;
    cmd1.anyCommand.cmdAR.r1 = 1;
    cmd1.anyCommand.cmdAR.addr = firstaddress;
    comp.memory.push_memory(cmd1, cmd1address);

    DataType cmd2;
    cmd2.anyCommand.cmdAR.opcode = 4;
    cmd2.anyCommand.cmdAR.r1 = 2;
    cmd2.anyCommand.cmdAR.addr = secondaddress;
    comp.memory.push_memory(cmd2, cmd2address);

    DataType cmd3;
    cmd3.anyCommand.cmdAR.opcode = 4;
    cmd3.anyCommand.cmdAR.r1 = 3;
    cmd3.anyCommand.cmdAR.addr = 100;
    comp.memory.push_memory(cmd3, cmd3address);

    DataType cmd_oper;
    cmd_oper.anyCommand.cmdU.opcode = oper; // operation
    cmd_oper.anyCommand.cmdU.r1 = 3;
    cmd_oper.anyCommand.cmdU.r2 = 1;
    cmd_oper.anyCommand.cmdU.r3 = 2;
    comp.memory.push_memory(cmd_oper, pluaddress);

    DataType cmde;
    cmde.anyCommand.cmdU.opcode = 0;
    comp.memory.push_memory(cmde, endaddress);
    comp.PSW.ip = cmd1address;

    comp.run();

    return cmd_oper.anyCommand.cmdU.r1;
}



TEST_P(cmd_test_int_math, cmd_int_plus)
{
    DataType num1;
    num1.intEl = GetParam().first;
    DataType num2;
    num2.intEl = GetParam().second;

    DataType res;
    res.intEl = num1.intEl + num2.intEl;


    CPU comp;

    EXPECT_EQ(comp.memory.pop_memory(comp.addressRegister[do_program(comp, opcode::addI, num1, num2)]).intEl, res.intEl);
}

TEST_P(cmd_test_int_math, cmd_int_min)
{
    DataType num1;
    num1.intEl = GetParam().first;
    DataType num2;
    num2.intEl = GetParam().second;

    DataType res;
    res.intEl = num1.intEl - num2.intEl;


    CPU comp;

    EXPECT_EQ(comp.memory.pop_memory(comp.addressRegister[do_program(comp, opcode::subI, num1, num2)]).intEl, res.intEl);
}

TEST_P(cmd_test_int_math, cmd_int_umn)
{
    DataType num1;
    num1.intEl = GetParam().first;
    DataType num2;
    num2.intEl = GetParam().second;

    DataType res;
    res.intEl = num1.intEl * num2.intEl;


    CPU comp;

    EXPECT_EQ(comp.memory.pop_memory(comp.addressRegister[do_program(comp, opcode::multI, num1, num2)]).intEl, res.intEl);
}

TEST_P(cmd_test_int_math_del, cmd_int_del)
{
    DataType num1;
    num1.intEl = GetParam().first;
    DataType num2;
    num2.intEl = GetParam().second;

    DataType res;
    res.intEl = num1.intEl / num2.intEl;


    CPU comp;

    EXPECT_EQ(comp.memory.pop_memory(comp.addressRegister[do_program(comp, opcode::divI, num1, num2)]).intEl, res.intEl);
}


TEST_P(cmd_test_float_math, cmd_float_plus)
{
    DataType num1;
    num1.flEl = GetParam().first;
    DataType num2;
    num2.flEl = GetParam().second;

    DataType res;
    res.flEl = num1.flEl + num2.flEl;


    CPU comp;

    EXPECT_EQ(comp.memory.pop_memory(comp.addressRegister[do_program(comp, opcode::addF, num1, num2)]).intEl, res.intEl);
}

TEST_P(cmd_test_float_math, cmd_float_min)
{
    DataType num1;
    num1.flEl = GetParam().first;
    DataType num2;
    num2.flEl = GetParam().second;

    DataType res;
    res.flEl = num1.flEl - num2.flEl;


    CPU comp;

    EXPECT_EQ(comp.memory.pop_memory(comp.addressRegister[do_program(comp, opcode::SubF, num1, num2)]).intEl, res.intEl);
}

TEST_P(cmd_test_float_math, cmd_float_umn)
{
    DataType num1;
    num1.flEl = GetParam().first;
    DataType num2;
    num2.flEl = GetParam().second;

    DataType res;
    res.flEl = num1.flEl * num2.flEl;


    CPU comp;

    EXPECT_EQ(comp.memory.pop_memory(comp.addressRegister[do_program(comp, opcode::multF, num1, num2)]).intEl, res.intEl);
}

TEST_P(cmd_test_float_math, cmd_float_del)
{
    DataType num1;
    num1.flEl = GetParam().first;
    DataType num2;
    num2.flEl = GetParam().second;

    DataType res;
    res.flEl = num1.flEl / num2.flEl;


    CPU comp;

    EXPECT_EQ(comp.memory.pop_memory(comp.addressRegister[do_program(comp, opcode::divF, num1, num2)]).intEl, res.intEl);
}

TEST(cmd_test, cmd_int_plus_throw)
{
    DataType num11;
    num11.intEl = std::numeric_limits<int32_t>::max();
    DataType num12;
    num12.intEl = 1;


    CPU comp1;

    EXPECT_THROW(do_program(comp1, opcode::addI, num11, num12), std::overflow_error);

    DataType num21;
    num21.intEl = std::numeric_limits<int32_t>::min();
    DataType num22;
    num22.intEl = -1;


    CPU comp2;

    EXPECT_THROW(do_program(comp2, opcode::addI, num21, num22), std::overflow_error);
}
TEST(cmd_test, cmd_int_min_throw)
{
    DataType num11;
    num11.intEl = std::numeric_limits<int32_t>::min();
    DataType num12;
    num12.intEl = 1;


    CPU comp1;

    EXPECT_THROW(do_program(comp1, opcode::subI, num11, num12), std::overflow_error);

    DataType num21;
    num21.intEl = std::numeric_limits<int32_t>::max();
    DataType num22;
    num22.intEl = -1;


    CPU comp2;

    EXPECT_THROW(do_program(comp2, opcode::subI, num21, num22), std::overflow_error);
}

TEST(cmd_test, cmd_int_umn_throw)
{
    DataType num11;
    num11.intEl = std::numeric_limits<int32_t>::min();
    DataType num12;
    num12.intEl = -1;


    CPU comp1;

    EXPECT_THROW(do_program(comp1, opcode::multI, num11, num12), std::overflow_error);

    DataType num21;
    num21.intEl = std::numeric_limits<int32_t>::max();
    DataType num22;
    num22.intEl = 2;


    CPU comp2;

    EXPECT_THROW(do_program(comp2, opcode::multI, num21, num22), std::overflow_error);
}

TEST(cmd_test, cmd_int_del_throw)
{
    DataType num11;
    num11.intEl = 30;
    DataType num12;
    num12.intEl = 0;


    CPU comp1;

    EXPECT_THROW(do_program(comp1, opcode::divI, num11, num12), std::invalid_argument);
}

TEST(cmd_test, cmd_float_throw)
{
    DataType num11;
    num11.flEl = 30.30;
    DataType num12;
    num12.flEl = 0;


    CPU comp1;

    EXPECT_THROW(do_program(comp1, opcode::divF, num11, num12), std::invalid_argument);
}


TEST(cmd_test, cmd_for_ujump)
{
    unsigned int newIP = 100;
    CPU comp;

    const address beginaddress = 10;
    const address cmdaddress = 11;
    const address endaddress = 12;

    DataType num;
    num.flEl = 15.15;
    comp.memory.push_memory(num, beginaddress);

    DataType cmd1;
    cmd1.anyCommand.cmdAR.opcode = 22;
    cmd1.anyCommand.cmdAR.r1 = 0;
    cmd1.anyCommand.cmdAR.addr = newIP;
    comp.memory.push_memory(cmd1, cmdaddress);


    DataType cmde;
    cmde.anyCommand.cmdU.opcode = 0;
    comp.memory.push_memory(cmde, endaddress);
    comp.PSW.ip = cmdaddress;

    comp.run();

    EXPECT_EQ(comp.PSW.ip, newIP);
}

TEST(cmd_test, cmd_for_Ind_ujump)
{
    unsigned int newIP = 100;
    CPU comp;

    const address beginaddress = 10;
    const address cmdaddress = 11;
    const address endaddress = 12;

    DataType num;
    num.uintEl = newIP;
    comp.memory.push_memory(num, beginaddress);

    DataType cmd1;
    cmd1.anyCommand.cmdAR.opcode = 22;
    cmd1.anyCommand.cmdAR.r1 = 1;
    cmd1.anyCommand.cmdAR.addr = beginaddress;
    comp.memory.push_memory(cmd1, cmdaddress);


    DataType cmde;
    cmde.anyCommand.cmdU.opcode = 0;
    comp.memory.push_memory(cmde, endaddress);
    comp.PSW.ip = cmdaddress;

    comp.run();

    EXPECT_EQ(comp.PSW.ip, newIP);
}

TEST(cmd_test, cmd_for_IndReg_ujump)
{
    unsigned int newIP = 401;
    CPU comp;

    const address beginaddress = 10;
    const address cmdaddress = 11;
    const address endaddress = 12;

    DataType num;
    num.flEl = 15.15;
    comp.memory.push_memory(num, beginaddress);

    comp.addressRegister[100] = 200;
    comp.addressRegister[101] = 201;

    DataType cmd3;
    cmd3.anyCommand.cmdU.opcode = 22;
    cmd3.anyCommand.cmdU.r1 = 2;
    cmd3.anyCommand.cmdU.r2 = 100;
    cmd3.anyCommand.cmdU.r3 = 101;
    comp.memory.push_memory(cmd3, cmdaddress);


    DataType cmde;
    cmde.anyCommand.cmdU.opcode = 0;
    comp.memory.push_memory(cmde, endaddress);
    comp.PSW.ip = cmdaddress;

    comp.run();

    EXPECT_EQ(comp.PSW.ip, newIP);
}

TEST(cmd_test, cmd_rel_ujump)
{
    unsigned int newIP = 100;
    CPU comp;

    const address beginaddress = 10;
    const address cmdaddress = 11;
    const address endaddress = 12;

    DataType num;
    num.uintEl = 0;
    comp.memory.push_memory(num, beginaddress);

    DataType cmd1;
    cmd1.anyCommand.cmdAR.opcode = 22;
    cmd1.anyCommand.cmdAR.r1 = 3;
    cmd1.anyCommand.cmdAR.addr = newIP;
    comp.memory.push_memory(cmd1, cmdaddress);


    DataType cmde;
    cmde.anyCommand.cmdU.opcode = 0;
    comp.memory.push_memory(cmde, endaddress);
    comp.PSW.ip = cmdaddress;

    comp.run();

    EXPECT_EQ(comp.PSW.ip, cmdaddress+newIP);
}
*/
#endif // TST_CMD_TEST_H
