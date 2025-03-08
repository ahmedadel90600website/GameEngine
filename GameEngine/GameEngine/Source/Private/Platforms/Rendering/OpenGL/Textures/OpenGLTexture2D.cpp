#include "Public/PCH.h"
#include "Public/Platforms/Rendering/OpenGL/Textures/OpenGLTexture2D.h"

//Third party
#include "stb_image/Public/stb_image.h"
#include "glad/glad.h"

OpenGLTexture2D::OpenGLTexture2D(const std::string& texturePath) :
	Path(texturePath)
{
	stbi_set_flip_vertically_on_load(1);
	int width, height, channels;
	stbi_uc* const data = stbi_load(Path.c_str(), &width, &height, &channels, 0);
	GameEngine_Assert(data != nullptr, "OpenGLTexture2D::OpenGLTexture2D, couldn't load the texture.");
	Width = width;
	Height = height;

	uint32_t textureStoreFormat = 0;
	uint32_t textureDrawFormat = 0;
	if (channels == 3)
	{
		textureStoreFormat = GL_RGB8;
		textureDrawFormat = GL_RGB;
	}
	else if (channels == 4)
	{
		textureStoreFormat = GL_RGBA8;
		textureDrawFormat = GL_RGBA;
	}

	GameEngine_Assert(textureStoreFormat != 0 && textureDrawFormat != 0, "OpenGLTexture2D::OpenGLTexture2D, unsupported number of channels for texture.");

	glCreateTextures(GL_TEXTURE_2D, 1, &TextureID);
	glTextureStorage2D(TextureID, 1, textureStoreFormat, Width, Height);

	uint32_t colorInterType = GL_LINEAR;
	glTextureParameteri(TextureID, GL_TEXTURE_MIN_FILTER, colorInterType);
	glTextureParameteri(TextureID, GL_TEXTURE_MAG_FILTER, colorInterType);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTextureSubImage2D(TextureID, 0, 0, 0, Width, Height, textureDrawFormat, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
}

OpenGLTexture2D::~OpenGLTexture2D()
{
	glDeleteTextures(1, &TextureID);
}

void OpenGLTexture2D::Bind(const uint32_t slot) const
{
	glBindTextureUnit(slot, TextureID);
}