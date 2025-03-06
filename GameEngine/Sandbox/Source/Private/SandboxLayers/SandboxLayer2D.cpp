#include "Public/PCH.h"

#include "Public/SandboxLayers/SandboxLayer2D.h"
#include "Public/Core.h"

// Game Engine
#include "Public/Rendering/ShaderProgram.h"
#include "Public/Platforms/Rendering/OpenGL/OpenGLShaderProgram.h"
#include "Public/Rendering/VertexArray.h"
#include "Public/Rendering/Renderer.h"
#include "Public/Rendering/Renderer2D.h"
#include "Public/Rendering/RenderCommand.h"
#include "Public/Rendering/Cameras/OrthographicCamera.h"
#include "Public/Rendering/Buffers/VertexBuffer.h"
#include "Public/Rendering/Buffers/BufferLayout.h"
#include "Public/Rendering/Buffers/IndexBuffer.h"


// Third party
#include "ImGui/imgui.h"
#include "glm/gtc/type_ptr.hpp"

SandboxLayer2D::SandboxLayer2D()
{
	SceneCamera = std::make_shared<OrthographicCamera>(-1.0f, 1.0f, -1.0f, 1.0f);
	GameEngine_Assert(SceneCamera != nullptr, "Camera failed to be created.");
}

void SandboxLayer2D::Tick(const float deltaTime)
{
	RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
	RenderCommand::Clear();
	SceneCamera->Tick(deltaTime);

	Renderer2D::BeginScene(*SceneCamera);
	Renderer2D::DrawQuad(glm::vec4(ObjectColor.x, ObjectColor.y, ObjectColor.z, 1.0f));
	Renderer2D::EndScene();
}

void SandboxLayer2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square_Color", glm::value_ptr(ObjectColor));
	ImGui::End();
}