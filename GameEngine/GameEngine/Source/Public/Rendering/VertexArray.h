#pragma once

#include "Public/Rendering/Buffers/VertexBuffer.h"
#include "Public/Rendering/Buffers/IndexBuffer.h"

#include <memory>
#include <vector>

class VertexArray
{
public:

	static std::shared_ptr<VertexArray> Create();

	virtual void Bind() = 0;
	virtual void UnBind() = 0;

	virtual void BindVertexBuffer(const std::shared_ptr<VertexBuffer>& inVertexBuffer) = 0;
	virtual void BindIndexBuffer(const std::shared_ptr<IndexBuffer>& inIndexBuffer) = 0;

	inline virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
	inline virtual const std::shared_ptr<IndexBuffer>& GetTheIndexBuffer() const = 0;
};