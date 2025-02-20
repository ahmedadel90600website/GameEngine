#pragma once

#include "Public/Rendering/Textures/Texture2D.h"
#include "Public/Core.h"

class OpenGLTexture2D : public Texture2D
{
public:

	OpenGLTexture2D(const std::string& texturePath);
	~OpenGLTexture2D();

	inline uint32_t GetWidth() const override { return Width; }
	inline uint32_t GetHeight() const override { return Height; }
	void Bind(const uint32_t slot = 0) const override;

private:

	std::string Path;
	uint32_t TextureID = 0;
	uint32_t Width = 0;
	uint32_t Height = 0;
};