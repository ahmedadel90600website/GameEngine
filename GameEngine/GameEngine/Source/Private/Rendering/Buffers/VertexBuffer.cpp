#include "Public/PCH.h"
#include "Public/Rendering/Buffers/VertexBuffer.h"
#include "Public/Rendering/RendererAPI.h"
#include "Public/Platforms/Rendering/OpenGL/Buffers/OpenGLVertexBuffer.h"

std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32_t sizeInBytes, const float* const vertexData, uint32_t drawType)
{
    const ERendererAPIType rendererAPI = RendererAPI::GetTheRendererAPIType();
    if (rendererAPI == ERendererAPIType::NONE)
    {
        GameEngine_Assert(false, "VertexBuffer::Create, can't create a vertex buffer with ERendererAPI::NONE.");
        return nullptr;
    }
    else if (rendererAPI == ERendererAPIType::OPENGL)
    {
        return std::make_shared<OpenGLVertexBuffer>(sizeInBytes, vertexData, drawType);
    }

    GameEngine_Assert(false, "VertexBuffer::Create, unsupported rendering API.");
    return nullptr;
}
