#pragma once

#include <chrono>

struct FInstrumentationTimer
{
public:

    using TimePoint = std::chrono::steady_clock::time_point;

    FInstrumentationTimer(const char* name)
        : TimerName(name), bHasStopped(false)
    {
        StartTime = std::chrono::high_resolution_clock::now();
    }

    ~FInstrumentationTimer()
    {
        if (!bHasStopped)
        {
            Stop();
        }
    }

    void Stop();

private:

    std::chrono::time_point<std::chrono::steady_clock> StartTime;
    const char* TimerName = nullptr;
    bool bHasStopped : 1;
};