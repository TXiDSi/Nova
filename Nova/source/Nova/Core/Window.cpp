

#include "NovaPch.h"
#include "Nova/Core/Window.h"
#include "Nova/Platform/Windows/WindowsWindow.h"
namespace Nova
{
	Window* Window::Create(const WindowProps& props)
	{
		Window* window = new WindowsWindow(props);
        return window;
		return nullptr;
	}

}
