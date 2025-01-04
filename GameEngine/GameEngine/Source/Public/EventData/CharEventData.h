#pragma once

#include "Public/EventData/EventDataBase.h"

struct GameEngine_API FCharEventData : public FEventDataBase
{
	FCharEventData(unsigned int inCharKey) :
		CharKey(inCharKey)
	{

	}

	unsigned int CharKey;
};