#pragma once

#include "InstrumentationTimer.h"
#include "Public/Core.h"
#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>

#include <thread>



#ifdef GAMEENGINE_PROFILER

#define BEGIN_PROFILER_SESSION(Name, FilePath) Instrumentor::Get().BeginSession(Name, FilePath);
#define END_PROFILER_SESSION() Instrumentor::Get().EndSession();
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCSIG__)
#define PROFILE_SCOPE(TimerName) FInstrumentationTimer timer##__LINE__(TimerName);

#else

#define BEGIN_PROFILER_SESSION(SessionName, FilePath)
#define END_PROFILER_SESSION(,, FilePath)
#define PROFILE_FUNCTION()
#define PROFILE_SCOPE(TimerName)

#endif


#ifdef GAMEENGINE_RENDERER_PROFILER

#define RENDERER_PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCSIG__)
#define RENDERER_PROFILE_SCOPE(TimerName) FInstrumentationTimer timer##__LINE__(TimerName);

#else

#define RENDERER_PROFILE_FUNCTION() PROFILE_FUNCTION()
#define RENDERER_PROFILE_SCOPE(TimerName) PROFILE_SCOPE(TimerName)

#endif

struct ProfileResult
{
    std::string Name;
    long long Start, End;
    uint32_t ThreadID;
};

struct InstrumentationSession
{
    std::string Name;
};

class Instrumentor
{
public:

    Instrumentor()
        : CurrentSession(nullptr), m_ProfileCount(0)
    {
    }

    void BeginSession(const std::string& name, const std::string& filepath = "results.json");
    void EndSession();
    void WriteProfile(const ProfileResult& result);
    void WriteHeader();
    void WriteFooter();

    static Instrumentor& Get()
    {
        static Instrumentor instance;
        return instance;
    }

private:

    InstrumentationSession* CurrentSession;
    std::ofstream m_OutputStream;
    int m_ProfileCount;
};