#pragma once

#include <iostream>
#include <chrono>
#include <string>

#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)
#define LOG_DURATION(message) \
    LogDuration UNIQ_ID(__LINE__)(message);

class LogDuration {
public:
    explicit LogDuration(const std::string& msg = " ")
        : message(msg + ": ")
        , start(std::chrono::steady_clock::now())
    {}

    ~LogDuration() {
        auto finish = std::chrono::steady_clock::now();
        std::cerr
            << message
            << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count()
            << "ms" << std::endl;
    }
private:
    std::string message;
    std::chrono::steady_clock::time_point start;
};