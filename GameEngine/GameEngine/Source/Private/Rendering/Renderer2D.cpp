#include "public/PCH.h"

#include "Public/Rendering/VertexArray.h"
#include "Public/Rendering/RenderCommand.h"
#include "Public/Rendering/Buffers/BufferLayout.h"
#include "Public/Rendering/ShaderProgram.h"
#include "Public/Rendering/Renderer2D.h"
#include "Public/Rendering/Textures/Texture2D.h"
#include "Public/Rendering/Cameras/OrthographicCamera.h"
#include "Public/Platforms/Rendering/OpenGL/OpenGLShaderProgram.h"
#include "Public/Profiler/Instrumentor.h"

Renderer2D::Renderer2DData* Renderer2D::TheData = nullptr;

void Renderer2D::Init()
{
	RENDERER_PROFILE_FUNCTION();

	TheData = new Renderer2D::Renderer2DData();
	if (TheData == nullptr)
	{
		GameEngine_LOG(error, "Renderer2D::Init(). TheData failed to be created.");
		return;
	}

	float vertices[] =
	{
		-0.5, -0.5, 0.0f, 0.0f, 0.0f,
		 0.5, -0.5, 0.0f, 1.0f, 0.0f,
		 0.5,  0.5, 0.0f, 1.0f, 1.0f,
		-0.5,  0.5, 0.0f, 0.0f, 1.0f
	};

	TSharedPtr<ShaderProgram>& textureShaderProgram = TheData->TextureShaderProgram;
	textureShaderProgram = ShaderProgram::Create("Content/Shaders/SandboxShader.glsl");
	if (textureShaderProgram == nullptr)
	{
		GameEngine_LOG(error, "Renderer2D::Init(). textureShaderProgram failed to be created.");
		return;
	}

	textureShaderProgram->SetUniform("u_TextureSlot", 0);
	textureShaderProgram->SetUniform("u_TextureMultiplier", 1.0f);

	TSharedPtr<VertexArray>& vertexArray = TheData->TheVertexArray;
	vertexArray = VertexArray::Create();
	if (vertexArray == nullptr)
	{
		GameEngine_LOG(error, "Renderer2D::Init(). vertexArray failed to be created.");
		return;
	}

	TSharedPtr<VertexBuffer> vertexBuffer = VertexBuffer::Create(sizeof(vertices), vertices);
	if (vertexBuffer == nullptr)
	{
		GameEngine_LOG(error, "Renderer2D::Init(). vertexBuffer failed to be created.");
		return;
	}

	uint32_t indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	TSharedPtr<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	if (indexBuffer == nullptr)
	{
		GameEngine_LOG(error, "Renderer2D::Init(). IndexBuffer failed to be created.");
		return;
	}

	std::vector<BufferElement> bufferElements;
	bufferElements.emplace_back("a_Position", EShaderDataType::FLOAT3, false);
	bufferElements.emplace_back("a_TextureCoordinates", EShaderDataType::FLOAT2, false);
	BufferLayout layout(bufferElements);
	vertexBuffer->SetLayout(layout);

	VertexArray& vertexArrayRef = *vertexArray.get();
	vertexArrayRef.BindVertexBuffer(vertexBuffer);
	vertexArrayRef.BindIndexBuffer(indexBuffer);
}

void Renderer2D::BeginScene(const OrthographicCamera& orthoCamera)
{
	RENDERER_PROFILE_FUNCTION();

	ShaderProgram* const textureShaderProgram = TheData->TextureShaderProgram.get();
	if (textureShaderProgram == nullptr)
	{
		GameEngine_LOG(error, "Renderer2D::BeginScene. textureShaderProgram nullptr.");
		return;
	}

	ShaderProgram& textureShaderProgramRef = *textureShaderProgram;
	textureShaderProgramRef.Bind();
	textureShaderProgramRef.SetUniform("u_ViewProjection", orthoCamera.GetViewProjectionMatrix());
}

void Renderer2D::DrawQuad(const glm::vec4& inColor, const glm::mat4& localTransform, const glm::mat4& worldTransform, const float textureMultiplier)
{
	RENDERER_PROFILE_FUNCTION();

	const TSharedPtr<VertexArray>& vertextArrayShared = TheData->TheVertexArray;
	const VertexArray* const vertextArray = vertextArrayShared.get();
	if (vertextArray == nullptr)
	{
		GameEngine_LOG(error, "Renderer2D::DrawQuad(). vertextArrayis not valid.");
		return;
	}

	const TSharedPtr<ShaderProgram>& flatColorshaderProgramShared = TheData->TextureShaderProgram;
	ShaderProgram* const shaderProgram = flatColorshaderProgramShared.get();
	if (shaderProgram == nullptr)
	{
		GameEngine_LOG(error, "Renderer2D::DrawQuad(). shaderProgram not valid.");
		return;
	}

	ShaderProgram& shaderProgramRef = *shaderProgram;
	const VertexArray& vertextArrayRef = *vertextArray;

	vertextArrayRef.Bind();
	shaderProgramRef.Bind();
	shaderProgramRef.SetUniform("u_TheColor", inColor);
	shaderProgramRef.SetUniform("u_ObjectTransform", localTransform);
	shaderProgramRef.SetUniform("u_TextureMultiplier", textureMultiplier);
	shaderProgramRef.SetUniform("u_WorldTransform", worldTransform);
	RenderCommand::DrawIndexed(vertextArrayRef);}

void Renderer2D::DrawQuad(const Texture2D& intexture, const glm::mat4& localTransform, const glm::mat4& worldTransform, const glm::vec4& inTintColor, const float textureMultiplier)
{
	RENDERER_PROFILE_FUNCTION();

	const TSharedPtr<VertexArray>& vertextArrayShared = TheData->TheVertexArray;
	const VertexArray* const vertextArray = vertextArrayShared.get();
	if (vertextArray == nullptr)
	{
		GameEngine_LOG(error, "Renderer2D::DrawQuad(). vertextArrayis not valid.");
		return;
	}

	const TSharedPtr<ShaderProgram>& textureshaderProgramShared = TheData->TextureShaderProgram;
	ShaderProgram* const shaderProgram = TheData->TextureShaderProgram.get();
	if (shaderProgram == nullptr)
	{
		GameEngine_LOG(error, "Renderer2D::DrawQuad(). shaderProgram not valid.");
		return;
	}

	ShaderProgram& shaderProgramRef = *shaderProgram;
	const VertexArray& vertextArrayRef = *vertextArray;

	vertextArrayRef.Bind();
	shaderProgramRef.Bind();
	intexture.Bind();
	shaderProgramRef.SetUniform("u_TheColor", inTintColor);
	shaderProgramRef.SetUniform("u_ObjectTransform", localTransform);
	shaderProgramRef.SetUniform("u_TextureMultiplier", textureMultiplier);
	shaderProgramRef.SetUniform("u_WorldTransform", worldTransform);
	RenderCommand::DrawIndexed(vertextArrayRef);
}

void Renderer2D::EndScene()
{
	RENDERER_PROFILE_FUNCTION();

}

void Renderer2D::ShutDown()
{
	RENDERER_PROFILE_FUNCTION();

	delete TheData;
}