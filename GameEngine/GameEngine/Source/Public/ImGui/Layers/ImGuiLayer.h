#pragma once

#include "Public/Layers/Overlays/OverlayBase.h"

class ImGuiLayer : public OverlayBase
{

public:

	void OnAttached() override;
	void OnRemoved() override;

	void BeginRendering();
	void OnImGuiRender() override;
	void EndRendering();

	float CurrentTime = 0.0f;
};