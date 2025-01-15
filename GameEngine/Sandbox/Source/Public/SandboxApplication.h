#pragma once

// Engine
#include "Public/Application.h"

class SandboxApplication : public Application
{
public:

	SandboxApplication();
	~SandboxApplication(); 
	void Tick() override;

private:
};