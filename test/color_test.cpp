#include <gtest/gtest.h>
#include <vector>

#include "cpptools/ct_bits/color.hpp"

TEST(ct_test, color_test)
{
    std::cout << ct::color::green << "hello(green)\n"
              << ct::color::red << "world(red)" << ct::color::reset << std::endl;
}
