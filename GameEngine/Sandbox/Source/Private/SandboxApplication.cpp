// Game
#include "Public/SandboxApplication.h"

// Engine
#include "Public/EntryPoint.h"

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