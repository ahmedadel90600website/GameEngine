// Game
#include "Public/SandboxApplication.h"

// Engine
#include "Public/EntryPoint.h"
#include "Public/Layers/Overlays/OverlayBase.h"
//#include "ImGui/imgui.h"

class TestOverlay : public OverlayBase
{
	virtual void OnImGuiRender() override
	{
		//ImGui::Begin("Test");
		//ImGui::Text("Hello World");
		//ImGui::End();
	}

};

SandboxApplication::SandboxApplication()
{
	PushOverlay(static_cast<std::unique_ptr<TestOverlay>>(new TestOverlay()));

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