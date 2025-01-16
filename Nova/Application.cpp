#include "NovaPch.h"
#include "Application.h"

namespace Nova
{
	Application::Application()
	{
		std::cout<<"Application Constructor"<<std::endl;
	}
	Application::~Application()
	{
		std::cout << "Application Destructor" << std::endl;
	}
	void Application::Run()
	{
		while (true)
		{
			std::cout << "Welcome To Nova" << std::endl;
		}
		
	}
}
