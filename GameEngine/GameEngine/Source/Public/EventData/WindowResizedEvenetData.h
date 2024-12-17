#pragma once

class GLFWwindow;

#pragma once
#include "Public/EventData/EventDataBase.h"

struct GameEngine_API FWindowResizedEventData : public FEventDataBase
{
	FWindowResizedEventData(GLFWwindow* inWindow, int width, int height) :
		TheGLFWWindow(inWindow),
		Width(width),
		Height(height)
	{

	}

	GLFWwindow* TheGLFWWindow = nullptr;
	int Width = 0;
	int Height = 0;
};