#pragma once

#include "Public/Rendering/VertexArray.h"
#include "Public/Core.h"
#include <stdint.h>

class OpenGLVertexArray : public VertexArray
{
public:

	OpenGLVertexArray();
	virtual ~OpenGLVertexArray();

	void Bind() const override;
	void UnBind() const override;

	void BindVertexBuffer(const TSharedPtr<VertexBuffer>& inVertexBuffer) override;
	void BindIndexBuffer(const TSharedPtr<IndexBuffer>& inIndexBuffer) override;

	inline const std::vector<TSharedPtr<VertexBuffer>>& GetVertexBuffers() const override { return VertexBuffers; };
	inline const TSharedPtr<IndexBuffer>& GetTheIndexBuffer() const override { return TheIndexBuffer; };

private:

	std::vector<TSharedPtr<VertexBuffer>> VertexBuffers;
	TSharedPtr<IndexBuffer> TheIndexBuffer;
	uint32_t Handle;
};