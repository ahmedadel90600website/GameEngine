#include "Public/Core.h"
#include "Public/Events/MouseEvents/MouseKeyEvent.h"

class GameEngine_API MouseReleasedEvent : public MouseKeyEvent
{
public:

	MouseReleasedEvent(int inButton);

	// Event /////////////////////////////////////////
	EEventType GetEventType() const override;
	std::string GetEventName() const override;
	// Event /////////////////////////////////////////
};