#pragma once

#include "Public/Rendering/Textures/Texture2D.h"
#include "Public/Core.h"

#include "glad/glad.h"

class OpenGLTexture2D : public Texture2D
{
public:

	OpenGLTexture2D(const uint32_t width, const uint32_t height, void* data);
	OpenGLTexture2D(const std::string& texturePath);
	~OpenGLTexture2D();

	inline uint32_t GetWidth() const override { return Width; }
	inline uint32_t GetHeight() const override { return Height; }
	void Bind(const uint32_t slot = 0) const override;
	void UnBind(const uint32_t slot = 0) const;
	
	void SetData(void* data);

private:
	
	void CreateAnDSetupTexture(const uint32_t width, const uint32_t height, const uint32_t storeFormat, const uint32_t drawFormat, void* data);

	std::string Path;
	uint32_t TextureID = 0;
	uint32_t Width = 0;
	uint32_t Height = 0;
	uint32_t TextureStoreFormat = GL_RGBA8;
	uint32_t TextureDrawFormat = GL_RGBA;
};