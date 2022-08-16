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

/**
 * @brief 在printf等函数前调用，使得字符在控制台单行滚动输出
 */
inline void setScrollOutput()
{
#ifdef _WIN32
    std::printf("\r");
#else
    std::printf("\r\033[k");
#endif  // _WIN32
    std::fflush(stdout);
}
}  // namespace ct
