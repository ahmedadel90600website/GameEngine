#pragma once

#include "Public/Input/Input.h"

struct GLFWwindow;

class WindowsInput : public Input
{
private:

	virtual bool IsKeyDownImplementation(const int inKey) const override;
	virtual bool IsAMouseKeyImplementation(const int inKey) const override;
	virtual FVector2 GetMousePositionImplementation() const override;
	GLFWwindow* GetGLFWWindow() const;

	static std::unique_ptr<Input> InputSingleton;
};