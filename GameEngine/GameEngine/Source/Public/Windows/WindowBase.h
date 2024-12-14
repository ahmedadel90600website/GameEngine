#pragma once

#include "Public/Core.h"
#include "Public/Events/Event.h"
#include "Public/Windows/Structs/WindowProps.h"
#include "Public/Events/MulticastDelegate.h"
#include "Public/Windows/Structs/WindowData.h"

class GameEngine_API WindowBase
{
public:

	virtual ~WindowBase() {}
	virtual void OnUpdate() = 0;

	virtual void SetEventCallback(std::function<void(Event&)> inFunction) = 0;
	virtual void SetIsVSyncEnabled(const bool enabled) = 0;
	virtual bool GetIsVSyncEnabled() const = 0;

	MulticastDelegate<double, double>& GetOnMouseMovedRef();
	MulticastDelegate<double, double>& GetOnMouseScrolledRef();

	static WindowBase* Create(const WindowProps& inProps);

protected:

	WindowData TheWindowData;
};