#pragma once
#include "Nova/Event/Event.h"
#include "functional"
namespace Nova
{
	/*
	* 窗口参数，这些参数是全平台通用的
	*/
	struct WindowProps
	{
		char* title = "default";
		unsigned int width = 1920;
		unsigned int height = 1080; 
	};
	/*
	* 接口，主要负责 窗口的创建与销毁
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
