#pragma once
#include "Application.h"

extern Nova::Application* CreateApplication();

int main(int argc, char** argv)
{
	Nova::Application *app = CreateApplication();
	app->Run();
	return 0;
}