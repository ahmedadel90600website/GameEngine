#pragma once

#include "Public/PCH.h"
#include "Public/EventData/EventDataBase.h"
#include "Public/Events/MulticastDelegate.h"

struct GLFWwindow;

struct GameEngine_API FWindowData
{
	FWindowData() : bIsVSyncEnabled(false) {}

	std::string Title = "Window";
	int Height = 100;
	int Width = 100;
	bool bIsVSyncEnabled : 1;

	/* Param1 Button: like GLFW_MOUSE_BUTTON_LEFT or GLFW_KEY_SPACE
	* Param2 ScanCode: The scancode of a key is specific to that platform or sometimes even to that machine.
	  Scancodes are intended to allow users to bind keys that don't have a GLFW key token.
	  Such keys have key set to GLFW_KEY_UNKNOWN, their state is not saved and so it cannot be retrieved with glfwGetKey. Check: https://www.glfw.org/docs/3.0/group__input.html
	* Param3 Action: GLFW_RELEASE, GLFW_PRESS, GLFW_REPEAT
	* Param4 Mod: Another button held down with the mouse like shift.
	*/

	MulticastDelegate<FEventDataBase&> OnGLFWEvent;
};