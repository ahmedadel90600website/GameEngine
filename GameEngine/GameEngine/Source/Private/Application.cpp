#include "Public/PCH.h"

// Engine
#include "Public/Application.h"
#include "Public/Windows/Structs/WindowProps.h"

#include "GLFW/glfw3.h"

Application::Application() :
	bIsRunning(true)
{
	ApplicationWindow = static_cast<std::unique_ptr<WindowBase>>(WindowBase::Create(WindowProps("Test", 1000.0, 1000.0f)));
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