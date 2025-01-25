#include <Nova.h>

class TestLayer :public Nova::Layer
{
public:
	TestLayer(const char* name): Layer(name)
	{
		NOVA_INFO("Test Layer Constructer");
	}
	void OnUpdate()override
	{
	}

};

class NovaEditor :public Nova::Application
{
public:
	NovaEditor()
	{
		//TestLayer* test = new TestLayer("Test");
		//PushLayer(test);
		PushLayer(new Nova::ImguiLayer());
	}

	~NovaEditor()
	{
		
	}
};
Nova::Application* Nova::CreateApplication()
{
	return new NovaEditor();
}
