#pragma once

#include "Public/Core.h"
#include "Public/Events/Event.h"

class GameEngine_API KeyboardEvent : public Event
{
public:

	EEventConfiguration GetEventCategory() const override;

	int GetButton() const;

protected:

	KeyboardEvent(const int inButton);

private:

	uint8_t Button;
};