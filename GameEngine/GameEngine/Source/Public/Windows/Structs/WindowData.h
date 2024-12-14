#pragma once

#include "Public/PCH.h"
#include "Public/Events/Event.h"
#include "Public/Events/MulticastDelegate.h"

struct WindowData
{
	WindowData() : bIsVSyncEnabled (false) {}

	std::string Title = "Window";
	float Height = 100.0f;
	float Width = 100.0f;
	bool bIsVSyncEnabled : 1;
	std::function<void(Event&)> CallbackFunction;

	MulticastDelegate<double, double> OnMouseMoved;
	MulticastDelegate<double, double> OnMouseScrolled;
};