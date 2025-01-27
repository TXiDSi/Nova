#pragma once
#include <Nova/Event/Event.h>
namespace Nova
{
	class WindowCloseEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(EventType::OnWindowClose);
		EVENT_CLASS_CATAGORY(WindowEventCatagory);
		WindowCloseEvent() 
		{

		}
	};

	class WindowResizeEvent :public Event
	{
	public:
		EVENT_CLASS_TYPE(EventType::OnWindowResize);
		EVENT_CLASS_CATAGORY(WindowEventCatagory);
		WindowResizeEvent(unsigned int width, unsigned int height) :m_Width(width), m_Height(height)
		{

		}
		int GetWidth() const
		{
			return m_Width;
		}
		int GetHeight() const
		{
			return m_Height;
		}
	protected:
		int m_Width, m_Height;
	};

}