// Game
#include "Public/SandboxApplication.h"

// Engine
#include "Public/EntryPoint.h"
#include "Public/Core.h"
#include "Public/Layers/Overlays/OverlayBase.h"
#include "Public/Rendering/Cameras/Camera.h"
#include "Public/Rendering/Buffers/VertexBuffer.h"
#include "Public/Rendering/Buffers/IndexBuffer.h"
#include "Public/Rendering/Buffers/BufferLayout.h"
#include "Public/Rendering/VertexArray.h"
#include "Public/Rendering/ShaderProgram.h"
#include "Public/Rendering/RenderCommand.h"
#include "Public/Rendering/Renderer.h"
#include "Public/Input/Input.h"
#include "Public/Log.h"
#include "Public/Platforms/Rendering/OpenGL/OpenGLShaderProgram.h"
#include "Public/Rendering/Textures/Texture2D.h"
#include "Public/Rendering/ShaderLibrary.h"

// Third party
#include "ImGui/imgui.h"
#include "glm/gtc/type_ptr.hpp"

class TestOverlay : public OverlayBase
{
public:

	TestOverlay()
	{
		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		SceneCamera = std::make_shared<Camera>(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f));
		const TSharedPtr<ShaderProgram>& shaderProgram = ShaderLibraryTest.LoadShader("Content/Shaders/SandboxShader.glsl");

		TheVertexArray = VertexArray::Create();
		GameEngine_Assert(TheVertexArray != nullptr, "Application::Run(). Vertex array was nullptr");

		TheVertexBuffer = VertexBuffer::Create(sizeof(vertices), vertices);
		std::vector<BufferElement> bufferElements;
		bufferElements.emplace_back("a_Position", EShaderDataType::FLOAT3, false);
		bufferElements.emplace_back("a_TextureCoordinates", EShaderDataType::FLOAT2, false);
		BufferLayout layout(bufferElements);
		TheVertexBuffer->SetLayout(layout);

		uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };
		//uint32_t indices[] = { 0, 3, 2, 2, 1, 0 }; // Clock wise
		TheIndexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		VertexArray& vertexArrayRef = *TheVertexArray;
		vertexArrayRef.BindVertexBuffer(TheVertexBuffer);
		vertexArrayRef.BindIndexBuffer(TheIndexBuffer);

		The2DTexture = Texture2D::Create("Content/Textures/CJ.png");
		The2DTextureTest = Texture2D::Create("Content/Textures/BigSmoke.png");
		if (const TSharedPtr<OpenGLShaderProgram>& openGLShaderProgram = std::dynamic_pointer_cast<OpenGLShaderProgram>(shaderProgram))
		{
			openGLShaderProgram->UploadUniform("u_TextureSlot", 0);
		}
	}

private:

	void Tick(const float deltaTime) override
	{
		const TSharedPtr<RendererAPI>& renderingAPI = RenderCommand::GetTheRendererAPI();
		if (renderingAPI == nullptr)
		{
			return;
		}

		const TSharedPtr<ShaderProgram>& shaderProgram = ShaderLibraryTest.GetShader("SandboxShader");
		const TSharedPtr<OpenGLShaderProgram>& openGLShaderProgram = std::dynamic_pointer_cast<OpenGLShaderProgram>(shaderProgram);
		if (openGLShaderProgram.get() == nullptr)
		{
			Application_LOG(error, "No OpenGL shader created");
			return;
		}

		openGLShaderProgram->Bind();
		VertexArray& vertexArrayRef = *TheVertexArray;

		const RendererAPI& renderingAPIRef = *renderingAPI;
		RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		RenderCommand::Clear();

		Renderer::BeginScene(*SceneCamera);

		Camera& cameraRef = *SceneCamera;
		const glm::vec3& currentLocation = cameraRef.GetLocation();
		const float cameraSpeed = 1.0f * deltaTime;

		// Camera movement
		if (Input::IsKeyDown(GameEngineKeyCodes::KEY_UP))
		{
			cameraRef.SetLocation(currentLocation + glm::vec3(0.0f, cameraSpeed, 0.0f));
		}
		else if (Input::IsKeyDown(GameEngineKeyCodes::KEY_DOWN))
		{
			cameraRef.SetLocation(currentLocation + glm::vec3(0.0f, -cameraSpeed, 0.0f));
		}

		if (Input::IsKeyDown(GameEngineKeyCodes::KEY_RIGHT))
		{
			cameraRef.SetLocation(currentLocation + glm::vec3(cameraSpeed, 0.0f, 0.0f));
		}
		else if (Input::IsKeyDown(GameEngineKeyCodes::KEY_LEFT))
		{
			cameraRef.SetLocation(currentLocation + glm::vec3(-cameraSpeed, 0.0f, 0.0f));
		}

		const float rotationSpeed = glm::radians(180.0f) * deltaTime;
		const glm::quat& currentRotation = cameraRef.GetRotation();
		if (Input::IsKeyDown(GameEngineKeyCodes::KEY_D))
		{
			//cameraRef.SetRotation(currentRotation * glm::quat(glm::vec3(0.0f, 0.0f, -rotationSpeed)));
			ObjectsRotation = ObjectsRotation * glm::quat(glm::vec3(0.0f, 0.0f, -rotationSpeed));
		}
		else if (Input::IsKeyDown(GameEngineKeyCodes::KEY_A))
		{
			//cameraRef.SetRotation(currentRotation * glm::quat(glm::vec3(0.0f, 0.0f, rotationSpeed)));
			ObjectsRotation = ObjectsRotation * glm::quat(glm::vec3(0.0f, 0.0f, +rotationSpeed));
		}

		// Object movement
		if (Input::IsKeyDown(GameEngineKeyCodes::KEY_L))
		{
			ObjectLocation.x += cameraSpeed;
		}
		else if (Input::IsKeyDown(GameEngineKeyCodes::KEY_J))
		{
			ObjectLocation.x -= cameraSpeed;
		}

		if (Input::IsKeyDown(GameEngineKeyCodes::KEY_I))
		{
			ObjectLocation.y += cameraSpeed;
		}
		else if (Input::IsKeyDown(GameEngineKeyCodes::KEY_K))
		{
			ObjectLocation.y -= cameraSpeed;
		}

		//openGLShaderProgram->UploadUniform("u_TheColor", ObjectColor);
		//for (int i = 0; i < 10; ++i)
		//{
		//	const glm::vec3& finalLocation = ObjectLocation + glm::vec3(i * 0.11f, 0.0f, 0.0f);
		//	const glm::mat4& finalTransform = glm::translate(glm::mat4(1.0f), finalLocation) * scaleMatrix;
		//	Renderer::Submit(vertexArrayRef, *TheShaderProgram, finalTransform);
		//}

		The2DTexture->Bind();
		Renderer::Submit(vertexArrayRef, *shaderProgram, glm::translate(glm::mat4(1.0f), ObjectLocation) * glm::mat4(ObjectsRotation));

		The2DTextureTest->Bind();
		Renderer::Submit(vertexArrayRef, *shaderProgram, glm::translate(glm::mat4(1.0f), ObjectLocation + glm::vec3(0.5f, 0.5f, 0.0f)) * glm::mat4(ObjectsRotation));

		Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square_Color", glm::value_ptr(ObjectColor));
		ImGui::End();
	}

	glm::quat ObjectsRotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
	ShaderLibrary ShaderLibraryTest;
	TSharedPtr<VertexArray> TheVertexArray = nullptr;
	TSharedPtr<VertexBuffer> TheVertexBuffer = nullptr;
	TSharedPtr<IndexBuffer> TheIndexBuffer = nullptr;
	TSharedPtr<Camera> SceneCamera;
	TSharedPtr<Texture2D> The2DTexture;
	TSharedPtr<Texture2D> The2DTextureTest;
	glm::vec3 ObjectLocation = glm::vec3(0.0f);
	glm::vec3 ObjectColor = glm::vec3(1.0f, 0.0f, 0.0f);
};

SandboxApplication::SandboxApplication()
{
	PushOverlay(static_cast<TUniquePtr<TestOverlay>>(new TestOverlay()));
}

SandboxApplication::~SandboxApplication()
{
}

void SandboxApplication::Run()
{
	Application::Run();

}

Application* CreateApplication()
{
	return new SandboxApplication();
}