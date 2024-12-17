#pragma once
#include "Public/EventData/EventDataBase.h"

struct GameEngine_API FButtonActionEventData : public FEventDataBase
{
	FButtonActionEventData(const int button, const int scanCode, const int action, const int mods) :
		Button(button),
		ScanCode(scanCode),
		Action(action),
		Mods(mods)
	{

	}

	int Button = -1; 
	int ScanCode = -1;
	int Action = -1;
	int Mods = -1;
};