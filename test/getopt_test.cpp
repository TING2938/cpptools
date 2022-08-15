#include <gtest/gtest.h>
#include <vector>
#include "cpptools/ct.hpp"

TEST(ct_test, getopt_test)
{
    std::string commandline = "-a 1 -b 1.2 -vec [1, 2, 5]";

    int a    = 0;
    double b = 0.0;
    std::vector<int> vec;

    ct::Getopt getopt(commandline, "test for getopt");
    getopt(a, "-a", false, "params: a");
    getopt(b, "-b", true, "params: b");
    getopt.getArray(vec, "-vec", 0, false, "params: vec");
    getopt.finish();

    EXPECT_EQ(a, 1);
    EXPECT_DOUBLE_EQ(b, 1.2);
    EXPECT_EQ(vec, (std::vector<int>{1, 2, 5}));
}
