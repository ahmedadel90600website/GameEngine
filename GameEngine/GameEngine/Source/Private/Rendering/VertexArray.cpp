#include "Public/PCH.h"
#include "Public/Rendering/VertexArray.h"
#include "Public/Rendering/RendererAPI.h"
#include "Public/Platforms/Rendering/OpenGL/OpenGLVertexArray.h"

std::shared_ptr<VertexArray> VertexArray::Create()
{
	const ERendererAPIType renderAPIType = RendererAPI::GetTheRendererAPIType();
	if (renderAPIType == ERendererAPIType::OPENGL)
	{
		return std::make_shared<OpenGLVertexArray>();
	}

	return nullptr;
}
