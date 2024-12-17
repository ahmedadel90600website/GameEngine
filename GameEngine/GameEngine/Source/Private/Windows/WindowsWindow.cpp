#include "Public/PCH.h"

#include "Public/Windows/WindowsWindow.h"
#include "Public/EventData/ButtonActionEventData.h"
#include "Public/EventData/MouseMoveEventData.h"
#include "Public/EventData/MouseScrollEventData.h"
#include "Public/EventData/WindowClosedEventData.h"
#include "Public/EventData/WindowResizedEvenetData.h"

// Third party
#include "GLFW/glfw3.h"

static bool IsGLFWInitialized = false;

WindowBase* WindowBase::Create(const FWindowProps& inProps)
{
	return new WindowsWindow(inProps);
}

WindowsWindow::WindowsWindow(const FWindowProps& inProps)
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

void WindowsWindow::Initialize(const FWindowProps& inWindowProps)
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
	glfwSetCursorPosCallback(TheGLFWWindow, [](GLFWwindow* window, double xPos, double yPos)
		{
			FWindowData& windowData = *(FWindowData*)glfwGetWindowUserPointer(window);
			windowData.OnGLFWEvent.Broadcast(FMouseMoveEventData(xPos, yPos));
		});

	glfwSetScrollCallback(TheGLFWWindow, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			FWindowData& windowData = *(FWindowData*)glfwGetWindowUserPointer(window);
			windowData.OnGLFWEvent.Broadcast(FMouseScrollEventData(xOffset, yOffset));
		});

	glfwSetMouseButtonCallback(TheGLFWWindow, [](GLFWwindow* window, int button, int action, int mods)
		{
			FWindowData& windowData = *(FWindowData*)glfwGetWindowUserPointer(window);
			windowData.OnGLFWEvent.Broadcast(FButtonActionEventData(button, -1, action, mods));
		});
	// Mouse actions //////////////////////////////////////////////////////////////////////////////////////

	// Keyboard actions //////////////////////////////////////////////////////////////////////////////////////
	glfwSetKeyCallback(TheGLFWWindow, [](GLFWwindow* window, int button, int scanCode, int action, int mods)
		{
			FWindowData& windowData = *(FWindowData*)glfwGetWindowUserPointer(window);
			windowData.OnGLFWEvent.Broadcast(FButtonActionEventData(button, scanCode, action, mods));
		});

	glfwSetWindowCloseCallback(TheGLFWWindow, [](GLFWwindow* window)
		{
			FWindowData& windowData = *(FWindowData*)glfwGetWindowUserPointer(window);
			windowData.OnGLFWEvent.Broadcast(FWindowClosedEventData(window));
		});

	glfwSetWindowSizeCallback(TheGLFWWindow, [](GLFWwindow* window, int width, int height)
		{
			FWindowData& windowData = *(FWindowData*)glfwGetWindowUserPointer(window);
			windowData.OnGLFWEvent.Broadcast(FWindowResizedEventData(window, width, height));
		});
}

void WindowsWindow::ShutDown()
{
	glfwDestroyWindow(TheGLFWWindow);
}