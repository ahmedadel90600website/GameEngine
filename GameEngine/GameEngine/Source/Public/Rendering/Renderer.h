#pragma once

#include <stdint.h>

enum class ERendererAPI : uint8_t
{
	NONE,
	OPENGL
};

class Renderer
{
public:

	inline static ERendererAPI GetRendererAPI() { return RendererAPI; }

private:

	static ERendererAPI RendererAPI;
};