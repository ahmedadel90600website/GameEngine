#include "Public/PCH.h"

#include "Public/Platforms/Rendering/OpenGL/OpenGLGraphicsContext.h"
#include "Public/Profiler/Instrumentor.h"
#include "GLAD/glad.h"

OpenGLGraphicsContext::OpenGLGraphicsContext(GLFWwindow* const inWindowHandle) :
	WindowHandle(inWindowHandle)
{
	GameEngine_Assert(inWindowHandle != nullptr, "The window handle passed to OpenGLGraphicsContext::OpenGLGraphicsContext was nullptr");
}

void OpenGLGraphicsContext::Initialize()
{
	RENDERER_PROFILE_FUNCTION();

	glfwMakeContextCurrent(WindowHandle);
	int gladInitialization = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	GameEngine_Assert(gladInitialization, "WindowsWindow::Initialize. Wasn't able to init GLAD");
}

void OpenGLGraphicsContext::SwapBuffers()
{
	RENDERER_PROFILE_FUNCTION();

	glfwSwapBuffers(WindowHandle);
}