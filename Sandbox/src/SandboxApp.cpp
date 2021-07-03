#include <Lambda.h>

class Sandbox : public Lambda::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Lambda::Application* Lambda::CreateApplication()
{
	return new Sandbox();
}