#include "novapch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Nova/Platform/Opengl/OpenGLShader.h"

namespace Nova {

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLShader(vertexSrc, fragmentSrc);
		}
		return nullptr;
	}

}