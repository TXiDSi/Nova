#pragma once
#include <Nova/Core/Base.h>
#include <Nova/Core/Layer.h>
#include <Nova/Event/KeyEvent.h>
#include <Nova/Event/MouseEvent.h>
#include <Nova/Event/WindowEvent.h>
namespace Nova
{
	class NOVA_API ImGuiLayer:public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;

	};
}


