#pragma once

#include <Nova/Core/Input.h>
namespace Nova
{
	class WindowsInput : public Input
	{
		// Í¨¹ý Input ¼Ì³Ð
		virtual bool IsKeyImpl(int keycode) override;
		virtual bool IsMouseButtonImpl(int button) override;
	};
}


