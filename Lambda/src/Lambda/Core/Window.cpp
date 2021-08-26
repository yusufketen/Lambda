#include "lmpch.h"
#include "Lambda/Core/Window.h"

#ifdef LM_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Lambda
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef LM_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		LM_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}

}
