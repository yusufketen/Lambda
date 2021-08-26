#pragma once


#include "Lambda/Core/Base.h"
#include "Lambda/Core/Log.h"

#ifdef LM_ENABLE_ASSERTS

namespace Lambda::Assert
{
	// Returns the simple file name rather than full path as suggested by LovelySanta
	constexpr const char* CurrentFileName(const char* path) {
		const char* file = path;
		while (*path)
		{
			if (*path == '/' || *path == '\\')
				file = ++path;
			else
				path++;
		}
		return file;
	}
}

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define LM_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { LM##type##ERROR(msg, __VA_ARGS__); LM_DEBUGBREAK(); } }
#define LM_INTERNAL_ASSERT_WITH_MSG(type, check, ...) LM_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define LM_INTERNAL_ASSERT_NO_MSG(type, check) LM_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", LM_STRINGIFY_MACRO(check), ::Lambda::Assert::CurrentFileName(__FILE__), __LINE__)

#define LM_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define LM_INTERNAL_ASSERT_GET_MACRO(...) LM_EXPAND_MACRO( LM_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, LM_INTERNAL_ASSERT_WITH_MSG, LM_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define LM_ASSERT(...) LM_EXPAND_MACRO( LM_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define LM_CORE_ASSERT(...) LM_EXPAND_MACRO( LM_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define LM_ASSERT(...)
#define LM_CORE_ASSERT(...)
#endif