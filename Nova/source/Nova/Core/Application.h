#pragma once
#include "Nova/Core/Base.h"
#include "Nova/Event/Event.h"
#include "Nova/Core/Window.h"
#include "Nova/Core/LayerQueue.h"

namespace Nova
{
	/*
	* 代表应用本体的抽象
	* 管理主循环、事件分发等主要逻辑框架
	*/
	class NOVA_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		bool OnWindowClose(Event& event);

	private:
		Window* m_Window;
		LayerQueue m_LayerQueue;
		bool m_isRunning = true;


	};
	Application* CreateApplication();

	
}


