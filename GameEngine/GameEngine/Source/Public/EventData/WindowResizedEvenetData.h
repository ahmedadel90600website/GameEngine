#pragma once

#pragma once
#include "Public/EventData/EventDataBase.h"

struct GameEngine_API FWindowResizedEventData : public FEventDataBase
{
	FWindowResizedEventData(int width, int height) :
		Width(width),
		Height(height)
	{

	}

	int Width = 0;
	int Height = 0;
};