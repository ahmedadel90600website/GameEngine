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

MulticastDelegate<int, int, int, int>& WindowBase::GetOnButtonEvent()
{
	return TheWindowData.OnButtonEvent;
}

MulticastDelegate<GLFWwindow*>& WindowBase::GetOnWindowClosed()
{
	return TheWindowData.OnWindowClosed;
}

MulticastDelegate<GLFWwindow*, int, int>& WindowBase::GetOnWindowResized()
{
	return TheWindowData.OnWindowResized;
}