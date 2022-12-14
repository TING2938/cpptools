/*
 * http://blog.sina.com.cn/s/blog_628ba3e00101jll1.html
 */

#pragma once

#include <iostream>
#include <string>

namespace ct
{
namespace color
{
constexpr auto reset          = "\033[0m";
constexpr auto highlight      = "\033[1m";
constexpr auto red            = "\033[31m";
constexpr auto green          = "\033[32m";
constexpr auto yellow         = "\033[33m";
constexpr auto blue           = "\033[34m";
constexpr auto violet         = "\033[35m";
constexpr auto deepblue       = "\033[36m";
constexpr auto white          = "\033[37m";
constexpr auto underline      = "\033[38m";
constexpr auto dunderline     = "\033[39m";
constexpr auto clearScreen    = "\033[2J";
constexpr auto clearToEndLine = "\033[K";
constexpr auto hideCursor     = "\033[?25l";
constexpr auto showCursor     = "\033[?25h";

inline void cursorUp(int n)
{
    std::cout << "\033[" << n << "A";
}

inline void cursorDown(int n)
{
    std::cout << "\033[" << n << "B";
}

inline void cursorRight(int n)
{
    std::cout << "\033[" << n << "C";
}

inline void cursorLeft(int n)
{
    std::cout << "\033[" << n << "D";
}

inline void cursorPos(int x, int y)
{
    std::cout << "\033[" << y << ";" << x << "H";
}
}  // namespace color
}  // namespace ct
