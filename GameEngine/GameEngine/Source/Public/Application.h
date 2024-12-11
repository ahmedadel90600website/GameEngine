#pragma once

#include "Public/Core.h"
#include "Public/Windows/WindowBase.h"

class GameEngine_API Application
{

public:

	Application();
	virtual ~Application();
	virtual void Run();

private:

	std::unique_ptr<WindowBase> ApplicationWindow = nullptr;
	bool bIsRunning : 1;
};

extern Application* CreateApplication();