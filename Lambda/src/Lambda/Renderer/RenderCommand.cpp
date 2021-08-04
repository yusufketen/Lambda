#include "lmpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Lambda
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}