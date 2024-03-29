﻿#pragma once

#include "Lambda.h"
#include "Panels/SceneHierarchyPanel.h"

namespace Lambda {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);

	private:
		Lambda::OrthographicCameraController m_CameraController;

		// Temp
		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_FlatColorShader;
		Ref<Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;
		Entity m_CameraEntity;
		Entity m_SecondCamera;

		Entity m_HoveredEntity;
		glm::ivec4 entityIDs = { -1, -1, -1, -1 };

		bool m_PrimaryCamera = true;
		bool m_VSyncActive = true;

		Ref<Texture2D> m_CheckerboardTexture;
		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = {0.0f, 0.0f};
		glm::vec2 m_ViewportBounds[2];

		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
		Entity m_ClickedEntity;
		bool needUpdateClickedEntity = false;

	};

}
