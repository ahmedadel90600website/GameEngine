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

void SandboxApplication::Tick()
{
	Application::Tick();

}

Application* CreateApplication()
{
	return new SandboxApplication();
}