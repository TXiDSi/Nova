#pragma once
#include <Nova/Core/Base.h>
#include <Nova/Event/Event.h>
namespace Nova
{
	/*
	* 一个对外调用的接口，应该实现传递事件以及Update的功能
	* Layer设计初衷是解决Event事件穿透问题，除此之外的任何功能都是拓展
	*/
	class NOVA_API Layer
	{
	public:
		Layer(const char* name);
		virtual void OnAttach() {};
		virtual void OnDetach() {};

		virtual void OnEvent(Event& event) {};
		virtual void OnUpdate() {};
		const char* GetName() const { return m_name; }
	private:
		const char* m_name;
	};
}


