#include <gtest/gtest.h>
#include <vector>
#include "cpptools/ct.hpp"

using namespace ct::opt;

TEST(opt, vec_op_vec)
{
    const std::vector<int> v1 = {1, 2, 4};
    const std::vector<int> v2 = {3, 5, 7};

    EXPECT_EQ(v1 + v2, (std::vector<int>{4, 7, 11}));
    EXPECT_EQ(v1 - v2, (std::vector<int>{-2, -3, -3}));
    EXPECT_EQ(v1 * v2, (std::vector<int>{3, 10, 28}));
    EXPECT_EQ(v2 / v1, (std::vector<int>{3, 2, 1}));
}

TEST(opt, vec_op_eq_vec)
{
    const std::vector<int> v1 = {1, 2, 4};
    const std::vector<int> v2 = {3, 5, 7};

    auto v3 = v1;
    v3 += v2;
    EXPECT_EQ(v3, (std::vector<int>{4, 7, 11}));
    v3 = v1;
    v3 -= v2;
    EXPECT_EQ(v3, (std::vector<int>{-2, -3, -3}));
    v3 = v1;
    v3 *= v2;
    EXPECT_EQ(v3, (std::vector<int>{3, 10, 28}));
    v3 = v2;
    v3 /= v1;
    EXPECT_EQ(v3, (std::vector<int>{3, 2, 1}));
}

TEST(opt, vec_op_scalar)
{
    const std::vector<int> v1 = {1, 2, 4};
    const std::vector<int> v2 = {3, 5, 7};

    int scalar = 2;
    EXPECT_EQ(v1 + scalar, (std::vector<int>{3, 4, 6}));
    EXPECT_EQ(v1 - scalar, (std::vector<int>{-1, 0, 2}));
    EXPECT_EQ(v1 * scalar, (std::vector<int>{2, 4, 8}));
    EXPECT_EQ(v1 / scalar, (std::vector<int>{0, 1, 2}));
}

TEST(opt, vec_op_eq_scalar)
{
    const std::vector<int> v1 = {1, 2, 4};
    const std::vector<int> v2 = {3, 5, 7};

    int scalar = 2;
    auto v3    = v1;
    v3 += scalar;
    EXPECT_EQ(v3, (std::vector<int>{3, 4, 6}));
    v3 = v1;
    v3 -= scalar;
    EXPECT_EQ(v3, (std::vector<int>{-1, 0, 2}));
    v3 = v1;
    v3 *= scalar;
    EXPECT_EQ(v3, (std::vector<int>{2, 4, 8}));
    v3 = v1;
    v3 /= scalar;
    EXPECT_EQ(v3, (std::vector<int>{0, 1, 2}));
}

TEST(stdarray, func)
{
    const std::vector<int> v1    = {2, 4, 1};
    const std::vector<double> v2 = {3, 5, 7};

    EXPECT_EQ(ct::sum(v1), 7);
    EXPECT_EQ(ct::sum(v2), 15);
    EXPECT_DOUBLE_EQ(ct::mean(v1), 7 / 3.0);
    EXPECT_EQ(ct::max(v1), 4);
    EXPECT_EQ(ct::min(v1), 1);
    EXPECT_EQ(ct::argmax(v1), 1);
    EXPECT_EQ(ct::argmin(v1), 2);
    EXPECT_DOUBLE_EQ(ct::stddev(v1), 1.247219128924647);
    EXPECT_EQ(ct::prod(v1), 8);

    // contain
    EXPECT_TRUE(ct::contain(v1, 4));
    EXPECT_TRUE(ct::contain(v2, 3.0));
    EXPECT_FALSE(ct::contain(v1, 3));
    EXPECT_FALSE(ct::contain(v2, 4.3));
}

TEST(carray, func)
{
    const int v1[] = {2, 4, 1};
    const int v2[] = {3, 5, 7};

    EXPECT_EQ(ct::sum(v1), 7);
    EXPECT_DOUBLE_EQ(ct::mean(v1), 7 / 3.0);
    EXPECT_EQ(ct::max(v1), 4);
    EXPECT_EQ(ct::min(v1), 1);
    EXPECT_EQ(ct::argmax(v1), 1);
    EXPECT_EQ(ct::argmin(v1), 2);
    EXPECT_DOUBLE_EQ(ct::stddev(v1), 1.247219128924647);
    EXPECT_EQ(ct::prod(v1), 8);

    // contain
    EXPECT_TRUE(ct::contain(v1, 4));
    EXPECT_TRUE(ct::contain(v2, 3));
    EXPECT_FALSE(ct::contain(v1, 3));
    EXPECT_FALSE(ct::contain(v2, 4));
}
