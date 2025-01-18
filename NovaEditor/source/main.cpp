#include <Nova.h>

class NovaEditor :public Nova::Application
{
public:
	NovaEditor()
	{

	}

	~NovaEditor()
	{

	}
};
Nova::Application* Nova::CreateApplication()
{
	return new NovaEditor();
}
