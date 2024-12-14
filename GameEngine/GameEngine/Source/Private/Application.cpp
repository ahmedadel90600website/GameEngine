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
		applicationWindowRef.GetOnMouseMovedRef().ADD_OBJECT(Application, this, OnMouseMoved);
		applicationWindowRef.GetOnMouseScrolledRef().ADD_OBJECT(Application, this, OnMouseScrolled);
	}
}

Application::~Application()
{
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