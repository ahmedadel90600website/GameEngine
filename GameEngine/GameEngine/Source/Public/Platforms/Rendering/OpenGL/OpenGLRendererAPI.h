#pragma once
#include "Public/Rendering/RendererAPI.h"

class OpenGLRendererAPI : public RendererAPI
{
	void SetClearColor(const glm::vec4& inClearColor) const override;
	void Clear() const override;
	void DrawIndexed(const VertexArray& inVertexArray) const override;
};