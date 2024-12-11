#pragma once

// Engine
#include "Public/Core.h"
#include "spdlog/Logger.h"

#ifdef GameEngine_Platform_Windows
	#ifdef GameEngine_Build_DLL
		// Warn yellow, error red, info green
		#define	GameEngine_LOG(type, ...) GameEngineLog::GetGameEngineLogger()->type(##__VA_ARGS__);
	#else
		// Warn yellow, error red, info green
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