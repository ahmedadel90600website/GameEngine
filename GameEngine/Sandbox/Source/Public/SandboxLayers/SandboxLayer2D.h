#pragma once

#include "Public/Layers/LayerBase.h"
#include "glm/glm.hpp"
#include "glm/detail/type_quat.hpp"

class ShaderProgram;
class VertexArray;
class Texture2D;
class OrthographicCamera;

class SandboxLayer2D : public LayerBase
{
public:

	SandboxLayer2D();

private:

	void Tick(const float deltaTime) override;
	void OnImGuiRender() override;

	glm::quat ObjectsRotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
	glm::vec3 ObjectLocation = glm::vec3(0.0f);
	glm::vec3 ObjectColor = glm::vec3(1.0f, 0.0f, 0.0f);
	TSharedPtr<OrthographicCamera> SceneCamera = nullptr;
	TSharedPtr<Texture2D> SandboxTexture2D = nullptr;
	TSharedPtr<Texture2D> WhiteTexture2D = nullptr;
};