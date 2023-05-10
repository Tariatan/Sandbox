#pragma once

#include <iostream>
#include <bitset>

template<class T>
void showBits(const T x)
{
    constexpr int bits_count = CHAR_BIT * sizeof(x);

    std::cout << "0b";
    for (int i = bits_count - 1; i >= 0; --i)
    {
        std::cout << bool(x & (1U << i)) ? '1' : '0';
        if ((i != 0) && (i % 4) == 0)
        {
            std::cout << '\'';
        }
    }

    std::cout << std::endl;

    return;
    // or
    std::bitset<bits_count> bs(x);
    std::cout << "0b" << bs << std::endl;
}

void swapXOR(int& a, int& b)
{
    if (a == b)
    {
        return;
    }
        
    a ^= b;
    b ^= a;
    a ^= b;
}

bool isPowerOfTwo(const int x)
{
    return x && !(x & (x - 1));
}

int countBits(int x)
{
    int count = 0;
    while (x)
    {
        count += (x & 0xb0000'0001);
        x >>= 1U;
    }

    return count;
}

int InvertColor(const int clColor)
{
    return ~clColor & 0x00FFFFFF;
}

void shiftBits(char& c, const char s)
{
    c = 1 << s;
}

void applyMask(char& c, const char m)
{
    c |= m;
}

void clearMask(char& c, const char m)
{
    c &= ~m;
}

