#include "Public/PCH.h"
#include "Public/Rendering/Textures/Texture2D.h"
#include "Public/Rendering/RendererAPI.h"
#include "Public/Platforms/Rendering/OpenGL/Textures/OpenGLTexture2D.h"

TSharedPtr<Texture2D> Texture2D::Create(const std::string& texturePath)
{
    const ERendererAPIType rendererAPI = RendererAPI::GetTheRendererAPIType();
    if (rendererAPI == ERendererAPIType::NONE)
    {
        GameEngine_Assert(false, "IndexBuffer::Create, can't create an index buffer with ERendererAPI::NONE.");
        return nullptr;
    }
    else if (rendererAPI == ERendererAPIType::OPENGL)
    {
        return std::make_unique<OpenGLTexture2D>(texturePath);
    }

    GameEngine_Assert(false, "Texture2D::Create, unsupported rendering API.");
    return nullptr;
}