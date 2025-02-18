#include "Public/PCH.h"
#include "Public/Rendering/ShaderProgram.h"
#include <string>
#include "Public/Rendering/RendererAPI.h"
#include "Public/Core.h"
#include "Public/Platforms/Rendering/OpenGL/OpenGLShaderProgram.h"

TSharedPtr<ShaderProgram> ShaderProgram::Create(const std::string& inVertexShaderSource, const std::string& inFragmentShaderSource)
{
	const ERendererAPIType rendererAPIType = RendererAPI::GetTheRendererAPIType();
	if (rendererAPIType == ERendererAPIType::NONE)
	{
		GameEngine_Assert(false, "ShaderProgram::Create no API specified");
		return nullptr;
	}
	else if (rendererAPIType == ERendererAPIType::OPENGL)
	{
		return std::make_shared<OpenGLShaderProgram>(inVertexShaderSource, inFragmentShaderSource);
	}

	GameEngine_Assert(false, "ShaderProgram::Create. Unsupported API");
	return nullptr;
}