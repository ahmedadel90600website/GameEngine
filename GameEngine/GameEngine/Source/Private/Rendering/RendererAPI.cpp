#include "Public/PCH.h"
#include "Public/Rendering/RendererAPI.h"
#include "Public/Platforms/Rendering/OpenGL/OpenGLRendererAPI.h"
#include "Public/Core.h"


TSharedPtr<RendererAPI> RendererAPI::TheRendererAPI = nullptr;
ERendererAPIType RendererAPI::APIType = ERendererAPIType::OPENGL;

const TSharedPtr<RendererAPI>& RendererAPI::GetTheRendererAPI()
{
	if (TheRendererAPI == nullptr)
	{
		if (APIType == ERendererAPIType::NONE)
		{
			GameEngine_Assert(false, "RendererAPI::GetTheRendererAPI. No API specified.");
		}
		else if(APIType == ERendererAPIType::OPENGL)
		{
			TheRendererAPI = std::make_shared<OpenGLRendererAPI>();
		}
	}

	GameEngine_Assert(TheRendererAPI != nullptr, "RendererAPI::GetTheRendererAPI. No API was created.");

	return TheRendererAPI;
}