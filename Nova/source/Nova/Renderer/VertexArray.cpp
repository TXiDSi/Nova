#include "novapch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Nova/Platform/OpenGL/OpenGLVertexArray.h"

namespace Nova {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:    return nullptr;
		case RendererAPI::OpenGL:  return new OpenGLVertexArray();
		}
		return nullptr;
	}

}