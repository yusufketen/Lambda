#pragma once

#ifdef LM_PLATFORM_WINDOWS
#if LM_DYNAMIC_LINK
	#ifdef LM_BUILD_DLL
		#define LAMBDA_API __declspec(dllexport)
	#else
		#define LAMBDA_API __declspec(dllimport)
	#endif
#else
	#define LAMBDA_API
#endif
#else
	#error Lambda only supports Windows!
#endif

#ifdef LM_DEBUG
#define LM_ENABLE_ASSERTS
#endif

#ifdef LM_ENABLE_ASSERTS
#define LM_ASSERT(x, ...) { if(!(x)) { LM_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define LM_CORE_ASSERT(x, ...) { if(!(x)) { LM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define LM_ASSERT(x, ...)
#define LM_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define LM_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)