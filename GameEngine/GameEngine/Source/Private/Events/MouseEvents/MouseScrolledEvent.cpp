#include "Public/Events/MouseEvents/MouseScrolledEvent.h"

MouseScrolledEvent::MouseScrolledEvent(const float inOffsetX, const float inOffsetY) :
	OffsetX(inOffsetX),
	OffsetY(inOffsetY)
{
}

EEventType MouseScrolledEvent::GetEventType() const
{
	return EEventType::MOUSE_SCROLLED;
}

EEventConfiguration MouseScrolledEvent::GetEventCategory() const
{
	return (EEventConfiguration)((int)EEventConfiguration::MOUSE | (int)EEventConfiguration::INPUT);
}

std::string MouseScrolledEvent::GetEventName() const
{
	return std::string("Mouse scrolled");
}