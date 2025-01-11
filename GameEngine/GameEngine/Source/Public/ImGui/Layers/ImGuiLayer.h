#pragma once

#include "Public/Layers/Overlays/OverlayBase.h"

struct FButtonActionEventData;
struct FMouseMoveEventData;
struct FMouseScrollEventData;
struct FWindowClosedEventData;
struct FWindowResizedEventData;
struct FCharEventData;

class GameEngine_API ImGuiLayer : public OverlayBase
{

public:

	void OnAttached() override;
	void OnRemoved() override;

	void BeginRendering();
	void OnImGuiRender() override;
	void EndRendering();

	float CurrentTime = 0.0f;
};