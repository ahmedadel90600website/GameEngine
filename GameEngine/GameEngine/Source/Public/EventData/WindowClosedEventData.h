#pragma once

class GLFWwindow;

#pragma once
#include "Public/EventData/EventDataBase.h"

struct GameEngine_API FWindowClosedEventData : public FEventDataBase
{
	FWindowClosedEventData(GLFWwindow* const inWindow) :
		TheGLFWWindow(inWindow)
	{

	}

	GLFWwindow* TheGLFWWindow = nullptr;
};