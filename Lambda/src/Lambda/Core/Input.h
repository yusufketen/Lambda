#pragma once

#include <glm/glm.hpp>
#include "Lambda/Core/KeyCodes.h"
#include "Lambda/Core/MouseCodes.h"

namespace Lambda {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}