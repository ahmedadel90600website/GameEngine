#include "Public/PCH.h"
#include "Public/WindowClass/WindowBase.h"

MulticastDelegate<FEventDataBase*>& WindowBase::GetOnWindowEvent()
{
	return TheWindowData.OnWindowEvent;
}