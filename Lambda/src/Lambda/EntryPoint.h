#pragma once

#ifdef LM_PLATFORM_WINDOWS

extern Lambda::Application* Lambda::CreateApplication();

int main()
{
	auto app = Lambda::CreateApplication();
	app->Run();
	delete app;
}

#endif