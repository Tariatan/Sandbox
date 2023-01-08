#pragma once

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