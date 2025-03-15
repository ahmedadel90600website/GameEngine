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
#include "Public/Profiler/Instrumentor.h"

TSharedPtr<Renderer::SceneData> Renderer::TheSceneData = TMakeShared<Renderer::SceneData>();
void Renderer::Init()
{
	RENDERER_PROFILE_FUNCTION();

	RenderCommand::Init();
	Renderer2D::Init();
}

void Renderer::BeginScene(const Camera& inCamera)
{
	RENDERER_PROFILE_FUNCTION();

	GameEngine_Assert(TheSceneData != nullptr, "Renderer::BeginScene. TheSceneData was nullptr")
	TheSceneData->ViewProjectionMatrix = inCamera.GetViewProjectionMatrix();
}

void Renderer::EndScene()
{
	RENDERER_PROFILE_FUNCTION();

}

void Renderer::Submit(const VertexArray& inVertexArray, ShaderProgram& inShaderProgram, const glm::mat4& localTransform, const glm::mat4& worldTransform)
{
	RENDERER_PROFILE_FUNCTION();

	GameEngine_Assert(TheSceneData != nullptr, "Renderer::Submit. TheSceneData was nullptr");

	inShaderProgram.Bind();
	inVertexArray.Bind();
	inShaderProgram.SetUniform("u_ViewProjection", TheSceneData->ViewProjectionMatrix);
	inShaderProgram.SetUniform("u_ObjectTransform", localTransform);
	inShaderProgram.SetUniform("u_WorldTransform", worldTransform);
	RenderCommand::DrawIndexed(inVertexArray);
}

void Renderer::SetViewPortDimensions(uint32_t width, uint32_t height)
{
	RENDERER_PROFILE_FUNCTION();

	RenderCommand::SetViewPortDimensions(width, height);
}