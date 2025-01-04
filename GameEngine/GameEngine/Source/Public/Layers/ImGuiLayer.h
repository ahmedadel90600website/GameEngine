#pragma once

#include "Public/Layers/LayerBase.h"

struct FButtonActionEventData;
struct FMouseMoveEventData;
struct FMouseScrollEventData;
struct FWindowClosedEventData;
struct FWindowResizedEventData;
struct FCharEventData;

class GameEngine_API ImGuiLayer : public LayerBase
{

public:

	void OnAttached() override;
	void OnRemoved() override;
	void Tick() override;
	void OnEvent(FEventDataBase& inEvent) override;

private:

	bool OnButtonActionEvent(FButtonActionEventData& buttonActionEventData);
	bool OnMouseMovedEvent(FMouseMoveEventData& mouseMovedEventData);
	bool OnMouseScrolldEvent(FMouseScrollEventData& mouseScrolledEventData);
	bool OnCharKeyEvent(FCharEventData& charKeyEventData);
	bool OnWindowClosedEvent(FWindowClosedEventData& mouseScrolledEventData);
	bool OnWindowResizedEvent(FWindowResizedEventData& windowResizedEventData);

	float CurrentTime = 0.0f;
};