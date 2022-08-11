#include <gtest/gtest.h>
#include <vector>
#include "cpptools/ct.hpp"

#include <Eigen/Dense>
using namespace Eigen;

TEST(ct_test, seq_test)
{
    ArrayXd arr = {{1, 2, 5, 8}};
    fmt::print("arr:\n {}\n", arr);
    fmt::print("arr[{{0, 1, 2}}]:\n {}\n", arr(seq(0, 2)));
    fmt::print("arr[{{0, 1}}]:\n {}\n", arr(seqN(0, 2)));
    fmt::print("arr[{{0, 1, 3}}]:\n {}\n", arr({0, 1, 3}));
}