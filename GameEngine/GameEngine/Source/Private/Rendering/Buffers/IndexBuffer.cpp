#include "Public/PCH.h"
#include "Public/Rendering/Buffers/IndexBuffer.h"
#include "Public/Rendering/RendererAPI.h"
#include "Public/Platforms/Rendering/OpenGL/Buffers/OpenGLIndexBuffer.h"

std::shared_ptr<IndexBuffer> IndexBuffer::Create(const uint32_t* const indexData, const uint32_t count, uint32_t drawType)
{
    const ERendererAPIType rendererAPI = RendererAPI::GetTheRendererAPIType();
    if (rendererAPI == ERendererAPIType::NONE)
    {
        GameEngine_Assert(false, "IndexBuffer::Create, can't create an index buffer with ERendererAPI::NONE.");
        return nullptr;
    }
    else if (rendererAPI == ERendererAPIType::OPENGL)
    {
        return std::make_unique<OpenGLIndexBuffer>(indexData, count, drawType);
    }

    GameEngine_Assert(false, "IndexBuffer::Create, unsupported rendering API.");
    return nullptr;
}