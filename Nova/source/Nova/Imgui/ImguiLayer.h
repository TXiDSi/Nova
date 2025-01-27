#pragma once
#include <Nova/Core/Base.h>
#include <Nova/Core/Layer.h>
#include <Nova/Event/KeyEvent.h>
#include <Nova/Event/MouseEvent.h>
#include <Nova/Event/WindowEvent.h>
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

		// ImguiÊÂ¼þ
		bool OnMouseButtonDownEvent(MouseButtonDownEvent& e);
		bool OnMouseButtonUpEvent(MouseButtonUpEvent& e);
		bool OnMouseMovedEvent(MouseMoveEvent& e);
		bool OnMouseScrolledEvent(MouseScrollEvent& e);
		//bool OnKeyPressedEvent(KeyPressedEvent& e);
		//bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		//bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);


	};
}


