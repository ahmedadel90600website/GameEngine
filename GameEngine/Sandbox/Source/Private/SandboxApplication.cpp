// Game
#include "Public/SandboxApplication.h"

// Engine
#include "Public/EntryPoint.h"
#include "Public/Events/KeyboardEvents/KeyboardButtonReleased.h"

SandboxApplication::SandboxApplication()
{
}

SandboxApplication::~SandboxApplication()
{
}

void SandboxApplication::Run()
{
	Application::Run();

}

Application* CreateApplication()
{
	return new SandboxApplication();
}