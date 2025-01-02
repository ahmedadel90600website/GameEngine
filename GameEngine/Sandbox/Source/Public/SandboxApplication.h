#pragma once

// Engine
#include "Public/Application.h"
#include "Public/Layers/ImGuiLayer.h"

class SandboxApplication : public Application
{
public:

	SandboxApplication();
	~SandboxApplication();
	void Tick() override;

private:

	std::shared_ptr<ImGuiLayer> TheImGuiLayer = nullptr;
};