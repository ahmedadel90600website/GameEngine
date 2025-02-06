#pragma once

#include <stdint.h>

class IndexBuffer
{
public:

	virtual ~IndexBuffer() {};

	static std::shared_ptr<IndexBuffer> Create(const uint32_t* const indexData, const uint32_t inCount, uint32_t drawType);
	virtual void Bind() const = 0;
	virtual void UnBind() const = 0;
	virtual uint32_t GetCount() const = 0;

protected:

	IndexBuffer() {};
};