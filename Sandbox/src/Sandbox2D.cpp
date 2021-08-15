#include "Sandbox2D.h"
#include "Lambda/Core/EntryPoint.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtc/type_ptr.hpp"

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{

}

void Sandbox2D::OnAttach()
{
	LM_PROFILE_FUNCTION();

	m_CheckerboardTexture = Lambda::Texture2D::Create("assets/textures/Checkerboard.png");

}

void Sandbox2D::OnDetach()
{
	LM_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(Lambda::Timestep ts)
{
	LM_PROFILE_FUNCTION();
	// Update

	m_CameraController.OnUpdate(ts);

	// Render

	{
		LM_PROFILE_SCOPE("Renderer Prep");
		Lambda::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Lambda::RenderCommand::Clear();
	}

	{
		LM_PROFILE_SCOPE("Renderer Draw");
		Lambda::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Lambda::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Lambda::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Lambda::Renderer2D::DrawQuad({ -5.0f, -5.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
		Lambda::Renderer2D::DrawQuad({ -0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f }, m_CheckerboardTexture, 20.0f);
		Lambda::Renderer2D::EndScene();
	}

}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Lambda::Event& e)
{
	m_CameraController.OnEvent(e);
}
