#pragma once

#include <memory>

#include "Lambda/Core/PlatformDetection.h"

#ifdef LM_DEBUG
#if defined(LM_PLATFORM_WINDOWS)
#define LM_DEBUGBREAK() __debugbreak()
#elif defined(LM_PLATFORM_LINUX)
#include <signal.h>
#define LM_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define LM_ENABLE_ASSERTS
#else
#define LM_DEBUGBREAK()
#endif

#define LM_EXPAND_MACRO(x) x
#define LM_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define LM_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Lambda {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}

#include "Lambda/Core/Log.h"
#include "Lambda/Core/Assert.h"