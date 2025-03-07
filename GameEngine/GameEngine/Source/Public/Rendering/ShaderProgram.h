#pragma once
#include "Public/Core.h"

#include <stdint.h>
#include "glm/glm.hpp"

class ShaderProgram
{
public:

	static TSharedPtr<ShaderProgram> Create(const std::string& inShaderFilePath);
	static TSharedPtr<ShaderProgram> Create(const std::string& inVertexShaderSource, const std::string& inFragmentShaderSource);

	virtual void SetUniform(const std::string& uniformName, const glm::mat3& matrixUniform) = 0;
	virtual void SetUniform(const std::string& uniformName, const glm::mat4& matrixUniform) = 0;

	virtual void SetUniform(const std::string& uniformName, const int32_t inInteger) = 0;
	virtual void SetUniform(const std::string& uniformName, const float inFloat) = 0;
	virtual void SetUniform(const std::string& uniformName, const glm::vec2& vector) = 0;
	virtual void SetUniform(const std::string& uniformName, const glm::vec3& vector) = 0;
	virtual void SetUniform(const std::string& uniformName, const glm::vec4& vector) = 0;

	virtual ~ShaderProgram() {}
	virtual void Bind() const = 0;
	virtual void UnBind() const = 0;
	virtual const std::string& GetName() const = 0;
};