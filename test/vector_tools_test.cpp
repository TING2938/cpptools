#include <gtest/gtest.h>
#include <vector>
#include "cpptools/ct.hpp"

using namespace ct::opt;

TEST(ct_test, vec_op_vec)
{
    const std::vector<int> v1 = {1, 2, 4};
    const std::vector<int> v2 = {3, 5, 7};

    ASSERT_EQ(v1 + v2, (std::vector<int>{4, 7, 11}));
    ASSERT_EQ(v1 - v2, (std::vector<int>{-2, -3, -3}));
    ASSERT_EQ(v1 * v2, (std::vector<int>{3, 10, 28}));
    ASSERT_EQ(v2 / v1, (std::vector<int>{3, 2, 1}));
}

TEST(ct_test, vec_op_eq_vec)
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

TEST(ct_test, vec_op_scalar)
{
    const std::vector<int> v1 = {1, 2, 4};
    const std::vector<int> v2 = {3, 5, 7};

    int scalar = 2;
    ASSERT_EQ(v1 + scalar, (std::vector<int>{3, 4, 6}));
    ASSERT_EQ(v1 - scalar, (std::vector<int>{-1, 0, 2}));
    ASSERT_EQ(v1 * scalar, (std::vector<int>{2, 4, 8}));
    ASSERT_EQ(v1 / scalar, (std::vector<int>{0, 1, 2}));
}

TEST(ct_test, vec_op_eq_scalar)
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
