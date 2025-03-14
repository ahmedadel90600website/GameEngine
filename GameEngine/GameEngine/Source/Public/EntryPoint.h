#pragma once

// Note that this file is only included in SandboxApplication.cpp so the scope of this file will have GameEngine_Build_DLL be undefined.

// Engine
#include "Public/Application.h"
#include "Public/Profiler/Instrumentor.h"

// Third party
#include "spdlog/logger.h"

int main(int argc, char* argv[])
{
	GameEngineLog::Initialize();

	BEGIN_PROFILER_SESSION("Application creation Session", "Profiler_Application_Creation.json")
	Application* app = CreateApplication();
	END_PROFILER_SESSION();

	BEGIN_PROFILER_SESSION("Runtime Session", "Profiler_Runtime.json")
	app->Run();
	END_PROFILER_SESSION();

	BEGIN_PROFILER_SESSION("Application Ending Session", "Profiler_Application_Ending.json")
	delete app;
	END_PROFILER_SESSION();

	return 0;
}