#pragma once

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <algorithm>
#include <ostream>
#include <type_traits>
#include <vector>

template <typename T>
    requires std::is_enum_v<T>
auto format_as(T t)
{
    return fmt::underlying(t);
}