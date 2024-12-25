#pragma once

#include "Public/Core.h"
#include "Public/Windows/Structs/WindowProps.h"
#include "Public/Events/MulticastDelegate.h"
#include "Public/Windows/Structs/WindowData.h"

struct GLFWwindow;

class GameEngine_API WindowBase
{
public:

	virtual ~WindowBase() {}
	virtual void OnUpdate() = 0;

	virtual void SetIsVSyncEnabled(const bool enabled) = 0;
	virtual bool GetIsVSyncEnabled() const = 0;

	MulticastDelegate<FEventDataBase&>& GetOnGLFWEvent();

	static WindowBase* Create(const FWindowProps& inProps);

protected:

	FWindowData TheWindowData;
};