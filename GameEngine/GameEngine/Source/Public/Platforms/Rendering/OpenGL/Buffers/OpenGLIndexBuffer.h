#pragma once

#include "Public/Rendering/Buffers/IndexBuffer.h"

class OpenGLIndexBuffer : public IndexBuffer
{
public:

	OpenGLIndexBuffer(const uint32_t* const indexData, const uint32_t inCount);
	virtual ~OpenGLIndexBuffer();

	virtual void Bind() const;
	virtual void UnBind() const;
	inline uint32_t GetCount() const override { return Count; }

private:

	uint32_t IndexBufferHandle = 0;
	uint32_t Count = 0;
};