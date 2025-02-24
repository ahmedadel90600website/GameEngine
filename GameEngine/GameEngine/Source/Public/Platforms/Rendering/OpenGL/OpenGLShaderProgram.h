#pragma once

#include "Public/Rendering/ShaderProgram.h"
#include <string>
#include <stdint.h>
#include <unordered_map>
#include <array>

// Third party
#include "glm/glm.hpp"

static constexpr uint8_t MaxNumberOfShaders = 4;
class OpenGLShaderProgram : public ShaderProgram
{
public:

	OpenGLShaderProgram(const std::string& inShaderFilePath);
	OpenGLShaderProgram(const std::string& inVertexShaderSource, const std::string& inFragmentShaderSource);
	virtual ~OpenGLShaderProgram();

	uint32_t GetShaderTypeFromString(const std::string& inString) const;
	inline uint32_t GetProgramID() const { return ProgramID; }

	const std::string& GetName() const override;

	void UploadUniform(const std::string& uniformName, const glm::mat3& matrixUniform);
	void UploadUniform(const std::string& uniformName, const glm::mat4& matrixUniform);

	void UploadUniform(const std::string& uniformName, const int32_t inInteger);
	void UploadUniform(const std::string& uniformName, const float inFloat);
	void UploadUniform(const std::string& uniformName, const glm::vec2& vector);
	void UploadUniform(const std::string& uniformName, const glm::vec3& vector);
	void UploadUniform(const std::string& uniformName, const glm::vec4& vector);

	void Bind() const override;
	void UnBind() const override;

private:

	uint32_t GetUniformLocation(const std::string& uniformName);
	uint32_t CreateAndCompileShader(const int type, const char* const source);
	void CreateAndCompileShaderProgram(const std::array<uint32_t, MaxNumberOfShaders>& inShaders);

	std::unordered_map<std::string, uint32_t> UniformByName;
	std::string ShaderName = "";
	uint32_t ProgramID = 0;
};