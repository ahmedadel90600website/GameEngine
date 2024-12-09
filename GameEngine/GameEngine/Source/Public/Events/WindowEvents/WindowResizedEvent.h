#pragma once

#include "Public/Core.h"
#include "Public/Events/Event.h"

class GameEngine_API WindowResizedEvent : public Event
{
public:

	WindowResizedEvent(const float inWidth, const float inHeight);

	// Event /////////////////////////////////////////
	EEventType GetEventType() const override;
	EEventConfiguration GetEventCategory() const override;
	std::string GetEventName() const override;
	// Event /////////////////////////////////////////

	float GetWidth() const;
	float GetHeight() const;

private:

	float Width = 0.0f;
	float Height = 0.0f;
};