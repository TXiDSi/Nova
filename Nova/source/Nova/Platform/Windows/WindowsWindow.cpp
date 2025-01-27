#include "NovaPch.h"
#include "WindowsWindow.h"
#include <Nova/Core/Log.h>
#include <Nova/Event/KeyEvent.h>
#include <Nova/Event/WindowEvent.h>
#include <Nova/Event/MouseEvent.h>


namespace Nova
{
	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		this->Init(props);
		
	}

	void WindowsWindow::OnUpdate()
	{
		glfwSwapBuffers(m_window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

		//TODO tianxin：创建上下文测试GLAD，但目前GLAD在这初始化不一定正确，如果未来有问题再调整
		glfwMakeContextCurrent(m_window);

		success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if(success)
		NOVA_CORE_INFO("GLAD INIT SUCCESS");

		glClearColor(1, 0, 1, 1);
		glViewport(0, 0, props.width, props.height);
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


		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
			auto data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS :
				{
					MouseButtonDownEvent event(button);
					data.callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonUpEvent event(button);
					data.callback(event);
					break;
				}
			}

			});
		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {
			auto data = *(WindowData*)glfwGetWindowUserPointer(window);
		MouseMoveEvent event(xpos, ypos);
		data.callback(event);
			});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
			auto data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.callback(event);
			});

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
			auto data = *(WindowData*)glfwGetWindowUserPointer(window);
		WindowResizeEvent event(width, height);
		data.callback(event);
			});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset) {
			auto data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrollEvent event(xoffset, yoffset);
			data.callback(event);
			});

	}


	

}