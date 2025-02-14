#include "Public/PCH.h"
#include "Public/Rendering/Renderer.h"
#include "Public/Rendering/RendererAPI.h"
#include "Public/Rendering/Cameras/Camera.h"
#include "Public/Rendering/ShaderProgram.h"
#include "Public/Rendering/VertexArray.h"

std::shared_ptr<Renderer::SceneData> Renderer::TheSceneData = std::make_shared<Renderer::SceneData>();
void Renderer::BeginScene(const Camera& inCamera)
{
	GameEngine_Assert(TheSceneData != nullptr, "Renderer::BeginScene. TheSceneData was nullptr")
	TheSceneData->ViewProjectionMatrix = inCamera.GetViewProjectionMatrix();
}

void Renderer::EndScene()
{
}

void Renderer::Submit(const VertexArray& inVertexArray, const ShaderProgram& inShaderProgram, const glm::mat4& transform)
{
	GameEngine_Assert(TheSceneData != nullptr, "Renderer::Submit. TheSceneData was nullptr")

	inShaderProgram.Bind();
	inVertexArray.Bind();
	inShaderProgram.UploadUniform("u_ViewProjection", TheSceneData->ViewProjectionMatrix);
	inShaderProgram.UploadUniform("u_ObjectTransform", transform);
	if (const std::shared_ptr<RendererAPI>& rendererAPI = RendererAPI::GetTheRendererAPI())
	{
		rendererAPI->DrawIndexed(inVertexArray);
	}
}