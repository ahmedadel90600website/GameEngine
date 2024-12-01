// Game
#include "Public/SandboxApplication.h"

// Engine
#include "Public/EntryPoint.h"

// std
#include <iostream>

SandboxApplication::SandboxApplication()
{
}

SandboxApplication::~SandboxApplication()
{
}

void SandboxApplication::Run()
{
	std::cout << "SandboxApplication is running";
}

Application* CreateApplication()
{
	return new SandboxApplication();
}