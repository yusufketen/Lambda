﻿#include "lmpch.h"

#include "Lambda/Renderer/OrthographicCameraController.h"

#include "Lambda/Core/Input.h"
#include "Lambda/Core/KeyCodes.h"

namespace Lambda {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		LM_PROFILE_FUNCTION();

		if (Input::IsKeyPressed(Key::A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(Key::D))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;

		if (Input::IsKeyPressed(Key::W))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(Key::S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(Key::Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			if (Input::IsKeyPressed(Key::E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		LM_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(LM_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(LM_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	void OrthographicCameraController::OnResize(float width, float height)
	{
		m_AspectRatio = width / height;
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		LM_PROFILE_FUNCTION();

		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		LM_PROFILE_FUNCTION();

		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}

}