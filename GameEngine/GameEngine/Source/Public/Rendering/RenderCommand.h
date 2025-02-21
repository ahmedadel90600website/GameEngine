#pragma once

#include "Public/Rendering/RendererAPI.h"
#include "Public/Core.h"

class RenderCommand
{
public:

	static const TSharedPtr<RendererAPI>& GetTheRendererAPI();

	static void Init();
	inline static void SetClearColor(const glm::vec4& color)
	{
		TheRendererAPI->SetClearColor(color);
	}

	inline static void Clear()
	{
		TheRendererAPI->Clear();
	}

	inline static void DrawIndexed(const VertexArray& vertexArray)
	{
		TheRendererAPI->DrawIndexed(vertexArray);
	}

private:

	static TSharedPtr<RendererAPI> TheRendererAPI;
};