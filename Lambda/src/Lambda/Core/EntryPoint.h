#pragma once

#ifdef LM_PLATFORM_WINDOWS

extern Lambda::Application* Lambda::CreateApplication();

int main()
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