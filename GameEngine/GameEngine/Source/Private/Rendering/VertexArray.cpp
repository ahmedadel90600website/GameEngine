#include "Public/PCH.h"
#include "Public/Rendering/VertexArray.h"
#include "Public/Rendering/Renderer.h"
#include "Public/Platforms/Rendering/OpenGL/OpenGLVertexArray.h"

std::shared_ptr<VertexArray> VertexArray::Create()
{
	const ERendererAPI renderAPIType = Renderer::GetRendererAPI();
	if (renderAPIType == ERendererAPI::OPENGL)
	{
		return std::make_shared<OpenGLVertexArray>();
	}

	return nullptr;
}
