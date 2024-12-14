#include "Public/PCH.h"
#include "Public/Windows/WindowBase.h"


MulticastDelegate<double, double>& WindowBase::GetOnMouseMovedRef()
{
	return TheWindowData.OnMouseMoved;
}

MulticastDelegate<double, double>& WindowBase::GetOnMouseScrolledRef()
{
	return TheWindowData.OnMouseScrolled;
}