#include <gtest/gtest.h>
#include <vector>
#include "cpptools/ct_bits/fmt_formatter.hpp"

enum class EnumClass
{
    AA,
    BB,
    CC,
};

TEST(ct_test, fmt_test)
{
    fmt::print("hello world, {}\n", 42);
    std::vector<int> veci{3, 1, 6, 9};
    fmt::print("fmt vector: {}\n", veci);

    fmt::print("fmt enum class: {}\n", std::vector<EnumClass>{EnumClass::BB, EnumClass::CC});
}