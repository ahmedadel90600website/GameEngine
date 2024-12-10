#include "Public/PCH.h"
#include "Public/Events/KeyboardEvents/KeyboardButtonReleased.h"

KeyboardButtonReleased::KeyboardButtonReleased(const int inButton) :
	KeyboardEvent(inButton)
{
}

EEventType KeyboardButtonReleased::GetEventType() const
{
	return EEventType::KEYBOARD_RELEASED;
}

std::string KeyboardButtonReleased::GetEventName() const
{
	return std::string();
}