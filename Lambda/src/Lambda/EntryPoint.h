#pragma once

#ifdef LM_PLATFORM_WINDOWS

extern Lambda::Application* Lambda::CreateApplication();

int main()
{
	Lambda::Log::Init();

	LM_CORE_WARN("Initialized Log!");
	LM_INFO("Hello!");
	LM_CRITICAL("TEST FATAL!");

	auto app = Lambda::CreateApplication();
	app->Run();
	delete app;
}

#endif