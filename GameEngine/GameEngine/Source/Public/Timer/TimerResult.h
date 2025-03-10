#pragma once

struct FTimerResult
{
	FTimerResult() {}
	FTimerResult(const char* const inTimerName, const float inDuration) :
		TimerName(inTimerName),
		TimerDuration(inDuration)
	{

	}

	const char* TimerName = nullptr;
	float TimerDuration = 0.0f;
};