#pragma once

#include <Nova/Event/Event.h>
namespace Nova
{
	class MouseButtonEvent :public Event
	{
	public:
		int GetMouseButton() const { return m_button; }
		EVENT_CLASS_CATAGORY(MouseEventCatagory);
	protected:
		MouseButtonEvent(const int mouseButton) :m_button(mouseButton)
		{
		}
		int m_button;
	};


	class MouseButtonDownEvent :public MouseButtonEvent
	{
	public:
		MouseButtonDownEvent(const int mouseButton) :MouseButtonEvent(mouseButton)
		{
		}
		EVENT_CLASS_TYPE(EventType::OnMouseButtonDown);
	};

	class MouseButtonUpEvent : public MouseButtonEvent
	{
	public:
		MouseButtonUpEvent(const int mouseButton) :MouseButtonEvent(mouseButton)
		{
		}
		EVENT_CLASS_TYPE(EventType::OnMouseButtonUp);
	};

	class MouseMoveEvent : public Event
	{
	public: 
		MouseMoveEvent(float x, float y) :m_x(x), m_y(y)
		{
		}
		EVENT_CLASS_CATAGORY(MouseEventCatagory);
		EVENT_CLASS_TYPE(EventType::OnMouseMove);
		float GetX() const { return m_x; }
		float GetY() const { return m_y; }
	protected:
		float m_x;
		float m_y;
	};

	class MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(float x, float y) :m_x(x), m_y(y)
		{
		}
		EVENT_CLASS_CATAGORY(MouseEventCatagory);
		EVENT_CLASS_TYPE(EventType::OnMouseScroll);
		float GetX() const { return m_x; }
		float GetY() const { return m_y; }
	protected:
		float m_x;
		float m_y;
	};


}