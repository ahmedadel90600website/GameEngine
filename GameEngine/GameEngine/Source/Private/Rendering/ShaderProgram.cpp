#include "Public/PCH.h"
#include "Public/Rendering/ShaderProgram.h"

// Third party
#include "glad/glad.h"

ShaderProgram::ShaderProgram(const std::string& inVertexShaderSource, const std::string& inFragmentShaderSource)
{
	const unsigned int vertexShader = CreateAndCompileShader(GL_VERTEX_SHADER, inVertexShaderSource.c_str());
	const unsigned int fragmentShader = CreateAndCompileShader(GL_FRAGMENT_SHADER, inFragmentShaderSource.c_str());
	CreateAndCompileShaderProgram(vertexShader, fragmentShader);
}
ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(ProgramID);
}

void ShaderProgram::Bind()
{
	glUseProgram(ProgramID);
}

void ShaderProgram::UnBind()
{
	glUseProgram(0);
}

unsigned int ShaderProgram::CreateAndCompileShader(const int type, const char* const source)
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

void ShaderProgram::CreateAndCompileShaderProgram(const unsigned int vertexShaderID, const unsigned int fragmentShaderID)
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