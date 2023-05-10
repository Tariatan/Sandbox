#include "UTILITIES.h"

#include "Factory.h"
#include "Prototype.h"
#include "Builder.h"
#include "Bridge.h"
#include "Composite.h"
#include "Decorator.h"
#include "Proxy.h"
#include "Flyweight.h"
#include "CRTP.h"
#include "VendingMachine.h"
#include "Multithreading.h"
#include "Bits.h"
#include "Sizeof.h"
#include "Exceptions.h"
#include "LogDuration.h"

#include <sstream>
#include <iostream>
#include <map>
#include <atomic>
#include <vector>
#include <algorithm>
#include <array>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <memory>

using namespace std;

void sort(int ar[], int size)
{
    for (auto i = 0; i < size; ++i)
    {
        for (auto j = 1; j < size; ++j)
        {
            if (ar[j] < ar[j - 1])
            {
                swap(ar[j], ar[j - 1]);
            }
        }
    }
}

void reverse(int ar[], int size)
{
    int i = 0;
    int j = size - 1;
    while (i < j)
    {
        swap(ar[i], ar[j]);
        ++i;
        --j;
    }
}

tuple<int, int> minMax(int ar[], int size)
{
    // { 43, 50, 0, 2, 61, 13 };
    
    if (size == 0)
    {
        return { 0, 0 };
    }

    std::pair<int, int> res{ ar[0], ar[0] };

    for (int i = 1; i < size; ++i)
    {
        if (ar[i] < res.first)
        {
            res.first = ar[i];
        }

        if (ar[i] > res.second)
        {
            res.second = ar[i];
        }
    }

    return res;
}

int smallest(int ar[], int size, int k)
{
    // {7, 10, 4, 3, 20, 15}
    sort(ar, size);
    return ar[k-1];
}

void DutchNationalFlag(int ar[], int size)
{
    //{0, 1, 1, 0, 1, 2, 1, 2, 0, 0, 0, 1}

    int b = 0;
    int e = size - 1;

    int anchor = 0;

    while (anchor <= e)
    {
        if (ar[anchor] == 0)
        {
            swap(ar[b], ar[anchor]);
            ++anchor;
            ++b;
        }
        else if (ar[anchor] == 1)
        {
            ++anchor;
        }
        else if (ar[anchor] == 2)
        {
            swap(ar[e], ar[anchor]);
            --e;
        }
    }
}

void negativeFirst(int ar[], int size)
{
    // {-12, 11, -13, -5, 6, -7, 5, -3, -6}

    int begin = 0;
    int end = size - 1;

    while (begin < end)
    {
        if (ar[begin] > 0)
        {
            swap(ar[begin], ar[end]);
            --end;
        }
        else
        {
            ++begin;
        }
    }
}

void printArray(int ar[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        std::cout << ar[i] << " ";
    }
}

int romanToInt(const string& s)
{
	if ((s.length() < 1) || (s.length() > 15))
	{
		return 0;
	}

	if (s.find_first_not_of("IVXLCDM") != s.npos)
	{
		return 0;
	}

    map<char, int> numerals = { {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100},{'D', 500}, {'M', 1000} };

    int result = 0;
    const auto len = s.length();

    for (size_t i = 0u; i < len; ++i)
	{
        const char ch = s[i];
        if(((i + 1U) < len) && (numerals[ch] < numerals[s[i + 1U]]))
        {
            result -= numerals[ch];
        }
        else
        {
            result += numerals[ch];
        }
	}

	return result;
}

string intToRoman(int num)
{
	if ((num < 1) || (num > 3999))
	{
		return "";
	}

    static const char* hundreds[] = { "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" };
    static const char* tens[] = { "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" };
    static const char* ones[] = { "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };

    string result;
    result.append(num / 1000, 'M');
    result.append(hundreds[num % 1000 / 100]);
    result.append(tens[num % 100 / 10]);
    result.append(ones[num % 10]);
	return result;
}

bool contains(int item)
{
    static const std::unordered_set<int> items{ 5, 6, 2, 1, 8, 9, 0 };

    return items.count(item);
}

int getMaxInt()
{
    return std::numeric_limits<int>::max();
}

void digitSeparator()
{
    auto b = 0b1100'1100;
    b;
    auto m = 1'000'000;
    m;
}
// Structured Binding
void structuredBinding()
{
    std::map<int, string> ctMap{ {1, "one" }, {2, "two"}, {3, "three"} };

    for (const auto& [key, value] : ctMap)
    {
        cout << key << ": " << value << endl;
    }
}

double power(double base, int exp)
{
    if (exp == 0)
    {
        return 1;
    }

    if (exp < 0)
    {
        exp = abs(exp);
        base = 1 / base;
    }

    //return base * power(base, exp - 1);

    if (exp % 2 == 0)
    {
        return power(base * base, exp / 2);
    }

    return base * power(base, (exp - 1));
}

void intersection(int arr1[], int size1, int arr2[], int size2)
{
/*
    input:
    int arr1[] = { 7, 1, 5, 2, 3, 6 };
    int arr2[] = { 3, 8, 6, 20, 7 };
    result:
    intersection {3, 6, 7 }
*/
    std::vector<int> inter;
    for (int i = 0; i < size1; ++i)
    {
        for (int j = 0; j < size2; ++j)
        {
            if (arr1[i] == arr2[j])
            {
                inter.push_back(arr1[i]);
            }
        }
    }
}

void unionset(int arr1[], int size1, int arr2[], int size2)
{
/*
    input:
    int arr1[] = { 7, 1, 5, 2, 3, 6 };
    int arr2[] = { 3, 8, 6, 20, 7 };
    result:
    union {1, 2, 3, 5, 6, 7, 8, 20}
*/
    std::set<int> unionset;
    for (int i = 0; i < size1; ++i)
    {
        unionset.emplace(arr1[i]);
    }
    for (int i = 0; i < size2; ++i)
    {
        unionset.emplace(arr2[i]);
    }
}

void rotate(int ar[], int size)
{
/*
Input:  arr[] = { 1, 2, 3, 4, 5 }
Output: arr[] = { 5, 1, 2, 3, 4 }
*/
    int tmp = ar[size - 1];
    for (int i = size - 1; i > 0; --i)
    {
        ar[i] = ar[i - 1];
    }
    ar[0] = tmp;
}

std::unordered_map<int, int> memo;
// Dynamic programming = recurring function + memo
int fibonacci(int n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }

    if (memo.count(n) > 0)
    {
        return memo[n];
    }

    // optimal substructure of overlapping subprograms
    memo[n] = fibonacci(n - 1) + fibonacci(n - 2);

    return memo[n];
}

// Largest Subarray Sum Problem (Kadane’s Algorithm)
int LSSP(int ar[], int size)
{
    //                 /                \
    // input: { -2, -3, 4, -1, -2, 1, 5, -3 };
    // output: 7
    int max_sum_so_far = std::numeric_limits<int>::min();
    int max_sum_ending_here = 0;

    for (int i = 0; i < size; ++i)
    {
        max_sum_ending_here += ar[i];

        if (max_sum_so_far < max_sum_ending_here)
        {
            max_sum_so_far = max_sum_ending_here;
        }

        if (max_sum_ending_here < 0)
        {
            max_sum_ending_here = 0;
        }
    }

    return max_sum_so_far;
}

// Minimize the maximum difference between the heights
int getMinDif(int arr[], int size, int k)
{
/*
    Given the heights of N towers and a value of K,
    either increase or decrease the height of every tower by K (only once) where K > 0.
    After modifications, the task is to minimize the difference between the heights of the longest and the shortest tower
    and output its difference.

    Input: arr[] = {3, 9, 12, 16, 20}, k = 3
    Output: Maximum difference is 11, arr[] = {6, 12, 9, 13, 17}

    The idea is to increase the first i towers by k and decrease the rest tower by k after sorting the heights,
    then calculate the maximum height difference.
*/
    sort(arr, size);

    // Maximum possible height difference
    int ans = arr[size - 1] - arr[0];

    int smallest = arr[0] + k;
    int largest = arr[size - 1] - k;
    int min;
    int max;

    for (int i = 1; i < size; ++i)
    {
        // If on subtracting k we got
        // negative then continue
        if (arr[i] - k < 0)
            continue;

        // Minimum element when we
        // add k to whole array
        min = std::min(smallest, arr[i] - k);

        // Maximum element when we
        // subtract k from whole array
        max = std::max(arr[i - 1] + k, largest);

        ans = std::min(ans, max - min);
    }
    return ans;
}

int sum(const std::vector<int>& v)
{
    return std::accumulate(v.begin(), v.end(), 0);
}

// String to int
string timeConvertor(string s)
{
    //string s = "12:05:45AM";

    bool isPM = s.substr(s.size() - 2) == "PM";
    int HH = std::stoi(s.substr(0, 2));
    int MM = std::stoi(s.substr(3, 2));
    int SS = std::stoi(s.substr(6, 2));

    if (isPM)
    {
        if (HH < 12)
        {
            HH += 12;
        }
    }
    else
    {
        if (HH == 12)
        {
            HH = 0;
        }
    }

    const int buf_len = 9;
    char buf[buf_len];
    std::snprintf(buf, buf_len, "%0.2d:%0.2d:%0.2d", HH, MM, SS);
    return buf;
}

bool isPalindrome(const std::string& s)
{
    if (s.empty() == 0)
    {
        return false;
    }

    auto itB = s.begin();
    auto itE = s.end() - 1;

    for (; itB < itE; ++itB, --itE)
    {
        if (*itB != *itE)
        {
            return false;
        }
    }

    return true;
}

bool isAllPalindrome(const std::vector<int>& v)
{
    if (v.empty() == 0)
    {
        return false;
    }

    for (auto el : v)
    {
        std::string s{ std::to_string(el) };
        if (!isPalindrome(s))
        {
            return false;
        }
    }

    return true;
}

// Trailing return type is used to represent a fully generic return type for a+b.
template <typename FirstType, typename SecondType>
auto trailingReturnType(FirstType a, SecondType b) -> decltype(a + b)
{
    return a + b;
}

auto CLangPotentialMemoryLeakWarning()
{
    // Potential memory leak
    //return [x = std::make_shared<std::string>()](){};

    // Workaround:
    auto x = std::make_unique<std::string>();
    return x;// [x = std::move(x)] (){};
}

[[nodiscard]] int switchFallthrough(int i)
{
    switch (i)
    {
        case 0:
            [[fallthrough]];
        case 1:
            break;
        default:
            break;
    }

    return 0;
}

std::string dayOfProgrammer(int year)
{
    std::string result;
    if (year == 1918)
    {
        result = "26.09.1918";
    }
    else
    {
        bool isLeap = false;
        if (year < 1918)
        {
            isLeap = (year % 4 == 0);
        }
        else
        {
            isLeap = (((year % 400) == 0) || (((year % 4) == 0) && ((year % 100) != 0)));
        }

        result = isLeap ? "12.09." : "13.09.";
        result += std::to_string(year);
    }

    return result;
}

int magicSquare(const std::vector<std::vector<int>> v)
{
//    in
//    {{ 5, 3, 4},
//     { 1, 5, 8 },
//     { 6, 4, 2 } };
//     desired at cost = 3
//     8 3 4
//     1 5 9
//     6 7 2
//

    static const std::vector<vector<vector<int>>> vs
    {
        {{8, 1, 6}, {3, 5, 7}, {4, 9, 2}},
        {{6, 1, 8}, {7, 5, 3}, {2, 9, 4}},
        {{4, 9, 2}, {3, 5, 7}, {8, 1, 6}},
        {{2, 9, 4}, {7, 5, 3}, {6, 1, 8}},
        {{8, 3, 4}, {1, 5, 9}, {6, 7, 2}},
        {{4, 3, 8}, {9, 5, 1}, {2, 7, 6}},
        {{6, 7, 2}, {1, 5, 9}, {8, 3, 4}},
        {{2, 7, 6}, {9, 5, 1}, {4, 3, 8}},
    };

    int min_cost = std::numeric_limits<int>::max();
    for (auto matrix : vs)
    {
        int cost = 0;
        for (int row = 0; row < 3; ++row)
        {
            for (int col = 0; col < 3; ++col)
            {
                cost += std::abs((matrix[row][col] - v[row][col]));
            }
        }

        if (cost < min_cost)
        {
            min_cost = cost;
        }
    }

    return min_cost;
}

std::vector<int> climingTheLeaderboard(std::vector<int> ranked, std::vector<int> player)
{
//  in   std::vector<int> ranked{ 100, 100, 50, 40, 40, 20, 10 };
//  in   std::vector<int> player{ 5, 25, 50, 120 };
//  out 6, 4, 2, 1

    auto last = std::unique(ranked.begin(), ranked.end());
    ranked.erase(last, ranked.end());

    std::map<int, int> leaders;
    int pos = 1;
    for (auto rank : ranked)
    {
        leaders[rank] = pos++;
    }

    std::vector<int> results{};
    results.reserve(player.size());

    for (auto score : player)
    {
        auto it = leaders.lower_bound(score);

        if (it == leaders.end())
        {
            results.push_back(1);
        }
        else if (score == it->first)
        {
            results.push_back(it->second);
        }
        else if (score < it->first)
        {
            results.push_back(it->second + 1);
        }
    }

    return results;
}

int grow(int n)
{
//        Period  Height
//         0          1
//         1          2
//         2          3
//         3          6
//         4          7
//         5          14

    if (n == 0)
    {
        return 1;
    }

    return ((n % 2) == 0) ? grow(n - 1) + 1 : grow(n - 1)  * 2;
}

int beautifulDays(int i, int j, int k)
{
// in: i = 20, j = 23, k = 6
// |20 - 02| / 6 = 3    => +1
// |21 - 12| / 6 = 1.5  => +0
// |22 - 22| / 6 = 0    => +1
// |23 - 32| / 6 = 1.5  => +0
// out: 2

    int count = 0;
    for (int day = i; day <= j; ++day)
    {
        std::string num = std::to_string(day);
        std::reverse(num.begin(), num.end());
        int r_day = std::stoi(num);

        int diff = std::abs(day - r_day);

        if ((diff % k) == 0)
        {
            ++count;
        }
    }

    return count;
}

// Literal operator must have a parameter list of the form 'const char *, std::size_t'
int operator""_toInt(const char* text, std::size_t length)
{
    // usage: auto ul = "25"_toInt;
    return std::stoi(text);
}

bool isOneOfAny(std::string word, std::initializer_list<string> strings)
{
    // usage: isOneOfAny("word", {"hello", "world", "work"})
    return std::any_of(strings.begin(), strings.end(), [word](const string value) { return value == word; } );
}

template<class T>
typename std::enable_if_t< std::is_integral_v<T>, T >
SFINAE_Div2(T t)
{
    return t >> 1;
}

template<class T>
typename std::enable_if_t< std::is_floating_point_v<T>, T >
SFINAE_Div2(T t)
{
    return t / 2.0;
}

int cyclicTurner(int positions, int turns, int start)
{
    //     352926151 380324688 94730870    => 122129406
    //     94431605 679262176 5284458      => 23525398
    //     208526924 756265725 150817879   => 72975907
    //     962975336 972576181 396355184   => 405956028
    //     464237185 937820284 255816794   => 265162707

    int warn = 0;
    int turn = (turns - 1 + start) % positions;
    warn = (turn == 0) ? positions : turn;

    return warn;
}

int main()
{
    LOG_DURATION("main");
    std::ignore = system("Color 0A");



    return 0;
}
