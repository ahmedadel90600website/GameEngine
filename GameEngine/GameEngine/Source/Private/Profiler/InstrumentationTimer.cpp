#include "Public/PCH.h"
#include "Public/Profiler/InstrumentationTimer.h"
#include "Public/Profiler/Instrumentor.h"

void FInstrumentationTimer::Stop()
{
    const TimePoint& endTimepoint = std::chrono::high_resolution_clock::now();
    const long long start = std::chrono::time_point_cast<std::chrono::microseconds>(StartTime).time_since_epoch().count();
    const long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
    const uint32_t threadID = (uint32_t)std::hash<std::thread::id>{}(std::this_thread::get_id());
    Instrumentor::Get().WriteProfile({ TimerName, start, end, threadID });

    bHasStopped = true;
}