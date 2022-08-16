#include <cpptools/ct_bits/ns_filter.hpp>
#include "gtest/gtest.h"

TEST(Testfilter, TestEMA)
{
    ct::ns_filter::EMA<double> flt2(0.1);
    double r = flt2.apply(1);
    EXPECT_TRUE(abs(r - 1) < 1e-5);

    r = flt2.apply(2);
    EXPECT_TRUE(abs(r - 1.9) < 1e-5);

    r = flt2.apply(4);
    EXPECT_TRUE(abs(r - 0.19 - 3.6) < 1e-5);

    r = flt2.apply(3);
    EXPECT_TRUE(abs(r - 0.019 - 0.36 - 2.7) < 1e-5);
}

TEST(Testfilter, TestSMA)
{
    ct::ns_filter::SMA<double, 3> flt;
    double r = flt.apply(1);
    EXPECT_TRUE(abs(r - 1) < 1e-5);

    r = flt.apply(2);
    EXPECT_TRUE(abs(r - 1.5) < 1e-5);

    r = flt.apply(4);
    EXPECT_TRUE(abs(r - 7.0 / 3) < 1e-5);

    r = flt.apply(3);
    EXPECT_TRUE(abs(r - 3) < 1e-5);
}

TEST(Testfilter, TestWMA)
{
    ct::ns_filter::WMA<double, 3> flt2;
    double r = flt2.apply(1);
    EXPECT_TRUE(abs(r - 1) < 1e-5);

    r = flt2.apply(2);
    EXPECT_TRUE(abs(r - 5.0 / 3) < 1e-5);

    r = flt2.apply(4);
    EXPECT_TRUE(abs(r - (1 + 4 + 12) * 1.0 / (1 + 2 + 3)) < 1e-5);

    r = flt2.apply(3);
    EXPECT_TRUE(abs(r - (2 + 8 + 9) * 1.0 / (1 + 2 + 3)) < 1e-5);
}
