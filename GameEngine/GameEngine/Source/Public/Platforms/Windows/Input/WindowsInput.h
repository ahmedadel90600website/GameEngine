#pragma once

#include "Public/Input/Input.h"
#include "Public/Core.h"

struct GLFWwindow;

class WindowsInput : public Input
{
private:

	virtual bool IsKeyDownImplementation(const int inKey) const override;
	virtual bool IsAMouseKeyImplementation(const int inKey) const override;
	virtual glm::vec2 GetMousePositionImplementation() const override;
	GLFWwindow* GetGLFWWindow() const;

	static TUniquePtr<Input> InputSingleton;
};