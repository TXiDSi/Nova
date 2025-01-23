#pragma once
#include "Nova/Core/Base.h"
#include "Nova/Event/Event.h"
#include "Nova/Core/Window.h"

namespace Nova
{
	/*
	* ����Ӧ�ñ���ĳ���
	* ������ѭ�����¼��ַ�����Ҫ�߼����
	*/
	class NOVA_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& event);

	private:
		Window* m_Window;


	};
	Application* CreateApplication();

	
}


