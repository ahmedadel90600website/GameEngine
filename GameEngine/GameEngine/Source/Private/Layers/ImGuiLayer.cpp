#include "Public/PCH.h"
#include "Public/Layers/ImGuiLayer.h"
#include "Public/Application.h"
#include "Public/ImGui/ImGuiOpenGLRenderer.h"
#include "Public/ImGui/ImGuiOpenGLRenderer.h"
#include "Public/Windows/WindowBase.h"

// Third party
#include "GLFW/glfw3.h"

void ImGuiLayer::OnAttached()
{
	// Setup Dear ImGui context
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	ImGuiBackendFlags& backenFlags = io.BackendFlags;
	backenFlags |= ImGuiBackendFlags_HasMouseCursors;
	backenFlags |= ImGuiBackendFlags_HasSetMousePos;

	ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiLayer::OnRemoved()
{
}

void ImGuiLayer::Tick()
{
	ImGuiIO& io = ImGui::GetIO();
	if (Application* application = Application::Get())
	{
		const WindowBase& window = application->GetWindow();
		io.DisplaySize = ImVec2(window.GetWidth(), window.GetHeight());
	}

	const float currentUpdatedTime = glfwGetTime();
	const float deltaTime = currentUpdatedTime - CurrentTime;
	io.DeltaTime = (deltaTime > 0.0f && CurrentTime > 0) ? deltaTime : 1 / 60.0f;
	CurrentTime = currentUpdatedTime;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();


	static bool showDemiWindow = true;
	ImGui::ShowDemoWindow(&showDemiWindow);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::OnEvent(FEventDataBase& inEvent)
{
}