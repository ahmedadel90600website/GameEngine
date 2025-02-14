// Game
#include "Public/SandboxApplication.h"

// Engine
#include "Public/EntryPoint.h"
#include "Public/Layers/Overlays/OverlayBase.h"
#include "ImGui/imgui.h"
#include "Public/Rendering/Cameras/Camera.h"
#include "Public/Rendering/Buffers/VertexBuffer.h"
#include "Public/Rendering/Buffers/IndexBuffer.h"
#include "Public/Rendering/Buffers/BufferLayout.h"
#include "Public/Rendering/VertexArray.h"
#include "Public/Rendering/ShaderProgram.h"
#include "Public/Rendering/RendererAPI.h"
#include "Public/Rendering/Renderer.h"
#include "Public/Input/Input.h"
#include "Public/Log.h"

class TestOverlay : public OverlayBase
{
public:

	TestOverlay()
	{
		constexpr int vertexSize = 7;
		float vertices[3 * vertexSize] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		SceneCamera = std::make_shared<Camera>(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f));

		const std::string& vertexShader = R"(
	#version 460 core
	layout(location = 0) in vec3 a_Position;
	layout(location = 1) in vec4 a_Color;
	
	out vec4 v_Color;

	uniform mat4 u_ViewProjection;
	uniform mat4 u_ObjectTransform;
	void main()
	{
		v_Color = a_Color;
		gl_Position = u_ViewProjection * u_ObjectTransform * vec4(a_Position, 1.0f);
	}
)";


		const std::string& fragmentShader = R"(
	#version 460 core
	layout(location = 0) out vec4 a_color;
	
	in vec4 v_Color;

	void main()
	{
		a_color = v_Color;
	}
)";

		TheShaderProgram = std::make_shared<ShaderProgram>(vertexShader, fragmentShader);

		TheVertexArray = VertexArray::Create();
		GameEngine_Assert(TheVertexArray != nullptr, "Application::Run(). Vertex array was nullptr");

		TheVertexBuffer = VertexBuffer::Create(sizeof(vertices), vertices);
		std::vector<BufferElement> bufferElements;
		bufferElements.emplace_back("a_Position", EShaderDataType::FLOAT3, false);
		bufferElements.emplace_back("a_Color", EShaderDataType::FLOAT4, false);
		BufferLayout layout(bufferElements);
		TheVertexBuffer->SetLayout(layout);

		uint32_t indices[3] = { 0, 2, 1 };
		TheIndexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		VertexArray& vertexArrayRef = *TheVertexArray;
		vertexArrayRef.BindVertexBuffer(TheVertexBuffer);
		vertexArrayRef.BindIndexBuffer(TheIndexBuffer);
	}

private:

	void Tick(const float deltaTime) override
	{
		const std::shared_ptr<RendererAPI>& renderingAPI = RendererAPI::GetTheRendererAPI();
		if (renderingAPI == nullptr)
		{
			return;
		}

		VertexArray& vertexArrayRef = *TheVertexArray;

		const RendererAPI& renderingAPIRef = *renderingAPI;
		renderingAPIRef.SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		renderingAPIRef.Clear();

		Renderer::BeginScene(*SceneCamera);
		vertexArrayRef.UnBind();

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

		const float cameraRotationSpeed = glm::radians(180.0f) * deltaTime;
		const glm::quat& currentRotation = cameraRef.GetRotation();
		if (Input::IsKeyDown(GameEngineKeyCodes::KEY_D))
		{
			cameraRef.SetRotation(currentRotation * glm::quat(glm::vec3(0.0f, 0.0f, -cameraRotationSpeed)));
		}
		else if (Input::IsKeyDown(GameEngineKeyCodes::KEY_A))
		{
			cameraRef.SetRotation(currentRotation * glm::quat(glm::vec3(0.0f, 0.0f, cameraRotationSpeed)));
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

		Renderer::Submit(vertexArrayRef, *TheShaderProgram, glm::translate(glm::mat4(1.0f), ObjectLocation));

		Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	std::shared_ptr<ShaderProgram> TheShaderProgram = nullptr;
	std::shared_ptr<VertexArray> TheVertexArray = nullptr;
	std::shared_ptr<VertexBuffer> TheVertexBuffer = nullptr;
	std::shared_ptr<IndexBuffer> TheIndexBuffer = nullptr;
	std::shared_ptr<Camera> SceneCamera;
	glm::vec3 ObjectLocation = glm::vec3(0.0f);
};

SandboxApplication::SandboxApplication()
{
	PushOverlay(static_cast<std::unique_ptr<TestOverlay>>(new TestOverlay()));

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