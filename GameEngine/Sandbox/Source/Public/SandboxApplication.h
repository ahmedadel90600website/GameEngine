#pragma once

// Engine
#include "Public/Application.h"

class SandboxApplication : public Application
{
public:

	SandboxApplication();
	~SandboxApplication();
	void Run() override;
};