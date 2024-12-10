#include "Public/PCH.h"
#include "Public/Events/WindowEvents/WindowResizedEvent.h"

WindowResizedEvent::WindowResizedEvent(const float inWidth, const float inHeight) :
	Width(inWidth),
	Height(inHeight)
{
}

EEventType WindowResizedEvent::GetEventType() const
{
	return EEventType::WINDOW_RESIZED;
}

EEventConfiguration WindowResizedEvent::GetEventCategory() const
{
	return EEventConfiguration::APPLICATION;
}

std::string WindowResizedEvent::GetEventName() const
{
	return std::string("Window resized event");
}

float WindowResizedEvent::GetWidth() const
{
	return Width;
}

float WindowResizedEvent::GetHeight() const
{
	return Height;
}