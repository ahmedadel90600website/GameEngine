#pragma once
#include "Public/Core.h"

struct FEventDataBase;

class GameEngine_API LayerBase
{
public:

	virtual void OnAttached() {}
	virtual void OnRemoved() {}
	virtual void Tick(const float deltaTime) {}
	virtual void OnEvent(FEventDataBase& inEvent) {}
	virtual void OnImGuiRender() {}
};