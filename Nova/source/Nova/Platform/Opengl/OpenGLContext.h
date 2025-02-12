#pragma once

#include "Nova/Renderer/RendererContext.h"

struct GLFWwindow;

namespace Nova {

	class OpenGLContext : public RendererContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}