#include "Public/PCH.h"
#include "Public/Rendering/RenderCommand.h"
#include "Public/Platforms/Rendering/OpenGL/OpenGLRendererAPI.h"

#include <memory>

TSharedPtr<RendererAPI> RenderCommand::TheRendererAPI = nullptr;
const TSharedPtr<RendererAPI>& RenderCommand::GetTheRendererAPI()
{
	return TheRendererAPI;
}

void RenderCommand::Init()
{
	if (TheRendererAPI == nullptr)
	{
		const ERendererAPIType renderAPIType = RendererAPI::GetTheRendererAPIType();
		if (renderAPIType == ERendererAPIType::NONE)
		{
			GameEngine_Assert(false, "RenderCommand::GetTheRendererAPI. No API specified.");
		}
		else if (renderAPIType == ERendererAPIType::OPENGL)
		{
			TheRendererAPI = TMakeShared<OpenGLRendererAPI>();
		}
	}

	GameEngine_Assert(TheRendererAPI != nullptr, "RenderCommand::GetTheRendererAPI. No API was created.");
	TheRendererAPI->Init();
}