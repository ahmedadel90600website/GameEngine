#include "Public/PCH.h"
#include "Public/Layers/ImGuiLayer.h"
#include "Public/Application.h"
#include "Public/ImGui/ImGuiOpenGLRenderer.h"
#include "Public/ImGui/ImGuiOpenGLRenderer.h"
#include "Public/WindowClass/WindowBase.h"
#include "Public/EventData/ButtonActionEventData.h"
#include "Public/EventData/MouseMoveEventData.h"
#include "Public/EventData/MouseScrollEventData.h"
#include "Public/EventData/WindowClosedEventData.h"
#include "Public/EventData/WindowResizedEvenetData.h"
#include "Public/EventData/CharEventData.h"

// Third party
#include "GLFW/glfw3.h"
#include "GLAD/glad.h"

void ImGuiLayer::OnAttached()
{
	// Setup Dear ImGui context
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();

	ImGuiBackendFlags& backenFlags = io.BackendFlags;
	backenFlags |= ImGuiBackendFlags_HasMouseCursors;
	backenFlags |= ImGuiBackendFlags_HasSetMousePos;

	io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
	io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
	io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
	io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
	io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
	io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
	io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
	io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
	io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
	io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
	io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
	io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
	io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
	io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
	io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
	io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
	io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
	io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
	io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
	io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
	io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

	ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiLayer::OnRemoved()
{
}

void ImGuiLayer::Tick()
{
	ImGuiIO& io = ImGui::GetIO();
	const WindowBase& window = Application::GetWindow();
	io.DisplaySize = ImVec2(window.GetWidth(), window.GetHeight());

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
	FEventDataBase* eventPointer = &inEvent;
	if (FButtonActionEventData* const buttonActionEventData = dynamic_cast<FButtonActionEventData*>(eventPointer))
	{
		OnButtonActionEvent(*buttonActionEventData);
	}
	else if (FMouseMoveEventData* const mouseMovedEventData = dynamic_cast<FMouseMoveEventData*>(eventPointer))
	{
		OnMouseMovedEvent(*mouseMovedEventData);
	}
	else if (FMouseScrollEventData* const mouseScrolledEventData = dynamic_cast<FMouseScrollEventData*>(eventPointer))
	{
		OnMouseScrolldEvent(*mouseScrolledEventData);
	}
	else if (FWindowClosedEventData* const mouseClosedEventData = dynamic_cast<FWindowClosedEventData*>(eventPointer))
	{
		OnWindowClosedEvent(*mouseClosedEventData);
	}
	else if (FWindowResizedEventData* const windowResizedEventData = dynamic_cast<FWindowResizedEventData*>(eventPointer))
	{
		OnWindowResizedEvent(*windowResizedEventData);
	}
	else if (FCharEventData* const charKeyEvent = dynamic_cast<FCharEventData*>(eventPointer))
	{
		OnCharKeyEvent(*charKeyEvent);
	}
}

bool ImGuiLayer::OnButtonActionEvent(FButtonActionEventData& buttonActionEventData)
{
	ImGuiIO& io = ImGui::GetIO();
	const int button = buttonActionEventData.Button;
	const int action = buttonActionEventData.Action;
	const bool isKeyPressed = action != GLFW_RELEASE;
	// 5 is the size of io.MouseDown
	if (button < 5)
	{
		io.MouseDown[button] = isKeyPressed;
	}
	else
	{
		bool (& keysDownRef)[ImGuiKey_COUNT] = io.KeysDown;
		keysDownRef[button] = isKeyPressed;
		if (isKeyPressed)
		{
			io.KeyCtrl = keysDownRef[GLFW_KEY_LEFT_CONTROL] || keysDownRef[GLFW_KEY_RIGHT_CONTROL];
			io.KeyShift = keysDownRef[GLFW_KEY_LEFT_SHIFT] || keysDownRef[GLFW_KEY_RIGHT_SHIFT];
			io.KeyAlt = keysDownRef[GLFW_KEY_LEFT_ALT] || keysDownRef[GLFW_KEY_RIGHT_ALT];
			io.KeySuper = keysDownRef[GLFW_KEY_LEFT_SUPER] || keysDownRef[GLFW_KEY_RIGHT_SUPER];
		}
	}

	return false;
}

bool ImGuiLayer::OnMouseMovedEvent(FMouseMoveEventData& mouseMovedEventData)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2(mouseMovedEventData.XPosition, mouseMovedEventData.YPosition);

	return false;
}

bool ImGuiLayer::OnMouseScrolldEvent(FMouseScrollEventData& mouseScrolledEventData)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseWheel += mouseScrolledEventData.YOffset;
	io.MouseWheelH += mouseScrolledEventData.XOffset;

	return false;
}

bool ImGuiLayer::OnCharKeyEvent(FCharEventData& charKeyEventData)
{
	ImGuiIO& io = ImGui::GetIO();
	const unsigned int charKey = charKeyEventData.CharKey;
	if (charKey > 0 && charKey < 0x10000)
	{
		io.AddInputCharacter(charKey);
	}

	return false;
}

bool ImGuiLayer::OnWindowClosedEvent(FWindowClosedEventData& mouseScrolledEventData)
{
	return false;
}

bool ImGuiLayer::OnWindowResizedEvent(FWindowResizedEventData& windowResizedEventData)
{
	const int width = windowResizedEventData.Width;
	const int height = windowResizedEventData.Height;
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(width, height);
	io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
	glViewport(0, 0, width, height);

	return false;
}