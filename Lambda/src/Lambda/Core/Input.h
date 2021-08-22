#pragma once

#include "Lambda/Core/Base.h"
#include "Lambda/Core/KeyCodes.h"
#include "Lambda/Core/MouseCodes.h"

namespace Lambda {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}