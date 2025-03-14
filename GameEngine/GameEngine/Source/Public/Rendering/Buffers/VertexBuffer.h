#pragma once

#include "Public/Core.h"
#include <stdint.h>

class BufferLayout;

class VertexBuffer
{
public:

	virtual ~VertexBuffer() {};

	static TSharedPtr<VertexBuffer> Create(uint32_t sizeInBytes, const float* const vertexData);
	virtual void Bind() const = 0;
	virtual void UnBind() const = 0;
	virtual const BufferLayout& GetLayout() const = 0;
	virtual void SetLayout(const BufferLayout& inLayout) = 0;

protected:

	VertexBuffer() {};
};