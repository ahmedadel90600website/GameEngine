#pragma once

#include "Public/Core.h"

#include "Public/Maths/MathsTypes.h"

class GameEngine_API Input
{
public:

	static bool IsKeyDown(const int inKey);
	static bool IsAMouseKey(const int inKey);
	static FVector2 GetMousePosition();

private:
	
	virtual bool IsKeyDownImplementation(const int inKey) const = 0;
	virtual bool IsAMouseKeyImplementation(const int inKey) const = 0;
	virtual FVector2 GetMousePositionImplementation() const = 0;

	static std::unique_ptr<Input> InputSingleton;
};