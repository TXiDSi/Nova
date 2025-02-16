#include "novapch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Nova/Platform/Opengl/OpenGLTexture.h"

namespace Nova {

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(path);
		}

		return nullptr;
	}

}