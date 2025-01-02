#pragma once

#ifdef GameEngine_Platform_Windows
	#ifdef GameEngine_Build_DLL
		#define	GameEngine_API _declspec(dllexport)
	#else
		#define	GameEngine_API _declspec(dllimport)

	#endif

#else
	#error GameEngine supports windows only.

#endif

#ifdef GameEngine_AssertsEnabled
	#define GameEngine_Assert(x, ...) if(!(x)) {GameEngine_LOG(error, "Assertion failed: {0}", ##__VA_ARGS__); __debugbreak();}
#else
	#define GameEngine_Assert(x, ...)

#endif