#pragma once

#include "Public/PCH.h"
#include "Public/Events/Event.h"
#include "Public/Events/MulticastDelegate.h"

extern class GLFWwindow;

struct WindowData
{
	WindowData() : bIsVSyncEnabled (false) {}

	std::string Title = "Window";
	float Height = 100.0f;
	float Width = 100.0f;
	bool bIsVSyncEnabled : 1;
	std::function<void(Event&)> CallbackFunction;

	MulticastDelegate<double /*XPos*/, double /*YPos*/> OnMouseMoved;
	MulticastDelegate<double /*XOffset*/, double /*YOffset*/> OnMouseScrolled;

	/* Param1 Button: like GLFW_MOUSE_BUTTON_LEFT or GLFW_KEY_SPACE
	* Param2 ScanCode: The scancode of a key is specific to that platform or sometimes even to that machine.
	  Scancodes are intended to allow users to bind keys that don't have a GLFW key token. 
	  Such keys have key set to GLFW_KEY_UNKNOWN, their state is not saved and so it cannot be retrieved with glfwGetKey. Check: https://www.glfw.org/docs/3.0/group__input.html
	* Param3 Action: GLFW_RELEASE, GLFW_PRESS, GLFW_REPEAT
	* Param4 Mod: Another button held down with the mouse like shift.
	*/
	MulticastDelegate<int /*Button*/, int /*ScanCode*/, int /*Action*/, int /*Mod*/> OnButtonEvent;

	MulticastDelegate<GLFWwindow*> OnWindowClosed;
	MulticastDelegate<GLFWwindow*, int /*width*/, int /*height*/> OnWindowResized;
};