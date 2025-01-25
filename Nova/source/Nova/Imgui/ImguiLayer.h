#pragma once
#include <Nova/Core/Base.h>
#include <Nova/Core/Layer.h>
namespace Nova
{
	class NOVA_API ImguiLayer:public Layer
	{
	public:
		ImguiLayer();
		~ImguiLayer();
		void OnAttach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;
	private:
		float m_Time = 0.0f;

	};
}


