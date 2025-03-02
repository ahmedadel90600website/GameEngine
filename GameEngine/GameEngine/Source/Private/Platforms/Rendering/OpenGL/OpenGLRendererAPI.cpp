#include "Public/PCH.h"
#include "Public/Platforms/Rendering/OpenGL/OpenGLRendererAPI.h"
#include "Public/Rendering/VertexArray.h"
#include "Public/Core.h"

// Third party
#include "glad/glad.h"

OpenGLRendererAPI::OpenGLRendererAPI()
{
}

void OpenGLRendererAPI::Init()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
	const TSharedPtr<IndexBuffer>& indexBuffer = inVertexArray.GetTheIndexBuffer();
	if (indexBuffer.get() == nullptr)
	{
		GameEngine_Assert(false, "OpenGLRendererAPI::DrawIndexed. Index buffer is invalid");
		return;
	}

	glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void OpenGLRendererAPI::SetViewPortDimensions(uint32_t width, uint32_t height) const
{
	glViewport(0, 0, width, height);
}