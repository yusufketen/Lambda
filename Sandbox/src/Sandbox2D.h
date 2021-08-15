#pragma once
#include "Lambda.h"

class Sandbox2D : public Lambda::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Lambda::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Lambda::Event& e) override;
private:
	Lambda::OrthographicCameraController m_CameraController;

	// Temp
	Lambda::Ref<Lambda::VertexArray> m_SquareVA;
	Lambda::Ref<Lambda::Shader> m_FlatColorShader;

	Lambda::Ref<Lambda::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};
