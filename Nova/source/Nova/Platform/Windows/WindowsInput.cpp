#include "WindowsInput.h"
#include "Nova/Core/Application.h"
#include "GLFW/glfw3.h"
namespace Nova
{
	Input* Input::s_Instance = new WindowsInput();
	bool WindowsInput::IsKeyImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow()->GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool WindowsInput::IsMouseButtonImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow()->GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}
}
