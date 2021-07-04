#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Lambda {

	class LAMBDA_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }



	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
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
