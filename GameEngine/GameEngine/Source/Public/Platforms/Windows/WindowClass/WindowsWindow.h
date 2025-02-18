#pragma once

#include "Public/WindowClass/WindowBase.h"
#include "Public/WindowClass/Structs/WindowProps.h"
#include "Public/Platforms/Rendering/OpenGL/OpenGLGraphicsContext.h"
#include "Public/Core.h"

struct GLFWwindow;

class WindowsWindow : public WindowBase
{
public:

	WindowsWindow(const FWindowProps& inProps);

	virtual ~WindowsWindow();

	int GetWidth() const override;
	int GetHeight() const override;
	// WindowBase ///////////////////////////////////////////////////////////////////
	void OnUpdate() override;
	void SetIsVSyncEnabled(const bool enabled) override;
	bool GetIsVSyncEnabled() const override;
	void* GetNativeWindow() const override;
	// WindowBase ///////////////////////////////////////////////////////////////////

	static MulticastDelegate<double, double> OnMouseMoved;

private:

	void Initialize(const FWindowProps& inProps);
	void ShutDown();

	GLFWwindow* TheGLFWWindow = nullptr;
	TUniquePtr<GraphicsContext> TheGraphicsContext = nullptr;
};