#include "Public/PCH.h"
#include "Public/Rendering/Cameras/OrthographicCamera.h"

#include "Public/EventData/MouseScrollEventData.h"
#include "Public/EventData/WindowResizedEvenetData.h"


OrthographicCamera::OrthographicCamera(const float left, const float right, const float bottom, const float top) :
	Camera(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
{
}

void OrthographicCamera::OnWindowEvent(FEventDataBase* theEvent)
{
	Camera::OnWindowEvent(theEvent);

	// Maybe this should be moved to Camera except for ProjectionMatrix = glm::ortho(-AspectRatio * ZoomOutLevel, AspectRatio * ZoomOutLevel, -ZoomOutLevel, ZoomOutLevel);
	bool shouldUpdateprojectionMatrix = false;
	if (FMouseScrollEventData* scrollEvent = dynamic_cast<FMouseScrollEventData*>(theEvent))
	{
		ZoomOutLevel -= (static_cast<float>(scrollEvent->YOffset) * ZoomOutLevelMultiplier);
		if (ZoomOutLevel < MinZoomOutLevel)
		{
			ZoomOutLevel = MinZoomOutLevel;
		}

		shouldUpdateprojectionMatrix = true;
	}
	else if (FWindowResizedEventData* resizeEvent = dynamic_cast<FWindowResizedEventData*>(theEvent))
	{
		FWindowResizedEventData& resizeEventRef = *resizeEvent;
		AspectRatio = (float)resizeEventRef.Width / resizeEventRef.Height;

		shouldUpdateprojectionMatrix = true;
	}

	if (shouldUpdateprojectionMatrix)
	{
		ProjectionMatrix = glm::ortho(-AspectRatio * ZoomOutLevel, AspectRatio * ZoomOutLevel, -ZoomOutLevel, ZoomOutLevel);
	}
}