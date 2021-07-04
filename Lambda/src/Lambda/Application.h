#pragma once
#include "Core.h"

#include "Window.h"
#include "Lambda/LayerStack.h"
#include "Lambda/Events/Event.h"
#include "Lambda/Events/ApplicationEvent.h"

namespace Lambda {
	class LAMBDA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// Should be defined in CLIENT
	Application* CreateApplication();
}

