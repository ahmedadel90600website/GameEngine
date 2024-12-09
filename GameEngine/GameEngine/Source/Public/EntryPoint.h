#pragma once

// Note that this file is only included in SandboxApplication.cpp so the scope of this file will have GameEngine_Build_DLL be undefined.

// Engine
#include "Public/Application.h"
#include "Public/Log.h"

// Third party
#include "spdlog/logger.h"

int main(int argc, char* argv[])
{
	GameEngineLog::Initialize();
	Application* app = CreateApplication();
	app->Run();
	delete app;

	return 0;
}