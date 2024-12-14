#include "Public/PCH.h"
#include "Public/Events/Event.h"

Event::Event() : bHasBeenHandled(false)
{

}

bool Event::IsOfConfigyrationType(const EEventConfiguration inConfigType) const
{
	return ((int)inConfigType & (int)GetEventCategory());
}

void Event::SetHasBeenHandled(const bool inValue)
{
	bHasBeenHandled = inValue;
}