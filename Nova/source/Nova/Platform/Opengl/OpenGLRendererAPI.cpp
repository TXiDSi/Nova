#include "novapch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Nova {
	void OpenGLRendererAPI::Init()
	{
		glDepthMask(GL_TRUE);
		glEnable(GL_DEPTH_TEST);
	}
	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void OpenGLRendererAPI::DrawElements(unsigned int count)
	{
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);

	}
}