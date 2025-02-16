#include "novapch.h"
#include "RenderCommand.h"

#include "Nova/Platform/Opengl/OpenGLRendererAPI.h"

namespace Nova {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}