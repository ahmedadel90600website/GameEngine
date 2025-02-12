#include "Public/PCH.h"

#include "Public/Rendering/Cameras/Camera.h"

// Third party
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"

Camera::Camera(const glm::mat4& inProjectionMatrix) :
	ProjectionMatrix(inProjectionMatrix)
{
	CalculateViewMatrix();
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

void Camera::CalculateViewMatrix()
{
	const glm::mat4& transform = glm::translate(glm::mat4(1.0f), Location) * glm::mat4(Rotation);
	ViewMatrix = glm::inverse(transform);
}