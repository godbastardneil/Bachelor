#ifndef TST_CLIENT_TEST_H
#define TST_CLIENT_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <algorithm>

#include "../../3_spo/lab2/VirtualMachine/types.h"
#include "../../3_spo/lab2/VirtualMachine/client.h"

using namespace testing;

class s_to_int : public ::testing::TestWithParam<std::pair<std::string, int>> {};
INSTANTIATE_TEST_SUITE_P(Instantiation, s_to_int, ::testing::Values(
                             std::make_pair("1234", 1234),
                             std::make_pair("1234.99", 1234),
                             std::make_pair("1", 1),
                             std::make_pair("2", 2),
                             std::make_pair("33.0", 33)
                            ));
class s_to_float : public ::testing::TestWithParam<std::pair<std::string, float>> {};
INSTANTIATE_TEST_SUITE_P(Instantiation, s_to_float, ::testing::Values(
                             std::make_pair("1234", 1234),
                             std::make_pair("1234.99", 1234.99),
                             std::make_pair("1", 1),
                             std::make_pair("2", 2),
                             std::make_pair("33.0", 33)
                            ));
TEST(s_to_int, StrToInteger)
{
    error err;

    EXPECT_EQ(client::StrToInteger(GetParam().first, err), GetParam().second);
}
TEST(s_to_float, StrToReal)
{
    error err;

    EXPECT_EQ(client::StrToReal(GetParam().first, err), GetParam().second);
}

TEST(client_create, client_creator)
{
    context ct;
    error err;
    std::string str = "((1234-5)/5)*4+10";

    client cl(str, ct, err);
    EXPECT_EQ(cl.Execute(), ((1234-5)/5)*4+10);

}

#endif // TST_CLIENT_TEST_H
