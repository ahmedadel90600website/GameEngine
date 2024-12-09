#include "Public/Events/MouseEvents/MouseMovedEvent.h"

MouseMovedEvent::MouseMovedEvent(const float inPositionX, const float inPositionY) :
	PositionX(inPositionX),
	PositionY(inPositionY)
{
}

EEventType MouseMovedEvent::GetEventType() const
{
	return EEventType::MOUSE_HAS_MOVED;
}

EEventConfiguration MouseMovedEvent::GetEventCategory() const
{
	return (EEventConfiguration)((int)EEventConfiguration::INPUT | (int)EEventConfiguration::MOUSE);
}

std::string MouseMovedEvent::GetEventName() const
{
	return std::string("Mouse moved event");
}

float MouseMovedEvent::GetPositionX() const
{
	return PositionX;
}

float MouseMovedEvent::GetPositionY() const
{
	return PositionY;
}