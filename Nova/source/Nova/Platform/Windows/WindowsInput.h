#pragma once

#include <Nova/Core/Input.h>
namespace Nova
{
	class WindowsInput : public Input
	{
		// ͨ�� Input �̳�
		virtual bool IsKeyImpl(int keycode) override;
		virtual bool IsMouseButtonImpl(int button) override;
	};
}


