#pragma once

#include "Public/Rendering/Buffers/VertexBuffer.h"
#include "Public/Rendering/Buffers/BufferLayout.h"

class OpenGLVertexBuffer : public VertexBuffer
{
public:

	OpenGLVertexBuffer(uint32_t sizeInBytes, const float* const vertexData);
	virtual ~OpenGLVertexBuffer();

	void Bind() const override;
	void UnBind() const override;
	inline const BufferLayout& GetLayout() const override { return Layout; }
	void SetLayout(const BufferLayout& inLayput) override;

private:

	BufferLayout Layout;
	uint32_t VertexBufferHandle = 0;
};