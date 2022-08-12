#include <gtest/gtest.h>
#include <vector>
#include "cpptools/ct.hpp"

TEST(ct_test, fmt_test)
{
    ct::RingVector<int> vec;

    fmt::print("init vec to size: 4\n");
    vec.init(4);
    fmt::print("[{}] the vec: {}\n", __LINE__, vec.lined_vector());

    int i = 0;
    for (; i < 6; i++) {
        vec.store(i);
        fmt::print("i={}, the vec: {}\n", i, vec.lined_vector());
    }

    fmt::print("init vec to size: 5\n");
    vec.init(5);
    fmt::print("[{}] the vec: {}\n", __LINE__, vec.lined_vector());

    for (; i < 15; i++) {
        vec.store(i);
        fmt::print("i={}, the vec: {}\n", i, vec.lined_vector());
    }
}