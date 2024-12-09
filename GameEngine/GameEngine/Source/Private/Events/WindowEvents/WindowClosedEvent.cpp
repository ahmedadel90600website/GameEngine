#include "Public/Events/WindowEvents/WindowClosedEvent.h"

EEventType WindowClosedEvent::GetEventType() const
{
    return EEventType::WINDOW_CLOSED;
}

EEventConfiguration WindowClosedEvent::GetEventCategory() const
{
    return EEventConfiguration::APPLICATION;
}

std::string WindowClosedEvent::GetEventName() const
{
    return std::string("Window Closed Event");
}