#pragma once

#include <Public/Core.h>
#include <stdint.h>

class IndexBuffer
{
public:

	virtual ~IndexBuffer() {};

	static TSharedPtr<IndexBuffer> Create(const uint32_t* const indexData, const uint32_t inCount);
	virtual void Bind() const = 0;
	virtual void UnBind() const = 0;
	virtual uint32_t GetCount() const = 0;

protected:

	IndexBuffer() {};
};