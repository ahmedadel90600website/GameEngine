#include "Public/PCH.h"
#include "Public/Platforms/Rendering/OpenGL/OpenGLRendererAPI.h"
#include "Public/Rendering/VertexArray.h"
#include "Public/Core.h"
#include "Public/Profiler/Instrumentor.h"

// Third party
#include "glad/glad.h"

OpenGLRendererAPI::OpenGLRendererAPI()
{
}

void OpenGLRendererAPI::Init()
{
	RENDERER_PROFILE_FUNCTION();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
}

void OpenGLRendererAPI::SetClearColor(const glm::vec4& inClearColor) const
{
	RENDERER_PROFILE_FUNCTION();

	glClearColor(inClearColor.r, inClearColor.g, inClearColor.b, inClearColor.a);
}

void OpenGLRendererAPI::Clear() const
{
	RENDERER_PROFILE_FUNCTION();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::DrawIndexed(const VertexArray& inVertexArray) const
{
	RENDERER_PROFILE_FUNCTION();

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
	RENDERER_PROFILE_FUNCTION();

	glViewport(0, 0, width, height);
}