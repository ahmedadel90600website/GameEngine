#pragma once

#include "Public/Core.h"
#include "Public/Events/KeyboardEvents/KeyboardEvent.h"

class GameEngine_API KeyboardButtonPressed : public KeyboardEvent
{
public:

	KeyboardButtonPressed(const int inButton, const int inRepeatCount);

	// Event ////////////////////////////////////////////////
	EEventType GetEventType() const override;
	std::string GetEventName() const override;
	// Event ////////////////////////////////////////////////

private:

	int RepeatCount = 0;
};