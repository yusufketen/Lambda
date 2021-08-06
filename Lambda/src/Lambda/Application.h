#pragma once
#include "Core.h"

#include "Window.h"
#include "Lambda/LayerStack.h"
#include "Lambda/Events/Event.h"
#include "Lambda/Events/ApplicationEvent.h"

#include "Lambda/ImGui/ImGuiLayer.h"

#include "Lambda/Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/OrthographicCamera.h"
#include "Renderer/VertexArray.h"

namespace Lambda
{
	class LAMBDA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;


	private:
		static Application* s_Instance;
	};

	// Should be defined in CLIENT
	Application* CreateApplication();
}
