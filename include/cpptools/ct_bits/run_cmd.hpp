#pragma once

#include <cstdio>
#include <stdexcept>
#include <string>

namespace ct
{
inline std::string run_cmd(const std::string& cmd)
{
    char buffer[1024] = {0};
    FILE* fp;
    if (cmd.empty()) {
        return "";
    }
#ifdef _WIN32
    if ((fp = _popen(cmd.c_str(), "r")) == nullptr) {
#else
    if ((fp = popen(cmd.c_str(), "r")) == nullptr) {
#endif
        throw std::runtime_error("run_cmd() connot open fp");
    }

    std::string ret;
    while (fgets(buffer, sizeof(buffer), fp) != nullptr) {
        ret += buffer;
    }
#ifdef _WIN32
    if (_pclose(fp) == -1) {
#else
    if (pclose(fp) == -1) {
#endif
        throw std::runtime_error("run_cmd() connot close fp");
    }
    return ret;
}
}  // namespace ct
