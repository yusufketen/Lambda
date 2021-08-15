#include "lmpch.h"

#include "Lambda/Renderer/RenderCommand.h"

namespace Lambda
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}