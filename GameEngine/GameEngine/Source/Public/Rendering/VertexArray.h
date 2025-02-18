#pragma once

#include "Public/Rendering/Buffers/VertexBuffer.h"
#include "Public/Rendering/Buffers/IndexBuffer.h"
#include "Public/Core.h"

#include <vector>

class VertexArray
{
public:

	static TSharedPtr<VertexArray> Create();

	virtual ~VertexArray() {}

	virtual void Bind() const = 0;
	virtual void UnBind() const = 0;

	virtual void BindVertexBuffer(const TSharedPtr<VertexBuffer>& inVertexBuffer) = 0;
	virtual void BindIndexBuffer(const TSharedPtr<IndexBuffer>& inIndexBuffer) = 0;

	inline virtual const std::vector<TSharedPtr<VertexBuffer>>& GetVertexBuffers() const = 0;
	inline virtual const TSharedPtr<IndexBuffer>& GetTheIndexBuffer() const = 0;
};