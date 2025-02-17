#pragma once
#include <memory>

class ShaderProgram
{
public:

	static std::shared_ptr<ShaderProgram> Create(const std::string& inVertexShaderSource, const std::string& inFragmentShaderSource);

	virtual ~ShaderProgram() {}
	virtual void Bind() const = 0;
	virtual void UnBind() const = 0;
};