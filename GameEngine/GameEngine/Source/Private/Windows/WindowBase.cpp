#include "Public/PCH.h"
#include "Public/Windows/WindowBase.h"

MulticastDelegate<FEventDataBase&>& WindowBase::GetOnGLFWEvent()
{
	return TheWindowData.OnGLFWEvent;
}