#pragma once
#include "Lambda/Core/Base.h"

#include "Lambda/Core/Window.h"
#include "Lambda/Core/LayerStack.h"
#include "Lambda/Events/Event.h"
#include "Lambda/Events/ApplicationEvent.h"

#include "Lambda/Core/Timestep.h"

#include "Lambda/ImGui/ImGuiLayer.h"

namespace Lambda
{
	class Application
	{
	public:
		Application(const std::string& name = "Lambda App");
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		void Close();

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	// Should be defined in CLIENT
	Application* CreateApplication();
}
