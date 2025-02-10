#pragma once

#include <string>
#include <stdint.h>

// Third party
#include "glm/glm.hpp"

class ShaderProgram
{
public:

	ShaderProgram(const std::string& inVertexShaderSource, const std::string& inFragmentShaderSource);
	~ShaderProgram();
	inline uint32_t GetProgramID() const { return ProgramID; }

	void UploadUniform(const std::string& uniformName, const glm::mat4& matrixUniform) const;
	void Bind() const;
	void UnBind() const;

private:

	uint32_t CreateAndCompileShader(const int type, const char* const source);
	void CreateAndCompileShaderProgram(const uint32_t vertexShaderID, const uint32_t fragmentShaderID);
	uint32_t ProgramID = 0;
};