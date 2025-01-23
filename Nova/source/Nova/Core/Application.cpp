#include "NovaPch.h"
#include "Nova/Core/Log.h"
#include "Application.h"
#include "Nova/Core/Window.h"
#include "Nova/Event/KeyEvent.h"
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
		while (true)
		{
			m_Window->OnUpdate();
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

	}


}
