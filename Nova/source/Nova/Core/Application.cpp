#include "NovaPch.h"
#include "Nova/Core/Log.h"
#include "Application.h"
#include "Nova/Core/Window.h"
#include "Nova/Event/KeyEvent.h"
#include "Nova/Event/WindowEvent.h"
#include <functional>

namespace Nova
{
	Application::Application()
	{
		//创建窗口
		m_Window = Window::Create();
		m_Window->SetEventCallback(BIND_EVENT_FUNC(OnEvent));
		
	}
	Application::~Application()
	{
		std::cout << "Application Destructor" << std::endl;
	}
	void Application::Run()
	{	
		while (m_isRunning)
		{
			m_Window->OnUpdate();
			for (auto it = m_LayerQueue.begin(); it != m_LayerQueue.end(); it++)
			{
				(*it)->OnUpdate();
			}
		}
	}



	/*
	* 事件函数测试区 后续用Layer替代
	*/
	bool OnKeyDownTest(OnKeyDownEvent& event)
	{
		NOVA_INFO("Click Keyboard");
		return true;
	}


	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		
		dispatcher.Dispatch<OnKeyDownEvent>(OnKeyDownTest);
		dispatcher.Dispatch<OnWindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClose));

		for(auto it = m_LayerQueue.begin();it!=m_LayerQueue.end();it++)
		{
			(*it)->OnEvent(event);
			if(event.isHandled)
				break;
		} 

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerQueue.PushLayer(layer);
	}

	void Application::PopLayer(Layer* layer)
	{
		m_LayerQueue.PopLayer(layer);
	}

	bool Application::OnWindowClose(Event& event)
	{
		NOVA_INFO("Window Close Event");
		m_isRunning = false;
		return false;
	}


}
