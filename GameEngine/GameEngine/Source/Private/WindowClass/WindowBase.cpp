#include "Public/PCH.h"
#include "Public/WindowClass/WindowBase.h"

MulticastDelegate<FEventDataBase&>& WindowBase::GetOnGLFWEvent()
{
	return TheWindowData.OnGLFWEvent;
}