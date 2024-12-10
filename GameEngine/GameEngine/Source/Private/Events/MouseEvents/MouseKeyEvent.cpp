#include "Public/PCH.h"
#include "Public/Events/MouseEvents/MouseKeyEvent.h"

MouseKeyEvent::MouseKeyEvent(int inButton) :
	Button(inButton)
{
}

EEventConfiguration MouseKeyEvent::GetEventCategory() const
{
	return (EEventConfiguration)((int)EEventConfiguration::INPUT | (int)(EEventConfiguration::MOUSE) | (int)(EEventConfiguration::MOUSE_BUTTON));
}