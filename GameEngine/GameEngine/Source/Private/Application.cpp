#include "Public/PCH.h"

// Engine
#include "Public/Application.h"
#include "Public/WindowClass/Structs/WindowProps.h"

#include "Public/EventData/WindowClosedEventData.h"
#include "Public/EventData/WindowResizedEvenetData.h"
#include "Public/Layers/Overlays/OverlayBase.h"
#include "Public/Rendering/Renderer.h"

#include <stdint.h>
#include "Public/Core.h"

// Third party
#include "glfw/glfw3.h"
#include "glm/ext/matrix_clip_space.hpp"

Application* Application::ApplicationSingleton = nullptr;

Application::Application() : bIsRunning(true)
{
	GameEngine_Assert(ApplicationSingleton == nullptr, "You can't create more than one application instance");

	ApplicationSingleton = this;

	ApplicationWindow = WindowBase::Create(FWindowProps("Test", 1920, 1080));
	if (ApplicationWindow != nullptr)
	{
		ApplicationWindow->GetOnWindowEvent().ADD_OBJECT(this, &Application::OnWindowEvent);
	}

	Renderer::Init();
	TheImGuiOverlay = std::make_shared<ImGuiLayer>();
	PushOverlay(TheImGuiOverlay);
}

Application::~Application()
{
	if (ApplicationWindow != nullptr)
	{
		WindowBase& applicationWindowRef = *ApplicationWindow;
		applicationWindowRef.GetOnWindowEvent().RemoveAll(this);
	}
}

void Application::Run()
{
	while (bIsRunning)
	{
		const float currentTime = (float)glfwGetTime();
		DeltaTime = currentTime - TimeLastFrame;
		TimeLastFrame = currentTime;

		std::vector<TSharedPtr<LayerBase>> allLayers;
		GatherAllLayers(allLayers);

		if (!bIsMinimized)
		{
			for (const TSharedPtr<LayerBase> currentLayer : allLayers)
			{
				currentLayer->Tick(DeltaTime);
			}
		}

		TheImGuiOverlay->BeginRendering();

		for (const TSharedPtr<LayerBase> currentLayer : allLayers)
		{
			currentLayer->OnImGuiRender();
		}

		TheImGuiOverlay->EndRendering();

		ApplicationWindow->OnUpdate();
	}
}

Application* Application::Get()
{
	return ApplicationSingleton;
}

WindowBase& Application::GetWindowRef()
{
	return *(ApplicationSingleton->ApplicationWindow.get());
}

const WindowBase& Application::GetWindow()
{
	return *(ApplicationSingleton->ApplicationWindow.get());
}

void Application::PushLayer(const TSharedPtr<LayerBase> inLayer)
{
	if (inLayer == nullptr)
	{
		GameEngine_LOG(error, "Pushed layer is nullptr");
		return;
	}

	LayersStack.push_back(inLayer);
	inLayer->OnAttached();
}

void Application::RemoveLayer(const TSharedPtr<LayerBase> inLayer)
{
	if (inLayer == nullptr)
	{
		GameEngine_LOG(error, "Layer to remove is nullptr");
		return;
	}

	const std::vector<TSharedPtr<LayerBase>>::iterator& layersStackEnd = LayersStack.end();
	const std::vector<TSharedPtr<LayerBase>>::iterator& foundLayer = std::find(LayersStack.begin(), layersStackEnd, inLayer);
	if (foundLayer != layersStackEnd)
	{

		LayersStack.erase(foundLayer);
		inLayer->OnRemoved();
		return;
	}
}

void Application::PushOverlay(const TSharedPtr<OverlayBase> inOverlay)
{
	if (inOverlay == nullptr)
	{
		GameEngine_LOG(error, "Pushed overlay is nullptr");
		return;
	}

	OverlayStack.push_back(inOverlay);
	inOverlay->OnAttached();
}

void Application::RemoveOverlay(const TSharedPtr<OverlayBase> inOverlay)
{
	if (inOverlay == nullptr)
	{
		GameEngine_LOG(error, "Overlay to remove is nullptr");
		return;
	}

	const std::vector<TSharedPtr<OverlayBase>>::iterator& overlayStackEnd = OverlayStack.end();
	const std::vector<TSharedPtr<OverlayBase>>::iterator& foundOverLay = std::find(OverlayStack.begin(), overlayStackEnd, inOverlay);
	if (foundOverLay != overlayStackEnd)
	{

		OverlayStack.erase(foundOverLay); 
		inOverlay->OnRemoved();
		return;
	}
}

void Application::GatherAllLayers(std::vector<TSharedPtr<LayerBase>>& outAllLayers)
{
	outAllLayers.clear();
	outAllLayers.reserve(LayersStack.size() + OverlayStack.size());
	outAllLayers.insert(outAllLayers.end(), LayersStack.begin(), LayersStack.end());
	outAllLayers.insert(outAllLayers.end(), OverlayStack.begin(), OverlayStack.end());
}

void Application::OnWindowEvent(FEventDataBase* inEvent)
{
	if (inEvent == nullptr)
	{
		return;
	}

	if (FWindowClosedEventData* windowClosedEventData = dynamic_cast<FWindowClosedEventData*>(inEvent))
	{
		OnWindowClosed();
	}
	else if (FWindowResizedEventData* windowResizedEventData = dynamic_cast<FWindowResizedEventData*>(inEvent))
	{
		OnWindowResized(windowResizedEventData->Width, windowResizedEventData->Height);
	}

	std::vector<TSharedPtr<LayerBase>> allLayers;
	GatherAllLayers(allLayers);

	const int numberOfLayers = static_cast<int>(allLayers.size());
	for (int i = numberOfLayers - 1; i >= 0; --i)
	{
		if (const TSharedPtr<LayerBase> currentLayer = allLayers[i])
		{
			currentLayer->OnEvent(inEvent);
			// Make the layer consume the event.
			if (inEvent->bHasBeenHandled)
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

void Application::OnWindowClosed()
{
	bIsRunning = false;
}

void Application::OnWindowResized(int width, int height)
{
	bIsMinimized = width == 0 || height == 0;
	Renderer::SetViewPortDimensions(width, height);
}