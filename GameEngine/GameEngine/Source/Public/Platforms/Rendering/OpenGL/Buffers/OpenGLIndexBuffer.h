#pragma once

#include "Public/Rendering/Buffers/IndexBuffer.h"

class OpenGLIndexBuffer : public IndexBuffer
{
public:

	OpenGLIndexBuffer(uint32_t sizeInBytes, const uint32_t* const indexData, uint32_t drawType);
	virtual ~OpenGLIndexBuffer();

	virtual void Bind() const;
	virtual void unBind() const;

private:

	uint32_t IndexBufferHandle = 0;
};