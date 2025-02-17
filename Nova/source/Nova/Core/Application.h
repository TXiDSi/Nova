#pragma once

#include "Base.h"

#include "Window.h"
#include "Nova/Core/LayerQueue.h"
#include "Nova/Event/Event.h"
#include "Nova/Event/WindowEvent.h"

#include "Nova/Core/Timestep.h"

#include "Nova/ImGui/ImGuiLayer.h"

namespace Nova {

	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerQueue m_LayerQueue;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}