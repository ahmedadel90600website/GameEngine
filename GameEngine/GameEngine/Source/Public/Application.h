#pragma once

#include "Public/Core.h"

class GameEngine_API Application
{

public:

	Application();
	virtual ~Application();
	virtual void Run();
};

extern Application* CreateApplication();