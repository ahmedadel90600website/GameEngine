#pragma once

#include <memory>
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

	static const std::shared_ptr<RendererAPI>& GetTheRendererAPI();
	static ERendererAPIType GetTheRendererAPIType();

	virtual void SetClearColor(const glm::vec4& inClearColor) const = 0;
	virtual void Clear() const = 0;
	virtual void DrawIndexed(const VertexArray& inVertexArray) const = 0;

private:

	static std::shared_ptr<RendererAPI> TheRendererAPI;
	static ERendererAPIType APIType;
};