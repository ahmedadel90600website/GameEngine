#include "Public/PCH.h"
#include "Public/Platforms/Rendering/OpenGL/OpenGLRendererAPI.h"
#include "Public/Rendering/VertexArray.h"

// Third party
#include "glad/glad.h"

OpenGLRendererAPI::OpenGLRendererAPI()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void OpenGLRendererAPI::SetClearColor(const glm::vec4& inClearColor) const
{
	glClearColor(inClearColor.r, inClearColor.g, inClearColor.b, inClearColor.a);
}

void OpenGLRendererAPI::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRendererAPI::DrawIndexed(const VertexArray& inVertexArray) const
{
	const std::shared_ptr<IndexBuffer>& indexBuffer = inVertexArray.GetTheIndexBuffer();
	if (indexBuffer.get() == nullptr)
	{
		GameEngine_Assert(false, "OpenGLRendererAPI::DrawIndexed. Index buffer is invalid");
		return;
	}

	glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
}