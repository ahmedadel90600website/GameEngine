#pragma once
#include "Public/Core.h"

class ShaderProgram
{
public:

	static TSharedPtr<ShaderProgram> Create(const std::string& inVertexShaderSource, const std::string& inFragmentShaderSource);

	virtual ~ShaderProgram() {}
	virtual void Bind() const = 0;
	virtual void UnBind() const = 0;
};