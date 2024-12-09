#pragma once

#include <cstdint>
#include <string>

#ifdef GameEngine_Platform_Windows
	#ifdef GameEngine_Build_DLL
		#define	GameEngine_API _declspec(dllexport)
	#else
		#define	GameEngine_API _declspec(dllimport)

	#endif

#else
	#error GameEngine supports windows only.

#endif