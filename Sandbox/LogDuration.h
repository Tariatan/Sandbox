#pragma once

#include <string>
#include <iostream>
#include <chrono>

class LogDuration
{
public:
    explicit LogDuration(const std::string& msg = "")
        : message(msg + ": ")
        , start(std::chrono::steady_clock::now()) {}

    ~LogDuration()
    {
        auto finish = std::chrono::steady_clock::now();
        auto duration = finish - start;
        std::cerr << message.c_str() << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms" << std::endl;
    }
private:
    std::string message;
    std::chrono::steady_clock::time_point start;
};

#define UNIQ_ID_IMPL(lineno) _a_local_var##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)
#define LOG_DURATION(message) LogDuration UNIQ_ID(__LINE__)(message)
