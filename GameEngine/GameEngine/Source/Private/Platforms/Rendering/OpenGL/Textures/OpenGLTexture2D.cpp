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

	glCreateTextures(GL_TEXTURE_2D, 1, &TextureID);
	glTextureStorage2D(TextureID, 1, GL_RGBA8, Width, Height);

	glTextureParameteri(TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(TextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTextureSubImage2D(TextureID, 0, 0, 0, Width, Height, GL_RGBA, GL_UNSIGNED_BYTE, data);

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