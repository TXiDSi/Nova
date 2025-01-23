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
	* �¼��Ļ���
	* 1�������¼�����
	* 2�������¼���������
	* 3�������¼���
	* 
	* �������ݶ�����չ
	*/
	class Event
	{
	public:
		bool isHandled = false;
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual EventCatagory GetEventCatagoryFlags() const = 0;

	};

	//�궨���¼�������غ����ͺ��������������д���ž�����
#define EVENT_CLASS_TYPE(type)\
static EventType GetStaticType(){return type;}\
virtual EventType GetEventType() const override {return type;}\
virtual const char* GetName() const override{return #type;}
	//�궨���¼�����
#define EVENT_CLASS_CATAGORY(catagory)\
virtual EventCatagory GetEventCatagoryFlags() const override{return catagory;}


	/*
	* �¼��ַ���
	* ����һ���¼�������Ϊ��Ҫ������¼�
	* ӵ�д�������������ģ��ƥ�������¼��ַ�����ȷ�ĺ���
	* ���������Ĳ���Ϊ��Ҫ�����¼��ĺ������䷵��ֵ�����¼��Ƿ������Ĵ������
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

