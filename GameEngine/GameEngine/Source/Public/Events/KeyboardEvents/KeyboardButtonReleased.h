#pragma once

#include "Public/Core.h"
#include "Public/Events/KeyboardEvents/KeyboardEvent.h"

class GameEngine_API KeyboardButtonReleased : public KeyboardEvent
{
public:

	KeyboardButtonReleased(const int inButton);

	// Event ////////////////////////////////////////////////
	EEventType GetEventType() const override;
	std::string GetEventName() const override;
	// Event ////////////////////////////////////////////////
};