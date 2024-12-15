#include "Public/PCH.h"

// Engine
#include "Public/Application.h"
#include "Public/Windows/Structs/WindowProps.h"

#include "GLFW/glfw3.h"

Application::Application() :
	bIsRunning(true)
{
	ApplicationWindow = static_cast<std::unique_ptr<WindowBase>>(WindowBase::Create(WindowProps("Test", 1000.0, 1000.0f)));
	if (ApplicationWindow != nullptr)
	{
		WindowBase& applicationWindowRef = *ApplicationWindow;
		// Mouse events
		applicationWindowRef.GetOnMouseMovedRef().ADD_OBJECT(Application, this, OnMouseMoved);
		applicationWindowRef.GetOnMouseScrolledRef().ADD_OBJECT(Application, this, OnMouseScrolled);

		// Keyboard events
		applicationWindowRef.GetOnButtonEvent().ADD_OBJECT(Application, this, OnButtonEvent);

		// Window events
		applicationWindowRef.GetOnWindowClosed().ADD_OBJECT(Application, this, OnWindowClosed);
		applicationWindowRef.GetOnWindowResized().ADD_OBJECT(Application, this, OnWindowResized);
	}
}

Application::~Application()
{
	if (ApplicationWindow != nullptr)
	{
		WindowBase& applicationWindowRef = *ApplicationWindow;
		// Mouse events
		applicationWindowRef.GetOnMouseMovedRef().RemoveAll(this);
		applicationWindowRef.GetOnMouseScrolledRef().RemoveAll(this);

		// Keyboard events
		applicationWindowRef.GetOnButtonEvent().RemoveAll(this);

		// Window events
		applicationWindowRef.GetOnWindowClosed().RemoveAll(this);
		applicationWindowRef.GetOnWindowResized().RemoveAll(this);
	}
}

void Application::Run()
{
	while (bIsRunning)
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ApplicationWindow->OnUpdate();
	}
}

void Application::OnMouseMoved(double xPos, double yPos)
{
	GameEngine_LOG(info, "XPos {0}, YPos {1}", xPos, yPos);
}

void Application::OnMouseScrolled(double xOffset, double yOffset)
{
	GameEngine_LOG(info, "XPos {0}, YPos {1}", xOffset, yOffset);
}

void Application::OnButtonEvent(int button, int scanCode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		OnButtonpressed(button, scanCode, mods);
	}
	else if (action == GLFW_REPEAT)
	{
		OnButtonHeld(button, scanCode, mods);
	}
	else if (action == GLFW_RELEASE)
	{
		OnButtonReleased(button, scanCode, mods);
	}
}

void Application::OnButtonpressed(int button, int scanCode, int mods)
{
}

void Application::OnButtonHeld(int button, int scanCode, int mods)
{
}

void Application::OnButtonReleased(int button, int scanCode, int mods)
{
}

void Application::OnWindowClosed(GLFWwindow* closedWindow)
{
	bIsRunning = false;
}

void Application::OnWindowResized(GLFWwindow* closedWindow, int width, int height)
{
}