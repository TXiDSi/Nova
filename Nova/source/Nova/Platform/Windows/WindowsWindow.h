#pragma once
#include <Nova/Core/Window.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Nova
{
	class WindowsWindow :public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		
		void SetEventCallback(const EventCallbackFn &callback) override
		{
			this->m_data.callback = callback;
		}

		void OnUpdate() override;
		void* GetNativeWindow() const override
		{
			return m_window;
		}


		unsigned int GetWidth() const override
		{
			return m_data.width;
		}
		unsigned int GetHeight() const override
		{
			return m_data.height;
		}

	private:

		virtual void Init(const WindowProps& props) ;


		GLFWwindow* m_window;
		struct WindowData
		{
			char* title;
			unsigned int width,height;
            EventCallbackFn callback;
		};
		WindowData m_data;


	};
}