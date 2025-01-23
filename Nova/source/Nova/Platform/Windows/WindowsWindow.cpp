#include "NovaPch.h"
#include "WindowsWindow.h"
#include <Nova/Core/Log.h>
#include <Nova/Event/KeyEvent.h>
namespace Nova
{
	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		this->Init(props);
	}

	void WindowsWindow::Init(const WindowProps &props) 
	{
		m_data.title = props.title;
		m_data.width = props.width;
		m_data.height = props.height;

#ifdef GLFW_INIT
#else
		int success = glfwInit();
		if (!success)
		{
			NOVA_CORE_ERROR("GLFW INIT FAILED");
			return;
		}
#define GLFW_INIT
#endif
		this->m_window = glfwCreateWindow(props.width, props.height, props.title, NULL, NULL);
		if (!this->m_window)
		{
			NOVA_CORE_ERROR("GLFW CREATE WINDOW FAILED");
			return;
		}

		glfwSetWindowUserPointer(m_window, &m_data);

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				auto data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
				case GLFW_PRESS:
				{
					OnKeyDownEvent event(key);
					data.callback(event);
					break;
				}
					
				case GLFW_RELEASE:
				{
					OnKeyUpEvent event(key);
					data.callback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					break;
				}
					
				}

			});

	}


	

}