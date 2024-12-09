#include "Public/Core.h"
#include "Public/Events/Event.h"

class GameEngine_API MouseMovedEvent : public Event
{
public:

	MouseMovedEvent(const float InPositionX, const float inPositionY);

	// Event /////////////////////////////////////////
	EEventType GetEventType() const override;
	EEventConfiguration GetEventCategory() const override;
	std::string GetEventName() const override;
	// Event /////////////////////////////////////////

	float GetPositionX() const;
	float GetPositionY() const;

private:

	float PositionX = 0.0f;
	float PositionY = 0.0f;
};