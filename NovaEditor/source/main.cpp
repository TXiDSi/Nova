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
		if (Nova::Input::IsKey(NOVA_KEY_SPACE))
		{
			NOVA_INFO("Click Space");
		}
	}

};

class NovaEditor :public Nova::Application
{
public:
	NovaEditor()
	{
		TestLayer* test = new TestLayer("Test");
		PushLayer(test);
	}

	~NovaEditor()
	{
		
	}
};
Nova::Application* Nova::CreateApplication()
{
	return new NovaEditor();
}
