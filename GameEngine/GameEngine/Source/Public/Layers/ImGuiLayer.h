#pragma once

#include "Public/Layers/LayerBase.h"

class GameEngine_API ImGuiLayer : public LayerBase
{

public:

	void OnAttached() override;
	void OnRemoved() override;
	void Tick() override;
	void OnEvent(FEventDataBase& inEvent) override;

private:

	float CurrentTime = 0.0f;
};