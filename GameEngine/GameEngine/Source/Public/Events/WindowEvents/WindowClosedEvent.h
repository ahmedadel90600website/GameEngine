#pragma once

#include "Public/Core.h"
#include "Public/Events/Event.h"

class GameEngine_API WindowClosedEvent : public Event
{
public:

	// Event //////////////////////////////////////////////
	EEventType GetEventType() const override;
	EEventConfiguration GetEventCategory() const override;
	std::string GetEventName() const override;
	// Event //////////////////////////////////////////////
};