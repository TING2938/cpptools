#include <cpptools/ct_bits/ns_filter.hpp>
#include "gtest/gtest.h"

std::unique_ptr<ct::ns_filter::Basic_Filter<double>> flt;

TEST(Testfilter, TestEMA)
{
    flt      = std::make_unique<ct::ns_filter::EMA<double>>(0.1);
    double r = flt->apply(1);
    EXPECT_TRUE(abs(r - 1) < 1e-5);

    r = flt->apply(2);
    EXPECT_TRUE(abs(r - 1.9) < 1e-5);

    flt->apply(4);
    EXPECT_TRUE(abs(flt->last_value() - 0.19 - 3.6) < 1e-5);

    r = flt->apply(3);
    EXPECT_TRUE(abs(r - 0.019 - 0.36 - 2.7) < 1e-5);

    flt->clear();
    r = flt->apply(1);
    EXPECT_TRUE(abs(r - 1) < 1e-5);

    r = flt->apply(2);
    EXPECT_TRUE(abs(r - 1.9) < 1e-5);

    flt->apply(4);
    EXPECT_TRUE(abs(flt->last_value() - 0.19 - 3.6) < 1e-5);
}

TEST(Testfilter, TestSMA)
{
    flt = std::make_unique<ct::ns_filter::SMA<double, 3>>();

    double r = flt->apply(1);
    EXPECT_TRUE(abs(r - 1) < 1e-5);

    r = flt->apply(2);
    EXPECT_TRUE(abs(r - 1.5) < 1e-5);

    flt->apply(4);
    EXPECT_TRUE(abs(flt->last_value() - 7.0 / 3) < 1e-5);

    r = flt->apply(3);
    EXPECT_TRUE(abs(r - 3) < 1e-5);

    flt->clear();
    r = flt->apply(1);
    EXPECT_TRUE(abs(r - 1) < 1e-5);

    r = flt->apply(2);
    EXPECT_TRUE(abs(r - 1.5) < 1e-5);

    flt->apply(4);
    EXPECT_TRUE(abs(flt->last_value() - 7.0 / 3) < 1e-5);
}

TEST(Testfilter, TestWMA)
{
    flt      = std::make_unique<ct::ns_filter::WMA<double, 3>>();
    double r = flt->apply(1);
    EXPECT_TRUE(abs(r - 1) < 1e-5);

    flt->apply(2);
    EXPECT_TRUE(abs(flt->last_value() - 5.0 / 3) < 1e-5);

    r = flt->apply(4);
    EXPECT_TRUE(abs(r - (1 + 4 + 12) * 1.0 / (1 + 2 + 3)) < 1e-5);

    r = flt->apply(3);
    EXPECT_TRUE(abs(r - (2 + 8 + 9) * 1.0 / (1 + 2 + 3)) < 1e-5);

    flt->clear();
    r = flt->apply(1);
    EXPECT_TRUE(abs(r - 1) < 1e-5);

    flt->apply(2);
    EXPECT_TRUE(abs(flt->last_value() - 5.0 / 3) < 1e-5);
}
