#pragma once

#include "Public/Core.h"

struct GameEngine_API FVector2
{
	FVector2() {}
	FVector2(float inX, float inY) :
		X(inX),
		Y(inY)
	{

	}

	float X = 0.0f;
	float Y = 0.0f;
};