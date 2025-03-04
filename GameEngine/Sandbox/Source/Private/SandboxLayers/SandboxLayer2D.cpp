#include "Public/PCH.h"

#include "Public/SandboxLayers/SandboxLayer2D.h"
#include "Public/Core.h"

// Game Engine
#include "Public/Rendering/ShaderProgram.h"
#include "Public/Platforms/Rendering/OpenGL/OpenGLShaderProgram.h"
#include "Public/Rendering/VertexArray.h"
#include "Public/Rendering/Renderer.h"
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

	float vertices[] =
	{
		-0.5, -0.5, 0.0f,
		 0.5, -0.5, 0.0f,
		 0.5,  0.5, 0.0f,
		-0.5,  0.5, 0.0f
	};

	TheShaderProgram = ShaderProgram::Create("Content/Shaders/FlatColor.glsl");
	GameEngine_Assert(TheShaderProgram != nullptr, "TheShaderProgram failed to be created.");

	TheVertexArray = VertexArray::Create();
	GameEngine_Assert(TheVertexArray != nullptr, "TheVertexArray failed to be created.");

	TSharedPtr<VertexBuffer> vertexBuffer = VertexBuffer::Create(sizeof(vertices), vertices);
	GameEngine_Assert(vertexBuffer != nullptr, "vertexBuffer failed to be created.");

	std::vector<BufferElement> bufferElements;
	bufferElements.emplace_back("a_Position", EShaderDataType::FLOAT3, false);
	BufferLayout layout(bufferElements);
	vertexBuffer->SetLayout(layout);

	uint32_t indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	TSharedPtr<IndexBuffer> IndexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	GameEngine_Assert(IndexBuffer != nullptr, "IndexBuffer failed to be created.");

	TheVertexArray->BindVertexBuffer(vertexBuffer);
	TheVertexArray->BindIndexBuffer(IndexBuffer);
}

void SandboxLayer2D::Tick(const float deltaTime)
{
	const TSharedPtr<RendererAPI>& renderingAPI = RenderCommand::GetTheRendererAPI();
	if (renderingAPI == nullptr)
	{
		return;
	}


	TSharedPtr<OpenGLShaderProgram> openGLShaderProgram = std::dynamic_pointer_cast<OpenGLShaderProgram>(TheShaderProgram);
	if (openGLShaderProgram == nullptr)
	{
		return;
	}

	openGLShaderProgram->Bind();
	RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
	RenderCommand::Clear();
	SceneCamera->Tick(deltaTime);

	Renderer::BeginScene(*SceneCamera);
	openGLShaderProgram->UploadUniform("u_TheColor", ObjectColor);

	Renderer::Submit(*TheVertexArray, *TheShaderProgram);
	TheShaderProgram->UnBind();
	Renderer::EndScene();
}

void SandboxLayer2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square_Color", glm::value_ptr(ObjectColor));
	ImGui::End();
}