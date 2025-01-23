#pragma once

#include "Nova/Core/Base.h"

namespace Nova
{
	enum class EventType
	{
		None = 0,
		//WindowEvent
		OnWindowClose, OnWindowResize,
		//MouseEvent
		OnMouseMove, OnMouseButtonDown, OnMouseButtonUp,
		//KeyEvent
		OnKeyDown, OnKeyUp, OnKeyRepeat,
		//AppEvent
		OnUpdate,
	};

	enum EventCatagory
	{
		None = 0,
		AppEventCatagory = BIT(1),
		KeyboardEventCatagory = BIT(2),
		MouseEventCatagory = BIT(3),
		WindowEventCatagory = BIT(4),
	};

	/*
	* 事件的基类
	* 1、返回事件分类
	* 2、返回事件具体类型
	* 3、返回事件名
	* 
	* 其余内容都是拓展
	*/
	class Event
	{
	public:
		bool isHandled = false;
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual EventCatagory GetEventCatagoryFlags() const = 0;

	};

	//宏定义事件类型其关乎类型函数，后续方便编写，杜绝出错
#define EVENT_CLASS_TYPE(type)\
static EventType GetStaticType(){return type;}\
virtual EventType GetEventType() const override {return type;}\
virtual const char* GetName() const override{return #type;}
	//宏定义事件分类
#define EVENT_CLASS_CATAGORY(catagory)\
virtual EventCatagory GetEventCatagoryFlags() const override{return catagory;}


	/*
	* 事件分发器
	* 接受一个事件类型作为将要处理的事件
	* 拥有触发函数，根据模板匹配来让事件分发给正确的函数
	* 触发函数的参数为将要处理事件的函数，其返回值决定事件是否被完整的处理完成
	*/
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& e):m_Event(e)
		{
		}
		template<typename T,typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.isHandled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

}

