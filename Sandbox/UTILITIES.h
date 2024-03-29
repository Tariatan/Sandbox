#pragma once

#include <type_traits>

#define STROF_EXPAND(value)  #value
#define STROF(value)         STROF_EXPAND(value)

#define ISODD(val)           (1U == ((size_t) (val) & 1U))
#define ISEVEN(val)          (0U == ((size_t) (val) & 1U))

template <typename T, int N>
auto array_len(T(&)[N])
{
    return N;
}

// Greatest Common Divider
int gcd(int x, int y)
{
    if (y == 0)
        return x;
    else
        return gcd(y, x % y);
}

// Lowest Common Multiple
int lcm(int x, int y)
{
    return (x * y) / gcd(x, y);
}

enum class EFlags
{
    first,
    second,
    third,
};

template<class T = void>
constexpr auto flags()
{
    return 0;
}

template<class T, class... TOtherValues>
constexpr auto flags(T flag, TOtherValues... otherFlags)
{
    return static_cast<std::underlying_type_t<T>>(flag) | flags(otherFlags...);
}

const auto combinedFlags = flags(EFlags::first, EFlags::second, EFlags::third);