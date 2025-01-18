#pragma once
extern Nova::Application* Nova::CreateApplication();

int main()
{
	Nova::Log::Init();
	NOVA_WARN("Hello World!");
	Nova::Application *app = Nova::CreateApplication();
	app->Run();
	delete app;
}
