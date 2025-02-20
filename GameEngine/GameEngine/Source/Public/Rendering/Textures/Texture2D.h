#pragma once

#include "TextureBase.h"
#include "Public/Core.h"

#include <string>

class Texture2D : public TextureBase
{
public:

	static TSharedPtr<Texture2D> Create(const std::string& texturePath);
};