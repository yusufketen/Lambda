﻿#include "lmpch.h"

#include "Lambda/Renderer/RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Lambda
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create()
	{
		LM_PROFILE_FUNCTION();

		switch (s_API)
		{
			case RendererAPI::API::None:    LM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLRendererAPI>();
		}

		LM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}