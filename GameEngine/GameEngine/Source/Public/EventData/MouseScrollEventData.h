#pragma once
#include "Public/EventData/EventDataBase.h"

struct FMouseScrollEventData : public FEventDataBase
{
	FMouseScrollEventData(const double xOffset, const double yOffset) :
		XOffset(xOffset),
		YOffset(yOffset)
	{

	}

	double XOffset = 0.0f;
	double YOffset = 0.0f;
};