#pragma once

#include <stdint.h>

class VertexBuffer
{
public:

	virtual ~VertexBuffer() {};

	static std::unique_ptr<VertexBuffer> Create(uint32_t sizeInBytes, const float* const vertexData, uint32_t drawType);
	virtual void Bind() const = 0;
	virtual void unBind() const = 0;

protected:

	VertexBuffer() {};
};