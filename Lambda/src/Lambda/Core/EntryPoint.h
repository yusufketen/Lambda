#pragma once
#include "Lambda/Core/Base.h"

#ifdef LM_PLATFORM_WINDOWS

extern Lambda::Application* Lambda::CreateApplication();

int main(int argc, char** argv)
{
	Lambda::Log::Init();

	LM_PROFILE_BEGIN_SESSION("Startup", "LambdaProfile-Startup.json");
	auto app = Lambda::CreateApplication();
	LM_PROFILE_END_SESSION();

	LM_PROFILE_BEGIN_SESSION("Runtime", "LambdaProfile-Runtime.json");
	app->Run();
	LM_PROFILE_END_SESSION();

	LM_PROFILE_BEGIN_SESSION("Shutdown", "LambdaProfile-Shutdown.json");
	delete app;
	LM_PROFILE_END_SESSION();
}

#endif
