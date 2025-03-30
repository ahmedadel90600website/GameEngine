#pragma once
#include "Public/Core.h"

class OrthographicCamera;
class VertexArray;
class ShaderProgram;
class Texture2D;

class Renderer2D
{
public:

	static void Init();
	static void BeginScene(const OrthographicCamera& orthoCamera);
	static void DrawQuad(const glm::vec4& inColor, const glm::mat4& localTransform = glm::mat4(1.0f), const glm::mat4& worldTransform = glm::mat4(1.0f), const float textureMultiplier = 1.0f);
	static void DrawQuad(const Texture2D& intexture, const glm::mat4& localTransform = glm::mat4(1.0f), const glm::mat4& worldTransform = glm::mat4(1.0f),
		const glm::vec4& inTintColor = glm::vec4(1.0f), const float textureMultiplier = 1.0f);
	static void EndScene();

	static void ShutDown();

private:

	struct Renderer2DData
	{
		TSharedPtr<VertexArray> TheVertexArray;
		TSharedPtr<ShaderProgram> TextureShaderProgram;
	};

	static Renderer2DData* TheData;
};