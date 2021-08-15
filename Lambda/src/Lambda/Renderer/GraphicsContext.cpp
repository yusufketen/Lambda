#include "lmpch.h"
#include "Lambda/Renderer/GraphicsContext.h"

#include "Lambda/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Lambda {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    LM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		LM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}