#include "Public/PCH.h"

#include "Public/Platforms/Windows/WindowClass/WindowsWindow.h"
#include "Public/EventData/ButtonActionEventData.h"
#include "Public/EventData/MouseMoveEventData.h"
#include "Public/EventData/MouseScrollEventData.h"
#include "Public/EventData/WindowClosedEventData.h"
#include "Public/EventData/WindowResizedEvenetData.h"
#include "Public/EventData/CharEventData.h"
#include "Public/Platforms/Rendering/OpenGL/OpenGLGraphicsContext.h"
#include "Public/Rendering/RendererAPI.h"
#include "Public/Profiler/Instrumentor.h"

// Third party
#include "GLFW/glfw3.h"

static bool IsGLFWInitialized = false;

TSharedPtr<WindowBase> WindowBase::Create(const FWindowProps& inProps)
{
	return TMakeShared<WindowsWindow>(inProps);
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
	PROFILE_FUNCTION();

	glfwPollEvents();
	if (TheGraphicsContext != nullptr)
	{
		TheGraphicsContext->SwapBuffers();
	}
}

void WindowsWindow::SetIsVSyncEnabled(const bool enabled)
{
	PROFILE_FUNCTION();

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
	PROFILE_FUNCTION();

	const std::string windowTitle = inWindowProps.Title;
	const int windowWidth = inWindowProps.Width;
	const int windowHeight = inWindowProps.Height;
	
	TheWindowData.Title = windowTitle;
	TheWindowData.Width = windowWidth;
	TheWindowData.Height = windowHeight;

	GameEngine_LOG(info, "A window has been created. Title: {0}, Width: {1}, Height: {2}", windowTitle, windowWidth, windowHeight);
	if (!IsGLFWInitialized)
	{
		PROFILE_SCOPE("glfwInit");

		int success = glfwInit();
		GameEngine_Assert(success, "WindowsWindow::Initialize. Wasn't able to init GLFW");

		IsGLFWInitialized = true;
	}

	{
		PROFILE_SCOPE("glfwCreateWindow");
		TheGLFWWindow = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), nullptr, nullptr);
		if (RendererAPI::GetTheRendererAPIType() == ERendererAPIType::OPENGL)
		{
			TheGraphicsContext = std::make_unique<OpenGLGraphicsContext>(TheGLFWWindow);
		}
	}

	GameEngine_Assert(TheGraphicsContext, "WindowsWindow::Initialize. Wasn't able to create TheGraphicsContext");
	TheGraphicsContext->Initialize();

	glfwSetWindowUserPointer(TheGLFWWindow, &TheWindowData);
	SetIsVSyncEnabled(true);

	// Mouse actions //////////////////////////////////////////////////////////////////////////////////////
	glfwSetCursorPosCallback(TheGLFWWindow, [](GLFWwindow* window, double xPos, double yPos)
		{
			FWindowData& windowData = *(FWindowData*)glfwGetWindowUserPointer(window);
			FMouseMoveEventData mouseMoveEventData = FMouseMoveEventData(xPos, yPos);
			windowData.OnWindowEvent.Broadcast(&mouseMoveEventData);
		});

	glfwSetScrollCallback(TheGLFWWindow, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			FWindowData& windowData = *(FWindowData*)glfwGetWindowUserPointer(window);
			FMouseScrollEventData mouseScrollEventData = FMouseScrollEventData(xOffset, yOffset);
			windowData.OnWindowEvent.Broadcast(&mouseScrollEventData);
		});

	glfwSetCharCallback(TheGLFWWindow, [](GLFWwindow* window, unsigned int codePoint)
		{
			FWindowData& windowData = *(FWindowData*)glfwGetWindowUserPointer(window);
			FCharEventData charEvent = FCharEventData(codePoint);
			windowData.OnWindowEvent.Broadcast(&charEvent);
		});

	glfwSetMouseButtonCallback(TheGLFWWindow, [](GLFWwindow* window, int button, int action, int mods)
		{
			FWindowData& windowData = *(FWindowData*)glfwGetWindowUserPointer(window);
			FButtonActionEventData buttonActionEvent = FButtonActionEventData(button, -1, action, mods);
			windowData.OnWindowEvent.Broadcast(&buttonActionEvent);
		});
	// Mouse actions //////////////////////////////////////////////////////////////////////////////////////

	// Keyboard actions //////////////////////////////////////////////////////////////////////////////////////
	glfwSetKeyCallback(TheGLFWWindow, [](GLFWwindow* window, int button, int scanCode, int action, int mods)
		{
			FWindowData& windowData = *(FWindowData*)glfwGetWindowUserPointer(window);
			FButtonActionEventData buttonActionEvenet = FButtonActionEventData(button, scanCode, action, mods);
			windowData.OnWindowEvent.Broadcast(&buttonActionEvenet);
		});

	glfwSetWindowCloseCallback(TheGLFWWindow, [](GLFWwindow* window)
		{
			FWindowData& windowData = *(FWindowData*)glfwGetWindowUserPointer(window);
			FWindowClosedEventData windowClosedEvent;
			windowData.OnWindowEvent.Broadcast(&windowClosedEvent);
		});

	glfwSetWindowSizeCallback(TheGLFWWindow, [](GLFWwindow* window, int width, int height)
		{
			FWindowData& windowData = *(FWindowData*)glfwGetWindowUserPointer(window);
			FWindowResizedEventData windowResizedEvent = FWindowResizedEventData(width, height);
			windowData.OnWindowEvent.Broadcast(&windowResizedEvent);
		});
}

void WindowsWindow::ShutDown()
{
	PROFILE_FUNCTION();

	glfwDestroyWindow(TheGLFWWindow);
}