#pragma once

#include "Public/Core.h"
#include "Public/Windows/WindowBase.h"

extern class GLFWwindow;

class GameEngine_API Application
{

public:

	Application();
	virtual ~Application();
	virtual void Run();

private:

	// Mouse events
	void OnMouseMoved(double xPos, double yPos);
	void OnMouseScrolled(double xPos, double yPos);

	// Buttons events
	void OnButtonEvent(int button, int scanCode, int action, int mods);
	void OnButtonpressed(int button, int scanCode, int mods);
	void OnButtonHeld(int button, int scanCode, int mods);
	void OnButtonReleased(int button, int scanCode, int mods);

	// Window events
	void OnWindowClosed(GLFWwindow* closedWindow);
	void OnWindowResized(GLFWwindow* closedWindow, int width, int height);

	std::unique_ptr<WindowBase> ApplicationWindow = nullptr;
	bool bIsRunning : 1;
};

extern Application* CreateApplication();