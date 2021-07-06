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
		if (Lambda::Input::IsKeyPressed(LM_KEY_TAB))
			LM_TRACE("Tab key is pressed (poll)!");
	}

	void OnEvent(Lambda::Event& event) override
	{
		if (event.GetEventType() == Lambda::EventType::KeyPressed)
		{
			Lambda::KeyPressedEvent& e = (Lambda::KeyPressedEvent&)event;
			if (e.GetKeyCode() == LM_KEY_TAB)
				LM_TRACE("Tab key is pressed (event)!");
			LM_TRACE("{0}", (char)e.GetKeyCode());
		}
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