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
		char* title = "Nova";
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
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void* GetNativeWindow() const = 0;

		virtual void SetEventCallback(const EventCallbackFn &callback) = 0;
		static Window* Create(const WindowProps &props = WindowProps());

	};
}
