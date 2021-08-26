#pragma once

#include "Lambda/Core/Base.h"

#include "Lambda/Core/Window.h"
#include "Lambda/Core/LayerStack.h"
#include "Lambda/Events/Event.h"
#include "Lambda/Events/ApplicationEvent.h"

#include "Lambda/Core/Timestep.h"

#include "Lambda/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace Lambda {

	class Application
	{
	public:
		Application(const std::string& name = "Lambda App");
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		Window& GetWindow() { return *m_Window; }

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		static Application& Get() { return *s_Instance; }
	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}
