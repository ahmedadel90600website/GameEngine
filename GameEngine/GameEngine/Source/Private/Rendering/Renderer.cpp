#include "Public/PCH.h"
#include "Public/Rendering/Renderer.h"
#include "Public/Rendering/Renderer2D.h"
#include "Public/Rendering/RenderCommand.h"
#include "Public/Rendering/Cameras/Camera.h"
#include "Public/Rendering/ShaderProgram.h"
#include "Public/Rendering/VertexArray.h"
#include "Public/Platforms/Rendering/OpenGL/OpenGLShaderProgram.h"
#include "Public/log.h"
#include "Public/Core.h"

TSharedPtr<Renderer::SceneData> Renderer::TheSceneData = std::make_shared<Renderer::SceneData>();
void Renderer::Init()
{
	RenderCommand::Init();
	Renderer2D::Init();
}

void Renderer::BeginScene(const Camera& inCamera)
{
	GameEngine_Assert(TheSceneData != nullptr, "Renderer::BeginScene. TheSceneData was nullptr")
	TheSceneData->ViewProjectionMatrix = inCamera.GetViewProjectionMatrix();
}

void Renderer::EndScene()
{
}

void Renderer::Submit(const VertexArray& inVertexArray, ShaderProgram& inShaderProgram, const glm::mat4& localTransform, const glm::mat4& worldTransform)
{
	GameEngine_Assert(TheSceneData != nullptr, "Renderer::Submit. TheSceneData was nullptr");

	OpenGLShaderProgram* const openGLShaderProgramRaw = dynamic_cast<OpenGLShaderProgram*>(&inShaderProgram);
	if (openGLShaderProgramRaw == nullptr)
	{
		GameEngine_LOG(error, "No OpenGL shader created");
		return;
	}

	inShaderProgram.Bind();
	inVertexArray.Bind();
	openGLShaderProgramRaw->UploadUniform("u_ViewProjection", TheSceneData->ViewProjectionMatrix);
	openGLShaderProgramRaw->UploadUniform("u_ObjectTransform", localTransform);
	openGLShaderProgramRaw->UploadUniform("u_WorldTransform", worldTransform);
	RenderCommand::DrawIndexed(inVertexArray);
}

void Renderer::SetViewPortDimensions(uint32_t width, uint32_t height)
{
	RenderCommand::SetViewPortDimensions(width, height);
}