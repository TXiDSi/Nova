#include "NovaPch.h"
#include "Nova/Core/Log.h"
#include "Nova/Core/Input.h"
#include "Application.h"
#include "Nova/Core/Window.h"
#include "Nova/Event/KeyEvent.h"
#include "Nova/Event/WindowEvent.h"
#include "Nova/Imgui/ImguiLayer.h"
#include <functional>


#include "glad/glad.h"

namespace Nova
{
	Application* Application::s_Instance = nullptr;
	Application::Application()
	{
		s_Instance = this;
		//创建窗口
		m_Window = Window::Create();
		m_Window->SetEventCallback(BIND_EVENT_FUNC(OnEvent));

		m_ImguiLayer = new ImguiLayer();
		PushLayer(m_ImguiLayer);

		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
		
	}
	Application::~Application()
	{
		std::cout << "Application Destructor" << std::endl;
	}
	void Application::Run()
	{	
		while (m_isRunning)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_BlueShader->Bind();
			m_SquareVA->Bind();
			glDrawElements(GL_TRIANGLES, m_SquareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_Shader->Bind();
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerQueue)
				layer->OnUpdate();


			m_Window->OnUpdate();
		}
	}



	/*
	* 事件函数测试区 后续用Layer替代
	*/
	bool OnKeyDownTest(OnKeyDownEvent& event)
	{
		NOVA_INFO("Click Keyboard");
		return true;
	}


	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		
		dispatcher.Dispatch<OnKeyDownEvent>(OnKeyDownTest);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClose));

		for(auto it = m_LayerQueue.begin();it!=m_LayerQueue.end();it++)
		{
			(*it)->OnEvent(event);
			if(event.isHandled)
				break;
		} 

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerQueue.PushLayer(layer);
	}

	void Application::PopLayer(Layer* layer)
	{
		m_LayerQueue.PopLayer(layer);
	}

	bool Application::OnWindowClose(Event& event)
	{
		NOVA_INFO("Window Close Event");
		m_isRunning = false;
		return false;
	}


}
