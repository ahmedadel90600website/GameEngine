#pragma once

#include "Public/Core.h"

// std
#include <unordered_map>

class ShaderProgram;

class ShaderLibrary
{
public:

	TSharedPtr<ShaderProgram> LoadShader(const std::string& inFilePath);
	TSharedPtr<ShaderProgram> GetShader(const std::string& inShaderName);

private:

	bool DoesShaderAlreadyExist(const std::string& shaderName) const;

	std::unordered_map<std::string, TSharedPtr<ShaderProgram>> ShaderByNameMap;
};