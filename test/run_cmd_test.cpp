#include <gtest/gtest.h>

#include <cpptools/ct_bits/run_cmd.hpp>
#include <string>

TEST(ct_test, run_cmd_test)
{
    std::string cmd = "curl -i www.baidu.com";
    auto ret        = ct::run_cmd(cmd);
    std::cout << "[ret begin]" << ret << "[ret end]" << std::endl;
}