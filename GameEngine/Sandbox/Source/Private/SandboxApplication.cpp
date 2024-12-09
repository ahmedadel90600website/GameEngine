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
	KeyboardButtonReleased TestEvent(2);
	if (TestEvent.IsOfConfigyrationType(EEventConfiguration::MOUSE))
	{
		Application_LOG(error, "This isn't a keyboard event");
	}
	else if (TestEvent.IsOfConfigyrationType(EEventConfiguration::KEYBOARD))
	{
		Application_LOG(info, "This is a keyboard event");
	}
}

Application* CreateApplication()
{
	return new SandboxApplication();
}