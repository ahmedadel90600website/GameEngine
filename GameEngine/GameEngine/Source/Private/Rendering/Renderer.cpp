#include "Public/PCH.h"
#include "Public/Rendering/Renderer.h"
#include "Public/Rendering/RendererAPI.h"
#include "Public/Rendering/Cameras/Camera.h"
#include "Public/Rendering/ShaderProgram.h"
#include "Public/Rendering/VertexArray.h"
#include "Public/Platforms/Rendering/OpenGL/OpenGLShaderProgram.h"
#include "Public/log.h"
#include "Public/Core.h"

TSharedPtr<Renderer::SceneData> Renderer::TheSceneData = std::make_shared<Renderer::SceneData>();
void Renderer::BeginScene(const Camera& inCamera)
{
	GameEngine_Assert(TheSceneData != nullptr, "Renderer::BeginScene. TheSceneData was nullptr")
	TheSceneData->ViewProjectionMatrix = inCamera.GetViewProjectionMatrix();
}

void Renderer::EndScene()
{
}

void Renderer::Submit(const VertexArray& inVertexArray, ShaderProgram& inShaderProgram, const glm::mat4& transform)
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
	openGLShaderProgramRaw->UploadUniform("u_ObjectTransform", transform);
	if (const TSharedPtr<RendererAPI>& rendererAPI = RendererAPI::GetTheRendererAPI())
	{
		rendererAPI->DrawIndexed(inVertexArray);
	}
}