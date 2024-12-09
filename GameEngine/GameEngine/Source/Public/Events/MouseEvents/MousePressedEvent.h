#include "Public/Core.h"
#include "Public/Events/MouseEvents/MouseKeyEvent.h"

class GameEngine_API MousePressedEvent : public MouseKeyEvent
{
public:

	MousePressedEvent(int inButton);

	// Event /////////////////////////////////////////
	EEventType GetEventType() const override;
	std::string GetEventName() const override;
	// Event /////////////////////////////////////////
};