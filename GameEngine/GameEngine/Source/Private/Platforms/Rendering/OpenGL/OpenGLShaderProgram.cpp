#include "Public/PCH.h"
#include "Public/Platforms/Rendering/OpenGL/OpenGLShaderProgram.h"

// Third party
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

OpenGLShaderProgram::OpenGLShaderProgram(const std::string& inVertexShaderSource, const std::string& inFragmentShaderSource)
{
	const unsigned int vertexShader = CreateAndCompileShader(GL_VERTEX_SHADER, inVertexShaderSource.c_str());
	const unsigned int fragmentShader = CreateAndCompileShader(GL_FRAGMENT_SHADER, inFragmentShaderSource.c_str());
	CreateAndCompileShaderProgram(vertexShader, fragmentShader);
}

OpenGLShaderProgram::~OpenGLShaderProgram()
{
	glDeleteProgram(ProgramID);
}

void OpenGLShaderProgram::UploadUniform(const std::string& uniformName, const glm::mat3& matrixUniform)
{
	glUniformMatrix3fv(GetUniformLocation(uniformName.c_str()), 1, false, glm::value_ptr(matrixUniform));
}

void OpenGLShaderProgram::UploadUniform(const std::string& uniformName, const glm::mat4& matrixUniform)
{
	glUniformMatrix4fv(GetUniformLocation(uniformName.c_str()), 1, false, glm::value_ptr(matrixUniform));
}

void OpenGLShaderProgram::UploadUniform(const std::string& uniformName, const float inFloat)
{
	glUniform1f(GetUniformLocation(uniformName.c_str()), inFloat);
}

void OpenGLShaderProgram::UploadUniform(const std::string& uniformName, const glm::vec2& vector)
{
	glUniform2f(GetUniformLocation(uniformName.c_str()), vector.x, vector.y);
}

void OpenGLShaderProgram::UploadUniform(const std::string& uniformName, const glm::vec3& vector)
{
	glUniform3f(GetUniformLocation(uniformName.c_str()), vector.x, vector.y, vector.z);
}

void OpenGLShaderProgram::UploadUniform(const std::string& uniformName, const glm::vec4& vector)
{
	glUniform4f(GetUniformLocation(uniformName.c_str()), vector.x, vector.y, vector.z, vector.a);
}

void OpenGLShaderProgram::Bind() const
{
	glUseProgram(ProgramID);
}

void OpenGLShaderProgram::UnBind() const
{
	glUseProgram(0);
}

uint32_t OpenGLShaderProgram::GetUniformLocation(const std::string& uniformName)
{
	if (UniformByName.find(uniformName) != UniformByName.end())
	{
		return UniformByName[uniformName];
	}

	const uint32_t uniformLocation = glGetUniformLocation(ProgramID, uniformName.c_str());
	UniformByName[uniformName] = uniformLocation;
	return uniformLocation;
}

	unsigned int OpenGLShaderProgram::CreateAndCompileShader(const int type, const char* const source)
	{
	unsigned int shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, &source, 0);
	glCompileShader(shaderID);

	int isCompiled = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
	if (!isCompiled)
	{
		int maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);
		char* infoLog = (char*)alloca(maxLength * sizeof(char));
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, infoLog);
		glDeleteShader(shaderID);

		GameEngine_LOG(error, "{0}", infoLog);
		GameEngine_Assert(false, "Wasn't able to compile the vertex shader");

		return 0;
	}

	return shaderID;
}

void OpenGLShaderProgram::CreateAndCompileShaderProgram(const uint32_t vertexShaderID, const uint32_t fragmentShaderID)
{
	ProgramID = glCreateProgram();

	glAttachShader(ProgramID, vertexShaderID);
	glAttachShader(ProgramID, fragmentShaderID);
	glLinkProgram(ProgramID);

	int isLinked = 0;
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &isLinked);
	if (!isLinked)
	{
		GLint maxLength = 0;
		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &maxLength);

		char* infoLog = (char*)alloca(maxLength * sizeof(char));
		glGetProgramInfoLog(ProgramID, maxLength, &maxLength, &infoLog[0]);
		glDeleteProgram(ProgramID);
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);

		GameEngine_LOG(error, "{0}", infoLog);
		GameEngine_Assert(false, "Wasn't able to compile the shader program");
	}

	glDetachShader(ProgramID, vertexShaderID);
	glDetachShader(ProgramID, fragmentShaderID);
}