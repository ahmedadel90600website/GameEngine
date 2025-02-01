#include "Public/PCH.h"
#include "Public/Rendering/Buffers/IndexBuffer.h"
#include "Public/Rendering/Renderer.h"
#include "Public/Platforms/Rendering/OpenGL/Buffers/OpenGLIndexBuffer.h"

std::unique_ptr<IndexBuffer> IndexBuffer::Create(uint32_t sizeInBytes, const uint32_t* const indexData, uint32_t drawType)
{
    const ERendererAPI rendererAPI = Renderer::GetRendererAPI();
    if (rendererAPI == ERendererAPI::NONE)
    {
        GameEngine_Assert(false, "IndexBuffer::Create, can't create an index buffer with ERendererAPI::NONE.");
        return nullptr;
    }
    else if (rendererAPI == ERendererAPI::OPENGL)
    {
        return std::make_unique<OpenGLIndexBuffer>(sizeInBytes, indexData, drawType);
    }

    GameEngine_Assert(false, "IndexBuffer::Create, unsupported rendering API.");
    return nullptr;
}