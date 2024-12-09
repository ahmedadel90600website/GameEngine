#include "Public/Core.h"
#include "Public/Events/Event.h"

class GameEngine_API MouseScrolledEvent : public Event
{
public:

	MouseScrolledEvent(const float inOffsetX, const float inOffsetY);

	// Event /////////////////////////////////////////
	EEventType GetEventType() const override;
	EEventConfiguration GetEventCategory() const override;
	std::string GetEventName() const override;
	// Event /////////////////////////////////////////

private:

	float OffsetX = 0.0f;
	float OffsetY = 0.0f;
};