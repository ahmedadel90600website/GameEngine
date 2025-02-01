#pragma once

#include <stdint.h>

class IndexBuffer
{
public:

	virtual ~IndexBuffer() {};

	static std::unique_ptr<IndexBuffer> Create(uint32_t sizeInBytes, const uint32_t* const indexData, uint32_t drawType);
	virtual void Bind() const = 0;
	virtual void unBind() const = 0;

protected:

	IndexBuffer() {};
};