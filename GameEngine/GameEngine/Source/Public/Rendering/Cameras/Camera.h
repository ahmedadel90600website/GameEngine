#pragma once

// Third party
#include "glm/glm.hpp"
#include "glm/detail/type_quat.hpp"

class Camera
{
public:

	Camera(const glm::mat4& inProjectionMatrix);
	void SetLocation(const glm::vec3& inPosition);
	void SetRotation(const glm::quat& inRotation);

	glm::mat4 GetViewProjectionMatrix() const;
	inline const glm::mat4& GetProjectionMatrix() const { return ProjectionMatrix; }
	inline const glm::mat4& GetViewMatrix() const { return ViewMatrix; }
	inline const glm::vec3& GetLocation() const { return Location; }
	inline const glm::quat& GetRotation() const { return Rotation; }

private:

	void CalculateViewMatrix();

	glm::mat4 ProjectionMatrix = glm::mat4(1.0f);
	glm::mat4 ViewMatrix = glm::mat4(1.0f);

	glm::quat Rotation = glm::quat(glm::highp_vec3(0.0f));
	glm::vec3 Location = glm::vec3(0.0f);
};