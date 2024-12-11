#pragma once

#include "Public/Windows/WindowBase.h"
#include "Public/Windows/Structs/WindowData.h"
#include "Public/Windows/Structs/WindowProps.h"

extern class GLFWwindow;

class WindowsWindow : public WindowBase
{
public:

	WindowsWindow(const WindowProps& inProps);

	virtual ~WindowsWindow();

	float GetWidth() const;
	float GetHeight() const;

	// WindowBase ///////////////////////////////////////////////////////////////////
	void OnUpdate() override;
	void SetEventCallback(std::function<void(Event&)> inFunction) override;
	void SetIsVSyncEnabled(const bool enabled) override;
	bool GetIsVSyncEnabled() const override;
	// WindowBase ///////////////////////////////////////////////////////////////////

private:

	void Initialize(const WindowProps& inProps);
	void ShutDown();

	GLFWwindow* TheGLFWWindow = nullptr;
	WindowData TheWindowData;
};