#include "Public/PCH.h"
#include "Public/Rendering/Buffers/VertexBuffer.h"
#include "Public/Rendering/RendererAPI.h"
#include "Public/Platforms/Rendering/OpenGL/Buffers/OpenGLVertexBuffer.h"
#include "Public/Core.h"

TSharedPtr<VertexBuffer> VertexBuffer::Create(uint32_t sizeInBytes, const float* const vertexData)
{
    const ERendererAPIType rendererAPI = RendererAPI::GetTheRendererAPIType();
    if (rendererAPI == ERendererAPIType::NONE)
    {
        GameEngine_Assert(false, "VertexBuffer::Create, can't create a vertex buffer with ERendererAPI::NONE.");
        return nullptr;
    }
    else if (rendererAPI == ERendererAPIType::OPENGL)
    {
        return TMakeShared<OpenGLVertexBuffer>(sizeInBytes, vertexData);
    }

    GameEngine_Assert(false, "VertexBuffer::Create, unsupported rendering API.");
    return nullptr;
}
