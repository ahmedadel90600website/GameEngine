#include "Public/PCH.h"
#include "Public/Events/MouseEvents/MouseReleasedEvent.h"

MouseReleasedEvent::MouseReleasedEvent(int inButton) :
	MouseKeyEvent(inButton)
{
}

EEventType MouseReleasedEvent::GetEventType() const
{
	return EEventType::MOUSE_BUTTON_RELEASED;
}

std::string MouseReleasedEvent::GetEventName() const
{
	return std::string("Mouse button released");
}