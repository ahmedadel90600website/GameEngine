#pragma once

#include "Public/Application.h"
#include <chrono>

#define SCOPEED_TIMER(timerName) FTimer timer##__LINE__(timerName);

struct FTimer
{
public:

    using TimePoint = std::chrono::steady_clock::time_point;

    FTimer(const char* name)
        : TimerName(name), bHasStopped(false)
    {
        StartTime = std::chrono::high_resolution_clock::now();
    }

    ~FTimer()
    {
        if (!bHasStopped)
        {
            Stop();
        }
    }

    void Stop()
    {
        const TimePoint& endTimepoint = std::chrono::high_resolution_clock::now();
        const long long start = std::chrono::time_point_cast<std::chrono::microseconds>(StartTime).time_since_epoch().count();
        const long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

        bHasStopped = true;
        Application::Get()->AddTimerResult(TimerName, ((end - start) * 0.001f));
    }

private:

    std::chrono::time_point<std::chrono::steady_clock> StartTime;
    const char* TimerName = nullptr;
    bool bHasStopped : 1;
};