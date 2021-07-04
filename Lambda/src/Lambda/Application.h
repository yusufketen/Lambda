#pragma once
#include "Core.h"
#include "Events/Event.h"

namespace Lambda {
	class LAMBDA_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	// Should be defined in CLIENT
	Application* CreateApplication();
}

