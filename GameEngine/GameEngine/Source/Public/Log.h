#pragma once

// Engine
#include "Core.h"
#include "spdlog/Logger.h"

#ifdef GameEngine_Platform_Windows
	#ifdef GameEngine_Build_DLL
		#define	GameEngine_LOG(type, message) GameEngineLog::GetGameEngineLogger()->type(message);
	#else
		#define	Application_LOG(type, message) GameEngineLog::GetApplicationLogger()->type(message);

	#endif

#else
#error GameEngine supports windows only.

#endif

namespace spdlog
{
	class logger;
}

namespace std
{
	template <class _Ty>
	class shared_ptr;
}

class GameEngine_API GameEngineLog
{
public:

	static void Initialize();

	static std::shared_ptr<spdlog::logger>& GetGameEngineLogger();
	static std::shared_ptr<spdlog::logger>& GetApplicationLogger();

private:

	static std::shared_ptr<spdlog::logger> GameEngineLogger;
	static std::shared_ptr<spdlog::logger> ApplicationLogger;
};