#pragma once

#include "Public/Core.h"
#include <stdint.h>
#include <Public/Rendering/RenderCommand.h>

// Third party
#include "glm/glm.hpp"

class VertexArray;
class Camera;
class ShaderProgram;

class Renderer
{
private:

	struct SceneData
	{
		glm::mat4 ViewProjectionMatrix;
	};

public:

	static void Init();
	static void BeginScene(const Camera& inCamera);
	static void EndScene();
	static void Submit(const VertexArray& inVertexArray, ShaderProgram& inShaderProgram, const glm::mat4& localtransform = glm::mat4(1.0f), const glm::mat4& worldTransform = glm::mat4(1.0f));
	static void SetViewPortDimensions(uint32_t width, uint32_t height);

	static TSharedPtr<SceneData> TheSceneData;
};