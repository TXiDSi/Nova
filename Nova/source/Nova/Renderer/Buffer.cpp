#include "novapch.h"
#include "Nova/Renderer/Buffer.h"

#include "Nova/Renderer/Renderer.h"
#include "Nova/Platform/OpenGL/OpenGLBuffer.h"

namespace Nova {

	std::shared_ptr<VertexBuffer> VertexBuffer::Create(const void* vertices, unsigned int size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}
		return nullptr;
	}

	std::shared_ptr <IndexBuffer> IndexBuffer::Create(unsigned int* indices, unsigned int size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared <OpenGLIndexBuffer>(indices, size);
		}

		return nullptr;
	}

}