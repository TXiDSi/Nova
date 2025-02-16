#pragma once

#include "Event.h"

namespace Nova {

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			:m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		EVENT_CLASS_TYPE(EventType::OnWindowResize)
		EVENT_CLASS_CATAGORY(WindowEventCatagory)
	private:
		unsigned int m_Width, m_Height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(EventType::OnWindowClose)
		EVENT_CLASS_CATAGORY(AppEventCatagory)
	};

	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(EventType::OnAppTick)
		EVENT_CLASS_CATAGORY(AppEventCatagory)
	};

	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(EventType::OnAppUpdate)
		EVENT_CLASS_CATAGORY(AppEventCatagory)
	};

	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(EventType::OnAppRender)
		EVENT_CLASS_CATAGORY(AppEventCatagory)
	};
}