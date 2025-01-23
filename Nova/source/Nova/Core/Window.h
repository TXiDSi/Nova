#pragma once
#include "Nova/Event/Event.h"
#include "functional"
namespace Nova
{
	/*
	* ���ڲ�������Щ������ȫƽ̨ͨ�õ�
	*/
	struct WindowProps
	{
		char* title = "default";
		unsigned int width = 1920;
		unsigned int height = 1080; 
	};
	/*
	* �ӿڣ���Ҫ���� ���ڵĴ���������
	*/
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		virtual ~Window() = default;

		virtual void OnUpdate()=0;

		virtual void SetEventCallback(const EventCallbackFn &callback) = 0;
		static Window* Create(const WindowProps &props = WindowProps());

	};
}
