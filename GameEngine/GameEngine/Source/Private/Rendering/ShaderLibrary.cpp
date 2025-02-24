#include "Public/PCH.h"
#include "Public/Rendering/ShaderLibrary.h"
#include "Public/Rendering/ShaderProgram.h"

TSharedPtr<ShaderProgram> ShaderLibrary::LoadShader(const std::string& inFilePath)
{
	TSharedPtr<ShaderProgram> shader = ShaderProgram::Create(inFilePath);
	GameEngine_Assert(shader != nullptr, "ShaderLibrary::LoadShader. Invalid shader!");

	const std::string& shaderName = shader->GetName();
	if (DoesShaderAlreadyExist(inFilePath))
	{
		GameEngine_LOG(warn, "ShaderLibrary::LoadShader. Trying to add an already existing shader.");
		return nullptr;
	}

	ShaderByNameMap[shaderName] = shader;
	return shader;
}

TSharedPtr<ShaderProgram> ShaderLibrary::GetShader(const std::string& inShaderName)
{
	if (DoesShaderAlreadyExist(inShaderName))
	{
		return ShaderByNameMap[inShaderName];
	}

	return nullptr;
}

bool ShaderLibrary::DoesShaderAlreadyExist(const std::string& shaderName) const
{
	return ShaderByNameMap.find(shaderName) != ShaderByNameMap.end();
}