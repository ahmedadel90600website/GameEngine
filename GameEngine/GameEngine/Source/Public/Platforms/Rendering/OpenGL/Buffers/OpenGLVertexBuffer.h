#pragma once

#include "Public/Rendering/Buffers/VertexBuffer.h"

class OpenGLVertexBuffer : public VertexBuffer
{
public:

	OpenGLVertexBuffer(uint32_t sizeInBytes, const float* const vertexData, uint32_t drawType);
	virtual ~OpenGLVertexBuffer();

	virtual void Bind() const;
	virtual void unBind() const;

private:

	uint32_t VertexBufferHandle = 0;
};