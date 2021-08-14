#pragma once

#include "Lambda/Core/Layer.h"

#include "Lambda/Events/ApplicationEvent.h"
#include "Lambda/Events/KeyEvent.h"
#include "Lambda/Events/MouseEvent.h"

namespace Lambda {

	class LAMBDA_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}