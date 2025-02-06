#include "Public/PCH.h"
#include "Public/Rendering/Buffers/VertexBuffer.h"
#include "Public/Rendering/Renderer.h"
#include "Public/Platforms/Rendering/OpenGL/Buffers/OpenGLVertexBuffer.h"

std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32_t sizeInBytes, const float* const vertexData, uint32_t drawType)
{
    const ERendererAPI rendererAPI = Renderer::GetRendererAPI(); 
    if (rendererAPI == ERendererAPI::NONE)
    {
        GameEngine_Assert(false, "VertexBuffer::Create, can't create a vertex buffer with ERendererAPI::NONE.");
        return nullptr;
    }
    else if (rendererAPI == ERendererAPI::OPENGL)
    {
        return std::make_shared<OpenGLVertexBuffer>(sizeInBytes, vertexData, drawType);
    }

    GameEngine_Assert(false, "VertexBuffer::Create, unsupported rendering API.");
    return nullptr;
}
