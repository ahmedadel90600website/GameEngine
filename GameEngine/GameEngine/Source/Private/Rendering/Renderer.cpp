#include "Public/PCH.h"
#include "Public/Rendering/Renderer.h"
#include "Public/Rendering/RendererAPI.h"

void Renderer::BeginScene()
{
}

void Renderer::EndScene()
{
}

void Renderer::Submit(const VertexArray& inVertexArray)
{
	if (const std::shared_ptr<RendererAPI>& rendererAPI = RendererAPI::GetTheRendererAPI())
	{
		rendererAPI->DrawIndexed(inVertexArray);
	}
}