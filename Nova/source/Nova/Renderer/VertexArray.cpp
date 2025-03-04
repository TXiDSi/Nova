#include "novapch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Nova/Platform/OpenGL/OpenGLVertexArray.h"

namespace Nova {

	std::shared_ptr<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLVertexArray>();
		}
		return nullptr;
	}

}