#include <Lambda.h>

class ExampleLayer : public Lambda::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		LM_INFO("ExampleLayer::Update");
	}

	void OnEvent(Lambda::Event& event) override
	{
		LM_TRACE("{0}", event);
	}

};

class Sandbox : public Lambda::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Lambda::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Lambda::Application* Lambda::CreateApplication()
{
	return new Sandbox();
}