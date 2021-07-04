#pragma once

#ifdef LM_PLATFORM_WINDOWS
	#ifdef LM_BUILD_DLL
		#define LAMBDA_API __declspec(dllexport)
	#else
		#define LAMBDA_API __declspec(dllimport)
	#endif
#else
	#error Lambda only supports Windows!
#endif

#define BIT(x) (1 << x)