#pragma once

#include "Public/Core.h"

enum class EEventType : uint8_t
{
	NONE,
	WINDOW_CLOSED, WINDOW_RESIZED, WINDOW_FOCUSED, WINDOW_LOST_FOCUS, WINDOW_MOVED,
	KEYBOARD_PRESSED, KEYBOARD_RELEASED,
	MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, MOUSE_HAS_MOVED, MOUSE_SCROLLED
};

enum class EEventConfiguration : uint8_t
{
	NONE = 0,
	APPLICATION = 1 << 0,
	INPUT = 1 << 1,
	KEYBOARD = 1 << 2,
	MOUSE = 1 << 3,
	MOUSE_BUTTON = 1 << 4
};

class GameEngine_API Event
{
public:

	virtual EEventType GetEventType() const = 0;
	virtual EEventConfiguration GetEventCategory() const = 0;
	virtual std::string GetEventName() const = 0;

	bool IsOfConfigyrationType(const EEventConfiguration inConfigType) const;
	void SetHasBeenHandled(const bool inValue);

protected:

	Event();

private:

	bool bHasBeenHandled : 1;
};