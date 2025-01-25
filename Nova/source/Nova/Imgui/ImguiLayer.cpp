#include "ImguiLayer.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "Nova/Platform/Opengl/imgui_impl_opengl3.h"
#include <Nova/Core/Application.h>
#include "Nova/Core/Log.h"
namespace Nova
{
	ImguiLayer::ImguiLayer(): Layer("ImguiLayer")
	{
	}
	ImguiLayer::~ImguiLayer()
	{
	}
	void ImguiLayer::OnAttach()
	{
		NOVA_INFO("ImguiLayer::OnAttach");
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO &io = ImGui::GetIO();
		//io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		//io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		ImGui_ImplOpenGL3_Init("#version 410");
	}
	void ImguiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow()->GetWidth(),app.GetWindow()->GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glViewport(0, 0, app.GetWindow()->GetWidth(), app.GetWindow()->GetHeight());


	}
	void ImguiLayer::OnEvent(Event& event)
	{
	}
}