#include "Application.h"

#include "Lambda/Events/ApplicationEvent.h"
#include "Lambda/Log.h"

namespace Lambda {

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		LM_TRACE(e);

		while (true);
	}

}
