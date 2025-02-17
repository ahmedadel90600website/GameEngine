#pragma once

#include <stdint.h>

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

	static void BeginScene(const Camera& inCamera);
	static void EndScene();
	static void Submit(const VertexArray& inVertexArray, ShaderProgram& inShaderProgram, const glm::mat4& transform = glm::mat4(1.0f));

	static std::shared_ptr<SceneData> TheSceneData;
};