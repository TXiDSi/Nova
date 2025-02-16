#pragma once

#include "Nova/Core/Log.h"

extern Nova::Application* Nova::CreateApplication();

int main()
{
	Nova::Log::Init();
	NOVA_INFO("Welcome to NOVA");
	Nova::Application *app = Nova::CreateApplication();
	app->Run();
	delete app;
}
