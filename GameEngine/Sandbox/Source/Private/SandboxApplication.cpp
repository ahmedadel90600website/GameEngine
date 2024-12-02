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

void SandboxApplication::Run()
{
}

Application* CreateApplication()
{
	return new SandboxApplication();
}