#pragma once

#include "Public/Rendering/VertexArray.h"
#include <stdint.h>

class OpenGLVertexArray : public VertexArray
{
public:

	OpenGLVertexArray();

	void Bind() override;
	void UnBind() override;

	void BindVertexBuffer(const std::shared_ptr<VertexBuffer>& inVertexBuffer) override;
	void BindIndexBuffer(const std::shared_ptr<IndexBuffer>& inIndexBuffer) override;

	inline const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return VertexBuffers; };
	inline const std::shared_ptr<IndexBuffer>& GetTheIndexBuffer() const override { return TheIndexBuffer; };

private:

	std::vector<std::shared_ptr<VertexBuffer>> VertexBuffers;
	std::shared_ptr<IndexBuffer> TheIndexBuffer;
	uint32_t Handle;
};