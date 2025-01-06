#include "Public/PCH.h"
#include "Public/Input/Input.h"

bool Input::IsKeyDown(const int inKey)
{
	if (InputSingleton != nullptr)
	{
		return InputSingleton->IsKeyDownImplementation(inKey);
	}

	return false;
}

bool Input::IsAMouseKey(const int inKey)
{
	if (InputSingleton != nullptr)
	{
		return InputSingleton->IsAMouseKeyImplementation(inKey);
	}

	return false;
}

FVector2 Input::GetMousePosition()
{
	if (InputSingleton != nullptr)
	{
		return InputSingleton->GetMousePositionImplementation();
	}

	return FVector2();
}