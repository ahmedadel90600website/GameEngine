// Game
#include "Public/SandboxApplication.h"

// Engine
#include "Public/EntryPoint.h"

SandboxApplication::SandboxApplication()
{
	TheImGuiLayer = std::make_shared<ImGuiLayer>();
	PushLayer(TheImGuiLayer);
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