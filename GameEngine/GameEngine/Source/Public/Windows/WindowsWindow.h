#pragma once

#include "Public/Windows/WindowBase.h"
#include "Public/Windows/Structs/WindowProps.h"

struct GLFWwindow;

class GameEngine_API WindowsWindow : public WindowBase
{
public:

	WindowsWindow(const FWindowProps& inProps);

	virtual ~WindowsWindow();

	int GetWidth() const override;
	int GetHeight() const override;
	void Test(GLFWwindow* window) {}
	// WindowBase ///////////////////////////////////////////////////////////////////
	void OnUpdate() override;
	void SetIsVSyncEnabled(const bool enabled) override;
	bool GetIsVSyncEnabled() const override;
	// WindowBase ///////////////////////////////////////////////////////////////////

	static MulticastDelegate<double, double> OnMouseMoved;

private:

	void Initialize(const FWindowProps& inProps);
	void ShutDown();

	GLFWwindow* TheGLFWWindow = nullptr;
};