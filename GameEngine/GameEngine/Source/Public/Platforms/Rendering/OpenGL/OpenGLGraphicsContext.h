#pragma once

#include "Public/Rendering/GraphicsContext.h"
#include "GLFW/glfw3.h"

class OpenGLGraphicsContext : public GraphicsContext
{
public:

	OpenGLGraphicsContext(GLFWwindow* const inWindowHandle);
	virtual void Initialize() override;
	virtual void SwapBuffers() override;

private:

	GLFWwindow* WindowHandle = nullptr;
};