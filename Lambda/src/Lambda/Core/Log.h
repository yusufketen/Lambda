#pragma once

#include "Lambda/Core/Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Lambda {

	class Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }



	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define LM_CORE_TRACE(...)		::Lambda::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LM_CORE_INFO(...)		::Lambda::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LM_CORE_WARN(...)		::Lambda::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LM_CORE_ERROR(...)		::Lambda::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LM_CORE_CRITICAL(...)	::Lambda::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define LM_TRACE(...)			::Lambda::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LM_INFO(...)			::Lambda::Log::GetClientLogger()->info(__VA_ARGS__)
#define LM_WARN(...)			::Lambda::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LM_ERROR(...)			::Lambda::Log::GetClientLogger()->error(__VA_ARGS__)
#define LM_CRITICAL(...)		::Lambda::Log::GetClientLogger()->critical(__VA_ARGS__)
