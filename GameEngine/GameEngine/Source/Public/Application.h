#pragma once

#include "Public/Core.h"
#include "Public/WindowClass/WindowBase.h"
#include "Public/EventData/EventDataBase.h"
#include "Public/ImGui/Layers/ImGuiLayer.h"

struct GLFWwindow;
class LayerBase;
class OverlayBase;

class GameEngine_API Application
{

public:

	Application();
	virtual ~Application();
	virtual void Run();

	static Application* Get();
	static WindowBase& GetWindowRef();
	static const WindowBase& GetWindow();

	// Layer functions
	void PushLayer(const TSharedPtr<LayerBase> inLayer);
	void RemoveLayer(const TSharedPtr<LayerBase> inLayer);

	void PushOverlay(const TSharedPtr<OverlayBase> inOverlay);
	void RemoveOverlay(const TSharedPtr<OverlayBase> inOverlay);
	void GatherAllLayers(std::vector<TSharedPtr<LayerBase>>& outAllLayers);
	// Layer funcitons

private:

	void OnWindowEvent(FEventDataBase* inEvent);

	// Mouse events
	void OnMouseMoved(double xPos, double yPos);
	void OnMouseScrolled(double xPos, double yPos);

	// Buttons events
	void OnButtonpressed(int button, int scanCode, int mods);
	void OnButtonHeld(int button, int scanCode, int mods);
	void OnButtonReleased(int button, int scanCode, int mods);

	// Window events
	void OnWindowClosed();
	void OnWindowResized(int width, int height);

	std::vector<TSharedPtr<LayerBase>> LayersStack;
	std::vector<TSharedPtr<OverlayBase>> OverlayStack;

	static Application* ApplicationSingleton;
	TSharedPtr<WindowBase> ApplicationWindow = nullptr;
	TSharedPtr<ImGuiLayer> TheImGuiOverlay = nullptr;
	
	float TimeLastFrame = 0.0f;
	float DeltaTime = 0.0f;
	bool bIsRunning : 1;
	bool bIsMinimized : 1;
};

extern Application* CreateApplication();