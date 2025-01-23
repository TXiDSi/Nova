#pragma once

#include "Nova/Event/Event.h"
#include "Nova/Core/Base.h"

namespace Nova {

	//键入类事件基类 记录键入数据
	class KeyEvent :public Event
	{
	public:
		EVENT_CLASS_CATAGORY(KeyboardEventCatagory);
	protected:
		KeyEvent(const int keycode):m_keycode(keycode)
		{

		}
		int m_keycode;
	};

	class OnKeyDownEvent :public KeyEvent
	{
	public:
        OnKeyDownEvent(const int keycode) :KeyEvent(keycode)
		{

		}
		EVENT_CLASS_TYPE(EventType::OnKeyDown);
	};
	class OnKeyUpEvent :public KeyEvent
	{
	public:
		OnKeyUpEvent(const int keycode) : KeyEvent(keycode)
		{

		}
		EVENT_CLASS_TYPE(EventType::OnKeyUp);
	};

}