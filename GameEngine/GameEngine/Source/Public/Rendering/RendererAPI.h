#pragma once

#include "Public/Core.h"
#include "glm/glm.hpp"

class VertexArray;

enum class ERendererAPIType : uint8_t
{
	NONE,
	OPENGL
};

class RendererAPI
{
public:

	virtual ~RendererAPI() {}
	inline static ERendererAPIType GetTheRendererAPIType() { return APIType; }

	virtual void Init() = 0;
	virtual void SetClearColor(const glm::vec4& inClearColor) const = 0;
	virtual void Clear() const = 0;
	virtual void DrawIndexed(const VertexArray& inVertexArray) const = 0;
	virtual void SetViewPortDimensions(uint32_t width, uint32_t height) const = 0;

private:

	static ERendererAPIType APIType;
};