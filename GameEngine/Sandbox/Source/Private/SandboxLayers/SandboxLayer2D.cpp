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
#include "Public/Rendering/Textures/Texture2D.h"


// Third party
#include "ImGui/imgui.h"
#include "glm/gtc/type_ptr.hpp"

SandboxLayer2D::SandboxLayer2D()
{
	SceneCamera = std::make_shared<OrthographicCamera>(-1.0f, 1.0f, -1.0f, 1.0f);
	GameEngine_Assert(SceneCamera != nullptr, "SandboxLayer2D::SandboxLayer2D. Camera failed to be created.");

	SandboxTexture2D = Texture2D::Create("Content/Textures/CJ.png");
	if (SandboxTexture2D == nullptr)
	{
		Application_LOG(error, "SandboxLayer2D::SandboxLayer2D(). texture failed to be created.");
		return;
	}
}

void SandboxLayer2D::Tick(const float deltaTime)
{
	RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
	RenderCommand::Clear();
	SceneCamera->Tick(deltaTime);

	Application_LOG(info, "{0}", sizeof(glm::vec3));
	Renderer2D::BeginScene(*SceneCamera);
	Renderer2D::DrawQuad(glm::vec4(ObjectColor.x, ObjectColor.y, ObjectColor.z, 1.0f), glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.0f)) * glm::mat4(glm::quat(glm::lowp_fvec3(0.0f, 0.0f, glm::radians(45.0f)))));
	Renderer2D::DrawQuad(*SandboxTexture2D, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.2f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.f)));
	Renderer2D::EndScene();
}

void SandboxLayer2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square_Color", glm::value_ptr(ObjectColor));
	ImGui::End();
}