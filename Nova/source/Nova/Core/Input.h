#pragma once
#include <Nova/Core/Base.h>
namespace Nova
{

	class NOVA_API Input
	{
	public:
		static bool IsKey(int keycode){ return s_Instance->IsKeyImpl(keycode);}
		static bool IsMouseButton(int button) { return s_Instance->IsMouseButtonImpl(button); }
	protected:
		virtual bool IsKeyImpl(int keycode) = 0;
		virtual bool IsMouseButtonImpl(int button) = 0;
	private:
		static Input* s_Instance;
	};

}