#pragma once

#include "Public/Rendering/Cameras/Camera.h"

class OrthographicCamera : public Camera
{
public:

	OrthographicCamera(const float left, const float right, const float bottom, const float top);

private:

	void OnWindowEvent(FEventDataBase* theEvent) override;
};