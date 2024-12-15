#include "Public/PCH.h"

#include "Public/Windows/WindowsWindow.h"

// Third party
#include "GLFW/glfw3.h"

static bool IsGLFWInitialized = false;

WindowBase* WindowBase::Create(const WindowProps& inProps)
{
	return new WindowsWindow(inProps);
}

WindowsWindow::WindowsWindow(const WindowProps& inProps)
{
	Initialize(inProps);
}

WindowsWindow::~WindowsWindow()
{
	ShutDown();
}

float WindowsWindow::GetWidth() const
{
	return TheWindowData.Width;
}

float WindowsWindow::GetHeight() const
{
	return TheWindowData.Height;
}

void WindowsWindow::OnUpdate()
{
	glfwPollEvents();
	glfwSwapBuffers(TheGLFWWindow);
}

void WindowsWindow::SetEventCallback(std::function<void(Event&)> inFunction)
{
	TheWindowData.CallbackFunction = inFunction;
}

void WindowsWindow::SetIsVSyncEnabled(const bool enabled)
{
	if (enabled)
	{
		glfwSwapInterval(1);
	}
	else
	{
		glfwSwapInterval(0);
	}

	TheWindowData.bIsVSyncEnabled = enabled;
}

bool WindowsWindow::GetIsVSyncEnabled() const
{
	return TheWindowData.bIsVSyncEnabled;
}

void WindowsWindow::Initialize(const WindowProps& inWindowProps)
{
	const std::string windowTitle = inWindowProps.Title;
	const float windowWidth = inWindowProps.Width;
	const float windowHeight = inWindowProps.Height;
	
	TheWindowData.Title = windowTitle;
	TheWindowData.Width = windowWidth;
	TheWindowData.Height = windowHeight;

	GameEngine_LOG(info, "A window has been created. Title: {0}, Width: {1}, Height: {2}", windowTitle, windowWidth, windowHeight);
	if (!IsGLFWInitialized)
	{
		int success = glfwInit();
		GameEngine_Assert(success, "WindowsWindow::Initialize. Wasn't able to init GLFW");

		IsGLFWInitialized = true;
	}

	TheGLFWWindow = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(TheGLFWWindow);
	glfwSetWindowUserPointer(TheGLFWWindow, &TheWindowData);
	SetIsVSyncEnabled(true);

	// Mouse actions //////////////////////////////////////////////////////////////////////////////////////
	glfwSetCursorPosCallback(TheGLFWWindow, [](GLFWwindow* window, double xpos, double ypos)
		{
			WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(window);
			windowData.OnMouseMoved.Broadcast(xpos, ypos);
		});

	glfwSetScrollCallback(TheGLFWWindow, [](GLFWwindow* window, double xpos, double ypos)
		{
			WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(window);
			windowData.OnMouseScrolled.Broadcast(xpos, ypos);
		});

	glfwSetMouseButtonCallback(TheGLFWWindow, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(window);
			windowData.OnButtonEvent.Broadcast(button, -1, action, mods);
		});
	// Mouse actions //////////////////////////////////////////////////////////////////////////////////////

	// Keyboard actions //////////////////////////////////////////////////////////////////////////////////////
	glfwSetKeyCallback(TheGLFWWindow, [](GLFWwindow* window, int button, int scanCode, int action, int mods)
		{
			WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(window);
			windowData.OnButtonEvent.Broadcast(button, scanCode, action, mods);
		});

	glfwSetWindowCloseCallback(TheGLFWWindow, [](GLFWwindow* window)
		{
			WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(window);
			windowData.OnWindowClosed.Broadcast(window);
		});

	glfwSetWindowSizeCallback(TheGLFWWindow, [](GLFWwindow* window, int width, int height)
		{
			WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(window);
			windowData.OnWindowResized.Broadcast(window, width, height);
		});
}

void WindowsWindow::ShutDown()
{
	glfwDestroyWindow(TheGLFWWindow);
}