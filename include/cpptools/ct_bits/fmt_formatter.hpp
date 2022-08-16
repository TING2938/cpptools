#pragma once

#include <fmt/format.h>
#include <fmt/ostream.h>
#include <ostream>
#include <type_traits>
#include <vector>

template <typename T>
inline typename std::enable_if<std::is_enum<T>::value, std::ostream&>::type operator<<(std::ostream& os, const T& value)
{
    return os << static_cast<typename std::underlying_type<T>::type>(value);
}

namespace fmt
{
template <typename T>
struct formatter<std::vector<T>>
{
    std::string f;
    auto parse(format_parse_context& ctx) -> decltype(ctx.begin())
    {
        auto beg = ctx.begin(), end = ctx.end();
        auto it = std::find(beg, end, '}');
        f.assign(ctx.begin(), it);
        if (f.empty())
            f = "{}";
        else
            f = "{:" + f + "}";
        return it;
    }

    template <typename FormatContext>
    auto format(const std::vector<T>& vec, FormatContext& ctx) -> decltype(ctx.out())
    {
        fmt::format_to(ctx.out(), "{{");
        if (!vec.empty()) {
            fmt::format_to(ctx.out(), f, vec[0]);
        }
        for (int i = 1; i < vec.size(); i++) {
            fmt::format_to(ctx.out(), ", ");
            fmt::format_to(ctx.out(), f, vec[i]);
        }
        return fmt::format_to(ctx.out(), "}}");
    }
};
}  // namespace fmt