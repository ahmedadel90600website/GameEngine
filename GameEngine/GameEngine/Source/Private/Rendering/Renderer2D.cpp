#include "public/PCH.h"

#include "Public/Rendering/VertexArray.h"
#include "Public/Rendering/RenderCommand.h"
#include "Public/Rendering/Buffers/BufferLayout.h"
#include "Public/Rendering/ShaderProgram.h"
#include "Public/Rendering/Renderer2D.h"
#include "Public/Rendering/Cameras/OrthographicCamera.h"
#include "Public/Platforms/Rendering/OpenGL/OpenGLShaderProgram.h"

Renderer2D::Renderer2DData* Renderer2D::TheData = nullptr;

void Renderer2D::Init()
{
	TheData = new Renderer2D::Renderer2DData();
	GameEngine_Assert(TheData != nullptr, "Renderer2D::Init(). TheData failed to be created.");

	float vertices[] =
	{
		-0.5, -0.5, 0.0f,
		 0.5, -0.5, 0.0f,
		 0.5,  0.5, 0.0f,
		-0.5,  0.5, 0.0f
	};

	TSharedPtr<ShaderProgram>& shaderProgram = TheData->TheShaderProgram;
	shaderProgram = ShaderProgram::Create("Content/Shaders/FlatColor.glsl");
	GameEngine_Assert(shaderProgram != nullptr, "TheShaderProgram failed to be created.");

	TSharedPtr<VertexArray>& vertexArray = TheData->TheVertexArray;
	vertexArray = VertexArray::Create();
	GameEngine_Assert(vertexArray != nullptr, "TheVertexArray failed to be created.");

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

	VertexArray& vertexArrayRef = *vertexArray.get();
	vertexArrayRef.BindVertexBuffer(vertexBuffer);
	vertexArrayRef.BindIndexBuffer(IndexBuffer);
}

void Renderer2D::BeginScene(const OrthographicCamera& orthoCamera)
{
	ShaderProgram* const openGLShaderProgramRaw = TheData->TheShaderProgram.get();

	openGLShaderProgramRaw->Bind();
	openGLShaderProgramRaw->SetUniform("u_ViewProjection", orthoCamera.GetViewProjectionMatrix());
}

void Renderer2D::DrawQuad(const glm::vec4& inColor, const glm::mat4& localTransform, const glm::mat4& worldTransform)
{
	const TSharedPtr<VertexArray>& vertextArrayShared = TheData->TheVertexArray;
	const VertexArray* const vertextArray = vertextArrayShared.get();
	if (vertextArray == nullptr)
	{
		GameEngine_LOG(error, "Renderer2D::DrawQuad(). vertextArrayis not valid.");
		return;
	}

	const TSharedPtr<ShaderProgram>& shaderProgramShared = TheData->TheShaderProgram;
	ShaderProgram* const shaderProgram = shaderProgramShared.get();
	if (vertextArray == nullptr)
	{
		GameEngine_LOG(error, "Renderer2D::DrawQuad(). shaderProgram not valid.");
		return;
	}

	OpenGLShaderProgram* const openGLShaderProgramRaw = dynamic_cast<OpenGLShaderProgram*>(shaderProgram);
	if (openGLShaderProgramRaw == nullptr)
	{
		GameEngine_LOG(error, "No OpenGL shader created");
		return;
	}

	const VertexArray& vertextArrayRef = *vertextArray;
	OpenGLShaderProgram& shaderProgramRef = *openGLShaderProgramRaw;

	vertextArrayRef.Bind();
	shaderProgramRef.Bind();
	shaderProgramRef.SetUniform("u_TheColor", glm::vec3(inColor.x, inColor.y, inColor.z));
	shaderProgramRef.SetUniform("u_ObjectTransform", localTransform);
	shaderProgramRef.SetUniform("u_WorldTransform", worldTransform);
	RenderCommand::DrawIndexed(vertextArrayRef);
}

void Renderer2D::EndScene()
{
}

void Renderer2D::ShutDown()
{
	delete TheData;
}