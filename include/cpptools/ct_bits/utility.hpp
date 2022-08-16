#pragma once

#include <ctime>
#include <iomanip>
#include <string>

namespace ct
{
/**
 * @brief 获取本地时间日期字符串
 * @param fmt 时间日期格式，参见 https://en.cppreference.com/w/cpp/io/manip/put_time
 * @return 时间日期字符串
 */
inline std::string localTime(const char* fmt = "%Y-%m-%d %H:%M:%S %A", std::time_t* t = nullptr)
{
    std::time_t t_tmp;
    char buf[500];
    if (t == nullptr) {
        t_tmp = time(NULL);
        t     = &t_tmp;
    }
    strftime(buf, 500, fmt, localtime(t));
    return buf;
}
}  // namespace ct
