#include "Public/PCH.h"
#include "Public/Events/KeyboardEvents/KeyboardButtonPressed.h"

KeyboardButtonPressed::KeyboardButtonPressed(const int inButton, const int inRepeatCount) :
	KeyboardEvent(inButton),
	RepeatCount(inRepeatCount)
{
}

EEventType KeyboardButtonPressed::GetEventType() const
{
	return EEventType::KEYBOARD_PRESSED;
}

std::string KeyboardButtonPressed::GetEventName() const
{
	return std::string();
}