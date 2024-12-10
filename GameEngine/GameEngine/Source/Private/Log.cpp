#include "Public/PCH.h"

// Engine
#include "Public/Log.h"

// Thirdparty
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> GameEngineLog::GameEngineLogger = nullptr;
std::shared_ptr<spdlog::logger> GameEngineLog::ApplicationLogger = nullptr;

void GameEngineLog::Initialize()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");
	GameEngineLogger = spdlog::stdout_color_mt("GameEngine");
	if (GameEngineLogger != nullptr)
	{
		GameEngineLogger->set_level(spdlog::level::trace);
	}
	else
	{
		std::cout << "Error: GameEngineLog::Initialize, the logging system couldn't create an Engine logger!";
	}

	ApplicationLogger = spdlog::stdout_color_mt("Application");
	if (ApplicationLogger != nullptr)
	{
		ApplicationLogger->set_level(spdlog::level::trace);
	}
	else
	{
		std::cout << "Error: GameEngineLog::Initialize, the logging system couldn't create an Application logger!";
	}
}

std::shared_ptr<spdlog::logger>& GameEngineLog::GetGameEngineLogger()
{
	return GameEngineLogger;
}

std::shared_ptr<spdlog::logger>& GameEngineLog::GetApplicationLogger()
{
	return ApplicationLogger;
}