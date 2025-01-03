#include "Public/PCH.h"

// Engine
#include "Public/Application.h"
#include "Public/Windows/Structs/WindowProps.h"

#include "Public/EventData/ButtonActionEventData.h"
#include "Public/EventData/MouseMoveEventData.h"
#include "Public/EventData/MouseScrollEventData.h"
#include "Public/EventData/WindowClosedEventData.h"
#include "Public/EventData/WindowResizedEvenetData.h"
#include "Public/Layers/Overlays/OverlayBase.h"

// Third party
#include "GLAD/glad.h"

Application* Application::ApplicationSingleton = nullptr;

Application::Application() :
	bIsRunning(true)
{
	GameEngine_Assert(ApplicationSingleton == nullptr, "You can't create more than one application instance");

	ApplicationSingleton = this;
	ApplicationWindow = static_cast<std::unique_ptr<WindowBase>>(WindowBase::Create(FWindowProps("Test", 1000, 1000)));
	if (ApplicationWindow != nullptr)
	{
		ApplicationWindow->GetOnGLFWEvent().ADD_OBJECT(Application, this, OnGLFWEvent);
	}
}

Application::~Application()
{
	if (ApplicationWindow != nullptr)
	{
		WindowBase& applicationWindowRef = *ApplicationWindow;
		applicationWindowRef.GetOnGLFWEvent().RemoveAll(this);
	}
}

void Application::Tick()
{
	while (bIsRunning)
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		std::vector<std::shared_ptr<LayerBase>> allLayers;
		GatherAllLayers(allLayers);
		for (const std::shared_ptr<LayerBase> currentLayer : allLayers)
		{
			currentLayer->Tick();
		}

		ApplicationWindow->OnUpdate();
	}
}

Application* Application::Get()
{
	return ApplicationSingleton;
}

const WindowBase& Application::GetWindow() const
{
	return *ApplicationWindow.get();
}

void Application::PushLayer(const std::shared_ptr<LayerBase> inLayer)
{
	if (inLayer == nullptr)
	{
		GameEngine_LOG(error, "Pushed layer is nullptr");
		return;
	}

	LayersStack.push_back(inLayer);
	inLayer->OnAttached();
}

void Application::RemoveLayer(const std::shared_ptr<LayerBase> inLayer)
{
	if (inLayer == nullptr)
	{
		GameEngine_LOG(error, "Layer to remove is nullptr");
		return;
	}

	const std::vector<std::shared_ptr<LayerBase>>::iterator& layersStackEnd = LayersStack.end();
	const std::vector<std::shared_ptr<LayerBase>>::iterator& foundLayer = std::find(LayersStack.begin(), layersStackEnd, inLayer);
	if (foundLayer != layersStackEnd)
	{

		LayersStack.erase(foundLayer);
		inLayer->OnRemoved();
		return;
	}
}

void Application::PushOverlay(const std::shared_ptr<OverlayBase> inOverlay)
{
	if (inOverlay == nullptr)
	{
		GameEngine_LOG(error, "Pushed overlay is nullptr");
		return;
	}

	OverlayStack.push_back(inOverlay);
	inOverlay->OnAttached();
}

void Application::RemoveOverlay(const std::shared_ptr<OverlayBase> inOverlay)
{
	if (inOverlay == nullptr)
	{
		GameEngine_LOG(error, "Overlay to remove is nullptr");
		return;
	}

	const std::vector<std::shared_ptr<OverlayBase>>::iterator& overlayStackEnd = OverlayStack.end();
	const std::vector<std::shared_ptr<OverlayBase>>::iterator& foundOverLay = std::find(OverlayStack.begin(), overlayStackEnd, inOverlay);
	if (foundOverLay != overlayStackEnd)
	{

		OverlayStack.erase(foundOverLay); 
		inOverlay->OnRemoved();
		return;
	}
}

void Application::GatherAllLayers(std::vector<std::shared_ptr<LayerBase>>& outAllLayers)
{
	outAllLayers.clear();
	outAllLayers.reserve(LayersStack.size() + OverlayStack.size());
	outAllLayers.insert(outAllLayers.end(), LayersStack.begin(), LayersStack.end());
	outAllLayers.insert(outAllLayers.end(), OverlayStack.begin(), OverlayStack.end());
}

void Application::OnGLFWEvent(FEventDataBase& inEvent)
{
	FEventDataBase* inEventPtr = &inEvent;
	if (FWindowClosedEventData* windowClosedEventData = dynamic_cast<FWindowClosedEventData*>(inEventPtr))
	{
		OnWindowClosed(windowClosedEventData->TheGLFWWindow);
	}

	std::vector<std::shared_ptr<LayerBase>> allLayers;
	GatherAllLayers(allLayers);

	const int numberOfLayers = static_cast<int>(allLayers.size());
	for (int i = numberOfLayers - 1; i >= 0; --i)
	{
		if (const std::shared_ptr<LayerBase> currentLayer = allLayers[i])
		{
			currentLayer->OnEvent(inEvent);
			// Make the layer consume the event.
			if (inEvent.bHasBeenHandled)
			{
				break;
			}
		}
	}
}

void Application::OnMouseMoved(double xPos, double yPos)
{
}

void Application::OnMouseScrolled(double xPos, double yPos)
{
}

void Application::OnButtonpressed(int button, int scanCode, int mods)
{
}

void Application::OnButtonHeld(int button, int scanCode, int mods)
{
}

void Application::OnButtonReleased(int button, int scanCode, int mods)
{
}

void Application::OnWindowClosed(GLFWwindow* closedWindow)
{
	bIsRunning = false;
}

void Application::OnWindowResized(GLFWwindow* closedWindow, int width, int height)
{
}