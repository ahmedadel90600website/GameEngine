#include "Public/PCH.h"

#include "Public/Platforms/Windows/WindowClass/WindowsWindow.h"
#include "Public/EventData/ButtonActionEventData.h"
#include "Public/EventData/MouseMoveEventData.h"
#include "Public/EventData/MouseScrollEventData.h"
#include "Public/EventData/WindowClosedEventData.h"
#include "Public/EventData/WindowResizedEvenetData.h"
#include "Public/EventData/CharEventData.h"

// Third party
#include "GLFW/glfw3.h"
#include "GLAD/glad.h"

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

int WindowsWindow::GetWidth() const
{
	return TheWindowData.Width;
}

int WindowsWindow::GetHeight() const
{
	return TheWindowData.Height;
}

void WindowsWindow::OnUpdate()
{
	glfwPollEvents();
	glfwSwapBuffers(TheGLFWWindow);
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

void* WindowsWindow::GetNativeWindow() const
{
	return TheGLFWWindow;
}

void WindowsWindow::Initialize(const FWindowProps& inWindowProps)
{
	const std::string windowTitle = inWindowProps.Title;
	const int windowWidth = inWindowProps.Width;
	const int windowHeight = inWindowProps.Height;
	
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

	int gladInitialization = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	GameEngine_Assert(gladInitialization, "WindowsWindow::Initialize. Wasn't able to init GLAD");

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

	glfwSetCharCallback(TheGLFWWindow, [](GLFWwindow* window, unsigned int codePoint)
		{
			FWindowData& windowData = *(FWindowData*)glfwGetWindowUserPointer(window);
			windowData.OnGLFWEvent.Broadcast(FCharEventData(codePoint));
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