#pragma once
#include<Nova/Core/Layer.h>
#include<Nova/Core/Base.h>
#include<vector>

namespace Nova
{
	/*
	* Layer�������������Queue͹��Layer�����˳���ִ��˳��
	* �ȱ���ӵ�Layer���ȱ�ִ��
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


