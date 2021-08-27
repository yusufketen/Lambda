#pragma once

#include "Lambda/Core/Layer.h"

#include "Lambda/Events/ApplicationEvent.h"
#include "Lambda/Events/KeyEvent.h"
#include "Lambda/Events/MouseEvent.h"

namespace Lambda {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

		void SetDarkThemeColors();

	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};
}
