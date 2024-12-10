#include "Public/PCH.h"
#include "Public/Events/MouseEvents/MousePressedEvent.h"

MousePressedEvent::MousePressedEvent(int inButton) :
	MouseKeyEvent(inButton)
{
}

EEventType MousePressedEvent::GetEventType() const
{
	return EEventType::MOUSE_BUTTON_PRESSED;
}

std::string MousePressedEvent::GetEventName() const
{
	return std::string("Mouse button pressed");
}