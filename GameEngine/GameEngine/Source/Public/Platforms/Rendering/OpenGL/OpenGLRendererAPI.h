#pragma once
#include "Public/Rendering/RendererAPI.h"

class OpenGLRendererAPI : public RendererAPI
{
public:

	OpenGLRendererAPI();

private:

	void Init() override;
	void SetClearColor(const glm::vec4& inClearColor) const override;
	void Clear() const override;
	void DrawIndexed(const VertexArray& inVertexArray) const override;
	void SetViewPortDimensions(uint32_t width, uint32_t height) const;
};