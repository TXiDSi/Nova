#pragma once
#include<Nova/Core/Layer.h>
#include<Nova/Core/Base.h>
#include<vector>

namespace Nova
{
	/*
	* Layer的容器，这里叫Queue凸显Layer的添加顺序和执行顺序
	* 先被添加的Layer最先被执行
	*/
	class LayerQueue
	{
	public:
		void PushLayer(Layer *layer);
		void PopLayer(Layer *layer);
		std::vector<Layer*>::iterator begin();
		std::vector<Layer*>::iterator end();
		virtual ~LayerQueue();
	private:
		std::vector<Layer*> m_Layers;
	};
}


