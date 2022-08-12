#include <gtest/gtest.h>
#include <vector>
#include "cpptools/ct.hpp"

using namespace ct::opt;

TEST(opt, vec_op_vec)
{
    const std::vector<int> v1 = {1, 2, 4};
    const std::vector<int> v2 = {3, 5, 7};

    ASSERT_EQ(v1 + v2, (std::vector<int>{4, 7, 11}));
    ASSERT_EQ(v1 - v2, (std::vector<int>{-2, -3, -3}));
    ASSERT_EQ(v1 * v2, (std::vector<int>{3, 10, 28}));
    ASSERT_EQ(v2 / v1, (std::vector<int>{3, 2, 1}));
}

TEST(opt, vec_op_eq_vec)
{
    const std::vector<int> v1 = {1, 2, 4};
    const std::vector<int> v2 = {3, 5, 7};

    auto v3 = v1;
    v3 += v2;
    ASSERT_EQ(v3, (std::vector<int>{4, 7, 11}));
    v3 = v1;
    v3 -= v2;
    ASSERT_EQ(v3, (std::vector<int>{-2, -3, -3}));
    v3 = v1;
    v3 *= v2;
    ASSERT_EQ(v3, (std::vector<int>{3, 10, 28}));
    v3 = v2;
    v3 /= v1;
    ASSERT_EQ(v3, (std::vector<int>{3, 2, 1}));
}

TEST(opt, vec_op_scalar)
{
    const std::vector<int> v1 = {1, 2, 4};
    const std::vector<int> v2 = {3, 5, 7};

    int scalar = 2;
    ASSERT_EQ(v1 + scalar, (std::vector<int>{3, 4, 6}));
    ASSERT_EQ(v1 - scalar, (std::vector<int>{-1, 0, 2}));
    ASSERT_EQ(v1 * scalar, (std::vector<int>{2, 4, 8}));
    ASSERT_EQ(v1 / scalar, (std::vector<int>{0, 1, 2}));
}

TEST(opt, vec_op_eq_scalar)
{
    const std::vector<int> v1 = {1, 2, 4};
    const std::vector<int> v2 = {3, 5, 7};

    int scalar = 2;
    auto v3    = v1;
    v3 += scalar;
    ASSERT_EQ(v3, (std::vector<int>{3, 4, 6}));
    v3 = v1;
    v3 -= scalar;
    ASSERT_EQ(v3, (std::vector<int>{-1, 0, 2}));
    v3 = v1;
    v3 *= scalar;
    ASSERT_EQ(v3, (std::vector<int>{2, 4, 8}));
    v3 = v1;
    v3 /= scalar;
    ASSERT_EQ(v3, (std::vector<int>{0, 1, 2}));
}

TEST(stdarray, func)
{
    const std::vector<int> v1 = {2, 4, 1};
    const std::vector<int> v2 = {3, 5, 7};

    ASSERT_EQ(ct::sum(v1), 7);
    ASSERT_DOUBLE_EQ(ct::mean(v1), 7 / 3.0);
    ASSERT_EQ(ct::max(v1), 4);
    ASSERT_EQ(ct::min(v1), 1);
    ASSERT_EQ(ct::argmax(v1), 1);
    ASSERT_EQ(ct::argmin(v1), 2);
    ASSERT_DOUBLE_EQ(ct::stddev(v1), 1.247219128924647);
    ASSERT_EQ(ct::prod(v1), 8);
}

TEST(carray, func)
{
    const int v1[] = {2, 4, 1};
    const int v2[] = {3, 5, 7};

    ASSERT_EQ(ct::sum(v1), 7);
    ASSERT_DOUBLE_EQ(ct::mean(v1), 7 / 3.0);
    ASSERT_EQ(ct::max(v1), 4);
    ASSERT_EQ(ct::min(v1), 1);
    ASSERT_EQ(ct::argmax(v1), 1);
    ASSERT_EQ(ct::argmin(v1), 2);
    ASSERT_DOUBLE_EQ(ct::stddev(v1), 1.247219128924647);
    ASSERT_EQ(ct::prod(v1), 8);
}
