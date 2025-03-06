#include "Public/PCH.h"
#include "Public/Core.h"
#include "Public/Platforms/Rendering/OpenGL/OpenGLShaderProgram.h"
#include <stdint.h>
#include <fstream>

// Third party
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

OpenGLShaderProgram::OpenGLShaderProgram(const std::string& inShaderFilePath)
{
	GameEngine_Assert(inShaderFilePath.size() > 0, "Empty file path was passed");

	std::unordered_map<uint32_t, std::string> shaderSources;

	std::string result;
	std::ifstream in(inShaderFilePath, std::ios::in | std::ios::binary);
	if (in)
	{
		in.seekg(0, std::ios::end);
		result.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&result[0], result.size());
		in.close();
	}
	else
	{
		GameEngine_LOG(error, "Could not open file '{0}'", inShaderFilePath);
		return;
	}

	const char* const typeToken = "#type";
	const size_t typeTokenSize = strlen(typeToken);
	size_t pos = result.find(typeToken, 0);
	while (pos != std::string::npos)
	{
		const size_t lineEnd = result.find_first_of("\r\n", pos);
		GameEngine_Assert(lineEnd != std::string::npos, "Syntax error");

		const size_t typeTokenEnd = pos + typeTokenSize;
		const size_t beginingOfType = result.find_first_not_of(" ", typeTokenEnd);

		const std::string& finalTypeAsString = result.substr(beginingOfType, lineEnd - beginingOfType);

		uint32_t shaderType = GetShaderTypeFromString(finalTypeAsString);
		GameEngine_Assert(shaderType != 0, "Invalid shader type specified");

		const size_t nextLinePos = result.find_first_not_of("\r\n", lineEnd);
		GameEngine_Assert(shaderType != std::string::npos, "No new line after #type");

		pos = result.find(typeToken, nextLinePos);
		shaderSources[shaderType] = result.substr(nextLinePos, (pos == std::string::npos ? (result.size()) : pos) - nextLinePos);
	}

	GameEngine_Assert(shaderSources.size() <= MaxNumberOfShaders, "Can't handle more than 4 shaders for now. OpenGLShaderProgram::OpenGLShaderProgram");
	std::array<uint32_t, MaxNumberOfShaders> shaders;
	uint8_t counter = 0;
	for (const std::pair<uint32_t, std::string>& currentShaderTypeAndSource : shaderSources)
	{
		shaders[counter] = (CreateAndCompileShader(currentShaderTypeAndSource.first, currentShaderTypeAndSource.second.c_str()));
		++counter;
	}

	CreateAndCompileShaderProgram(shaders);

	const size_t indexOfLastBackOrForwardSlash = inShaderFilePath.find_last_of("/\\");
	const size_t indexOfLastDot = inShaderFilePath.find_last_of('.');
	GameEngine_Assert(indexOfLastDot != std::string::npos, "Shader file must have an extension. Example: .glsl");

	const size_t indexOfLastLetterInShaderName = indexOfLastDot - 1;
	if (indexOfLastBackOrForwardSlash == std::string::npos)
	{
		ShaderName = inShaderFilePath.substr(0, indexOfLastLetterInShaderName);
	}
	else
	{
		ShaderName = inShaderFilePath.substr(indexOfLastBackOrForwardSlash + 1, indexOfLastLetterInShaderName - indexOfLastBackOrForwardSlash);
	}
}

OpenGLShaderProgram::OpenGLShaderProgram(const std::string& inVertexShaderSource, const std::string& inFragmentShaderSource)
{
	std::array<uint32_t, MaxNumberOfShaders> shaders;
	shaders[0] = CreateAndCompileShader(GL_VERTEX_SHADER, inVertexShaderSource.c_str());
	shaders[1] = CreateAndCompileShader(GL_FRAGMENT_SHADER, inFragmentShaderSource.c_str());
	CreateAndCompileShaderProgram(shaders);
}

OpenGLShaderProgram::~OpenGLShaderProgram()
{
	glDeleteProgram(ProgramID);
}

uint32_t OpenGLShaderProgram::GetShaderTypeFromString(const std::string& inString) const
{
	if (inString == "Vertex" || inString == "vertex")
	{
		return GL_VERTEX_SHADER;
	}
	else if (inString == "Fragment" || inString == "fragment" || inString == "Pixel" || inString == "pixel")
	{
		return GL_FRAGMENT_SHADER;
	}

	return 0;
}

const std::string& OpenGLShaderProgram::GetName() const
{
	return ShaderName;
}

void OpenGLShaderProgram::UploadUniform(const std::string& uniformName, const glm::mat3& matrixUniform)
{
	glUniformMatrix3fv(GetAddUniformLocation(uniformName.c_str()), 1, false, glm::value_ptr(matrixUniform));
}

void OpenGLShaderProgram::UploadUniform(const std::string& uniformName, const glm::mat4& matrixUniform)
{
	glUniformMatrix4fv(GetAddUniformLocation(uniformName.c_str()), 1, false, glm::value_ptr(matrixUniform));
}

void OpenGLShaderProgram::UploadUniform(const std::string& uniformName, const int32_t inInteger)
{
	glUniform1i(GetAddUniformLocation(uniformName.c_str()), inInteger);
}

void OpenGLShaderProgram::UploadUniform(const std::string& uniformName, const float inFloat)
{
	glUniform1f(GetAddUniformLocation(uniformName.c_str()), inFloat);
}

void OpenGLShaderProgram::UploadUniform(const std::string& uniformName, const glm::vec2& vector)
{
	glUniform2f(GetAddUniformLocation(uniformName.c_str()), vector.x, vector.y);
}

void OpenGLShaderProgram::UploadUniform(const std::string& uniformName, const glm::vec3& vector)
{
	glUniform3f(GetAddUniformLocation(uniformName.c_str()), vector.x, vector.y, vector.z);
}

void OpenGLShaderProgram::UploadUniform(const std::string& uniformName, const glm::vec4& vector)
{
	glUniform4f(GetAddUniformLocation(uniformName.c_str()), vector.x, vector.y, vector.z, vector.a);
}

void OpenGLShaderProgram::Bind() const
{
	glUseProgram(ProgramID);
}

void OpenGLShaderProgram::UnBind() const
{
	glUseProgram(0);
}

uint32_t OpenGLShaderProgram::GetAddUniformLocation(const std::string& uniformName)
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

void OpenGLShaderProgram::CreateAndCompileShaderProgram(const std::array<uint32_t, MaxNumberOfShaders>& inShaders)
{
	ProgramID = glCreateProgram();

	for (const uint32_t currentShader : inShaders)
	{
		glAttachShader(ProgramID, currentShader);
	}

	glLinkProgram(ProgramID);

	int isLinked = 0;
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &isLinked);
	if (!isLinked)
	{
		GLint maxLength = 0;
		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &maxLength);

		char* infoLog = (char*)alloca(maxLength * sizeof(char));
		glGetProgramInfoLog(ProgramID, maxLength, &maxLength, &infoLog[0]);
		for (const uint32_t currentShader : inShaders)
		{
			glDetachShader(ProgramID, currentShader);
			glDeleteShader(currentShader);
		}

		glDeleteProgram(ProgramID);
		GameEngine_LOG(error, "{0}", infoLog);
		GameEngine_Assert(false, "Wasn't able to compile the shader program");

		return;
	}

	for (const uint32_t currentShader : inShaders)
	{
		glDetachShader(ProgramID, currentShader);
		glDeleteShader(currentShader);
	}
}