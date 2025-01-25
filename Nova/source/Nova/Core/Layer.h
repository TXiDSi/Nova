#pragma once
#include <Nova/Core/Base.h>
#include <Nova/Event/Event.h>
namespace Nova
{
	/*
	* һ��������õĽӿڣ�Ӧ��ʵ�ִ����¼��Լ�Update�Ĺ���
	* Layer��Ƴ����ǽ��Event�¼���͸���⣬����֮����κι��ܶ�����չ
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


