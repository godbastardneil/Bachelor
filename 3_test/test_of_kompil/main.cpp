#include "tst_comp_test.h"
#include "tst_cmd_test.h"
#include "tst_mem_test.h"

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
