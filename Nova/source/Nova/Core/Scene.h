#pragma once

#include "vector"
#include "Nova/Core/GameObject.h"

namespace Nova
{
	class Scene
	{
	public:
		void Update();
		std::shared_ptr<GameObject> CreateGameObject();
	private:
		std::vector<std::shared_ptr<GameObject>> m_GameObjects;
	};
}