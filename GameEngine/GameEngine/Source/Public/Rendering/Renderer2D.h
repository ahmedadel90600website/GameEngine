#pragma once
#include "Public/Core.h"

class OrthographicCamera;
class VertexArray;
class ShaderProgram;

class Renderer2D
{
public:

	static void Init();
	static void BeginScene(const OrthographicCamera& orthoCamera);
	static void DrawQuad(const glm::vec4& inColor);
	static void EndScene();

	static void ShutDown();

private:

	struct Renderer2DData
	{
		TSharedPtr<VertexArray> TheVertexArray;
		TSharedPtr<ShaderProgram> TheShaderProgram;
	};

	static Renderer2DData* TheData;
};