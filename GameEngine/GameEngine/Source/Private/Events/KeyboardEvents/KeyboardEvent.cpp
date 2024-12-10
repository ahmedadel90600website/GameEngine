#include "Public/PCH.h"
#include "Public/Events/KeyboardEvents/KeyboardEvent.h"

KeyboardEvent::KeyboardEvent(const int inButton) :
	Button(inButton)
{
}

EEventConfiguration KeyboardEvent::GetEventCategory() const
{
	return (EEventConfiguration)((int)EEventConfiguration::INPUT | (uint8_t)EEventConfiguration::KEYBOARD);
}

int KeyboardEvent::GetButton() const
{
	return Button;
}