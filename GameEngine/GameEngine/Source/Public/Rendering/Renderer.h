#pragma once

#include <stdint.h>

class VertexArray;

class Renderer
{
public:

	static void BeginScene();
	static void EndScene();
	static void Submit(const VertexArray& inVertexArray);
};