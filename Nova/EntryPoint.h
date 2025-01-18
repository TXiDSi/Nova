#pragma once

extern Nova::Application* Nova::CreateApplication();

int main()
{
	Nova::Application *app = Nova::CreateApplication();
	app->Run();
	delete app;
}
