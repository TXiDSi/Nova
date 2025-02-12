#pragma once
#include "Nova/Imgui/ImguiLayer.h"
#include "Nova/Core/Base.h"
#include "Nova/Event/Event.h"
#include "Nova/Core/Window.h"
#include "Nova/Core/LayerQueue.h"
#include <Nova/Renderer/Shader.h>
#include <Nova/Renderer/VertexArray.h>

namespace Nova
{
	/*
	* 代表应用本体的抽象
	* 管理主循环、事件分发等主要逻辑框架
	*/
	class NOVA_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		Window* GetWindow() { return m_Window; }
		bool OnWindowClose(Event& event);

		static Application& Get() { return *s_Instance; }

	private:
		Window* m_Window;
		LayerQueue m_LayerQueue;
		bool m_isRunning = true;

		static Application* s_Instance;

		ImguiLayer* m_ImguiLayer;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;

	};
	Application* CreateApplication();

	
}


