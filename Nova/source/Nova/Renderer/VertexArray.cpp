#include "novapch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Nova/Platform/OpenGL/OpenGLVertexArray.h"

namespace Nova {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLVertexArray();
		}
		return nullptr;
	}

}