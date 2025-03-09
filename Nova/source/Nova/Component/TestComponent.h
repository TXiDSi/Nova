#pragma once
#include "Nova/Core/Log.h"
#include "Nova/Core/Component.h"
namespace Nova
{

	class TestComponent :public Component
	{
	public:
		void Update() override
		{
			NOVA_INFO("TestComponent");
		}

	};
}