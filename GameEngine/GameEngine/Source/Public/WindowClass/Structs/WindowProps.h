#pragma once

#include "Public/PCH.h"

struct FWindowProps
{
	std::string Title = "Window";
	int Height = 100;
	int Width = 100;
	FWindowProps() {}
	FWindowProps(const std::string& inTitle, int inHeight, int inWidth) :
		Title(inTitle),
		Height(inHeight),
		Width(inWidth)
	{

	}
};