#include "LayerQueue.h"
#include "Nova/Core/Log.h"
namespace Nova
{

	void LayerQueue::PushLayer(Layer* layer)
	{
		m_Layers.push_back(layer);
		layer->OnAttach();
	}

	void LayerQueue::PopLayer(Layer* layer)
	{
		auto it = std::remove(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			layer->OnDetach();
		}
	}

	std::vector<Layer*>::iterator LayerQueue::begin()
	{
		return m_Layers.begin();
	}

	std::vector<Layer*>::iterator LayerQueue::end()
	{
		return m_Layers.end();
	}

	LayerQueue::~LayerQueue()
	{
		/*NOVA_INFO("LayerQueue Destructor");
		for (Layer* layer : m_Layers)
		{
			NOVA_INFO("LayerQueue Destructor: {0}", layer->GetName());
			layer->OnDetach();
			delete layer;
		}*/
			
	}

}