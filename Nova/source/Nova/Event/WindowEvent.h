#pragma once
#include <Nova/Event/Event.h>
namespace Nova
{
	class OnWindowCloseEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(EventType::OnWindowClose);
		EVENT_CLASS_CATAGORY(WindowEventCatagory);
		OnWindowCloseEvent() 
		{

		}
	};

}