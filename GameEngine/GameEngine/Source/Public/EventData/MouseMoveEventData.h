#pragma once
#include "Public/EventData/EventDataBase.h"

struct GameEngine_API FMouseMoveEventData : public FEventDataBase
{
	FMouseMoveEventData(const double xPosition, const double yPosition) :
		XPosition(xPosition),
		YPosition(yPosition)
	{

	}

	double XPosition = 0.0f;
	double YPosition = 0.0f;
};