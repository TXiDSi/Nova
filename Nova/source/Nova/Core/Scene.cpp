#include "NovaPch.h"
#include"Nova/Core/Scene.h"

namespace Nova
{
	void Scene::Update()
	{
        for (auto& gameObject : m_GameObjects)
        {
            gameObject->Update();
        }
	}
	std::shared_ptr<GameObject> Scene::CreateGameObject()
	{
		auto gameObject = std::make_shared<GameObject>();
        gameObject->SetGameObjectPtr(gameObject);
		m_GameObjects.push_back(gameObject);
		return gameObject;
	}
}