#pragma once

#include "Public/Core.h"
#include "Public/Windows/WindowBase.h"
#include "Public/EventData/EventDataBase.h"

struct GLFWwindow;
class LayerBase;
class OverlayBase;

class GameEngine_API Application
{

public:

	Application();
	virtual ~Application();
	virtual void Tick();

	static Application* Get();
	const WindowBase& GetWindow() const;

	// Layer functions
	void PushLayer(const std::shared_ptr<LayerBase> inLayer);
	void RemoveLayer(const std::shared_ptr<LayerBase> inLayer);

	void PushOverlay(const std::shared_ptr<OverlayBase> inOverlay);
	void RemoveOverlay(const std::shared_ptr<OverlayBase> inOverlay);

	void GatherAllLayers(std::vector<std::shared_ptr<LayerBase>>& outAllLayers);
	// Layer funcitons

private:

	void OnGLFWEvent(FEventDataBase& inEvent);

	// Mouse events
	void OnMouseMoved(double xPos, double yPos);
	void OnMouseScrolled(double xPos, double yPos);

	// Buttons events
	void OnButtonpressed(int button, int scanCode, int mods);
	void OnButtonHeld(int button, int scanCode, int mods);
	void OnButtonReleased(int button, int scanCode, int mods);

	// Window events
	void OnWindowClosed(GLFWwindow* closedWindow);
	void OnWindowResized(GLFWwindow* closedWindow, int width, int height);

	std::vector<std::shared_ptr<LayerBase>> LayersStack;
	std::vector<std::shared_ptr<OverlayBase>> OverlayStack;

	static Application* ApplicationSingleton;
	std::unique_ptr<WindowBase> ApplicationWindow = nullptr;
	bool bIsRunning : 1;
};

extern Application* CreateApplication();