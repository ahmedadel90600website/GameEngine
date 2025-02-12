#pragma once

#include "Public/Core.h"
#include "Public/Input/KeyCodes.h"
#include "glm/vec2.hpp"

class GameEngine_API Input
{
public:

	static bool IsKeyDown(const int inKey);
	static bool IsAMouseKey(const int inKey);
	static glm::vec2 GetMousePosition();

private:
	
	virtual bool IsKeyDownImplementation(const int inKey) const = 0;
	virtual bool IsAMouseKeyImplementation(const int inKey) const = 0;
	virtual glm::vec2 GetMousePositionImplementation() const = 0;

	static std::unique_ptr<Input> InputSingleton;
};