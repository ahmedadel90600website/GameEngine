#include "Public/PCH.h"

#include "Public/Rendering/Cameras/Camera.h"
#include "Public/Application.h"
#include "Public/Input/Input.h"

// Third party
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"

Camera::Camera(const glm::mat4& inProjectionMatrix) : ProjectionMatrix(inProjectionMatrix)
{
	CalculateViewMatrix();
	Application::GetWindowRef().GetOnWindowEvent().ADD_OBJECT(this, &Camera::OnWindowEvent);
}

void Camera::SetLocation(const glm::vec3& inPosition)
{
	Location = inPosition;
	CalculateViewMatrix();
}

void Camera::SetRotation(const glm::quat& inRotation)
{
	Rotation = inRotation;
	CalculateViewMatrix();
}

glm::mat4 Camera::GetViewProjectionMatrix() const
{
	return ProjectionMatrix * ViewMatrix;
}

void Camera::Tick(const float deltaTime)
{
	const float cameraSpeed = ZoomOutLevel * deltaTime;

	// Camera movement
	if (Input::IsKeyDown(GameEngineKeyCodes::KEY_W))
	{
		SetLocation(Location + glm::vec3(0.0f, cameraSpeed, 0.0f));
	}
	else if (Input::IsKeyDown(GameEngineKeyCodes::KEY_S))
	{
		SetLocation(Location + glm::vec3(0.0f, -cameraSpeed, 0.0f));
	}

	if (Input::IsKeyDown(GameEngineKeyCodes::KEY_D))
	{
		SetLocation(Location + glm::vec3(cameraSpeed, 0.0f, 0.0f));
	}
	else if (Input::IsKeyDown(GameEngineKeyCodes::KEY_A))
	{
		SetLocation(Location + glm::vec3(-cameraSpeed, 0.0f, 0.0f));
	}

	const float rotationSpeed = glm::radians(180.0f) * deltaTime;
	if (Input::IsKeyDown(GameEngineKeyCodes::KEY_E))
	{
		SetRotation(Rotation * glm::quat(glm::vec3(0.0f, 0.0f, -rotationSpeed)));
	}
	else if (Input::IsKeyDown(GameEngineKeyCodes::KEY_Q))
	{
		SetRotation(Rotation * glm::quat(glm::vec3(0.0f, 0.0f, rotationSpeed)));
	}

	GameEngine_LOG(info, "X: {0}, Y: {1}", Location.x, Location.y);
}

void Camera::CalculateViewMatrix()
{
	const glm::mat4& transform = glm::translate(glm::mat4(1.0f), Location) * glm::mat4(Rotation);
	ViewMatrix = glm::inverse(transform);
}