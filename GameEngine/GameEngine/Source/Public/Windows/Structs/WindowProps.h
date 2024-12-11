#pragma once

#include "Public/PCH.h"

struct WindowProps
{
	std::string Title = "Window";
	float Height = 100.0f;
	float Width = 100.0f;
	WindowProps() {}
	WindowProps(const std::string& inTitle, float inHeight, float inWidth) :
		Title(inTitle),
		Height(inHeight),
		Width(inWidth)
	{

	}
};