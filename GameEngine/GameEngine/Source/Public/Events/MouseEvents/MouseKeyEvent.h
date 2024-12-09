#include "Public/Core.h"
#include "Public/Events/Event.h"

class GameEngine_API MouseKeyEvent : public Event
{
public:

	MouseKeyEvent(int Button);

	// Event /////////////////////////////////////////
	EEventConfiguration GetEventCategory() const override;
	// Event /////////////////////////////////////////

private:

	uint8_t Button = 0.0f;
};