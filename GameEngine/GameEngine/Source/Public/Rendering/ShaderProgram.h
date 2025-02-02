#pragma once

class ShaderProgram
{
public:

	ShaderProgram(const std::string& inVertexShaderSource, const std::string& inFragmentShaderSource);
	~ShaderProgram();
	inline unsigned int GetProgramID() const { return ProgramID; }

	void Bind();
	void UnBind();

private:

	unsigned int CreateAndCompileShader(const int type, const char* const source);
	void CreateAndCompileShaderProgram(const unsigned int vertexShaderID, const unsigned int fragmentShaderID);
	unsigned int ProgramID = 0;
};