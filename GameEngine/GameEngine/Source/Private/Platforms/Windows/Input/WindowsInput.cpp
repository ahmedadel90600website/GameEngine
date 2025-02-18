#include "Public/PCH.h"
#include "Public/Platforms/Windows/Input/WindowsInput.h"
#include "Public/Application.h"
#include "Public/WindowClass/WindowBase.h"
#include "Public/Core.h"

// Third party
#include "GLFW/glfw3.h"

TUniquePtr<Input> Input::InputSingleton = static_cast<TUniquePtr<Input>>(new WindowsInput());

bool WindowsInput::IsKeyDownImplementation(const int inKey) const
{
	GLFWwindow* nativeWindow = GetGLFWWindow();
	const int state = IsAMouseKeyImplementation(inKey) ? glfwGetMouseButton(nativeWindow, inKey) : glfwGetKey(nativeWindow, inKey);
	return state != GLFW_RELEASE;
}

bool WindowsInput::IsAMouseKeyImplementation(const int inKey) const
{
	return inKey >= GLFW_MOUSE_BUTTON_1 && inKey <= GLFW_MOUSE_BUTTON_LAST;
}

glm::vec2 WindowsInput::GetMousePositionImplementation() const
{
	double xPos = 0.0;
	double yPos = 0.0;
	glfwGetCursorPos(GetGLFWWindow(), &xPos, &yPos);

	return glm::vec2((float)xPos, (float)yPos);
}

GLFWwindow* WindowsInput::GetGLFWWindow() const
{
	return static_cast<GLFWwindow*>(Application::GetWindow().GetNativeWindow());
}