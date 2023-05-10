#pragma once

#include <cmath>
#include <thread>
#include <mutex>

bool isPrime(int n)
{
    int limit = static_cast<int>(std::sqrt(n));
    for (int i = 2; i <= limit; ++i)
    {
        if (n % i == 0)
        {
            return false;
        }
    }

    return true;
}

size_t calcPrime(int thCount, int first, int last)
{
    std::vector<std::thread> threads;
    threads.reserve(thCount);

    int chunk = (last - first + 1) / thCount;

    std::vector<int> result;
    std::mutex lock;

    for (int i = 0; i < thCount; ++i)
    {
        int start = first + i * chunk;
        int end = (i == thCount - 1) ? last : start + chunk - 1;

        auto l = [&result, &lock](int from, int to)
        {
            for (int i = from; i <= to; ++i)
            {
                if (isPrime(i))
                {
                    std::lock_guard<std::mutex> g(lock);
                    result.push_back(i);
                }
            }
        };

        std::thread t(l, start, end);
        threads.push_back(std::move(t));
    }

    for (auto& th : threads)
    {
        th.join();
    }

    return result.size();
}

void DoWork(int& a)
{
    a += 5;
}

int getWork()
{
    return 6;
}

class M
{
public:
    void DoWork(){};
    void DoesWork(int n){};
};

void multith()
{
    int n = 2;
    std::thread t(DoWork, std::ref(n));
    t.join();

    int result = 0;
    std::thread t1([&result]() { result = getWork(); });
    t1.join();

    class M m;
    std::thread t3(&M::DoWork, m);
    t3.join();

    std::thread t4(&M::DoesWork, m, 5);
    t4.join();

    std::thread t5([&](){m.DoWork(); });
    t5.join();
}