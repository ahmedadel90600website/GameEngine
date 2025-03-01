#pragma once

// Third party
#include "glm/glm.hpp"
#include "glm/detail/type_quat.hpp"

struct FEventDataBase;

class Camera
{
protected:

	Camera(const glm::mat4& inProjectionMatrix);

public:

	void SetLocation(const glm::vec3& inPosition);
	void SetRotation(const glm::quat& inRotation);

	glm::mat4 GetViewProjectionMatrix() const;
	inline const glm::mat4& GetProjectionMatrix() const { return ProjectionMatrix; }
	inline const glm::mat4& GetViewMatrix() const { return ViewMatrix; }
	inline const glm::vec3& GetLocation() const { return Location; }
	inline const glm::quat& GetRotation() const { return Rotation; }

	virtual void OnWindowEvent(FEventDataBase* theEvent) {};
	virtual void Tick(const float deltaTime);

protected:

	void CalculateViewMatrix();

	glm::mat4 ProjectionMatrix = glm::mat4(1.0f);

private:

	glm::mat4 ViewMatrix = glm::mat4(1.0f);
	glm::quat Rotation = glm::quat(glm::highp_vec3(0.0f));
	glm::vec3 Location = glm::vec3(0.0f);


protected:

	float ZoomOutLevel = 1.0f;
	float MinZoomOutLevel = 0.1f;
	float ZoomOutLevelMultiplier = 0.25f;
	float AspectRatio = 1.0f;
};