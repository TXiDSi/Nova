#include "NovaPch.h"
#include"Nova/Core/Scene.h"

#include "json/json.h"

#include "iostream"
#include "fstream"
#include "filesystem"

namespace Nova
{
	void Scene::Update()
	{
        for (auto& [key,gameObject] : m_GameObjects)
        {
            gameObject->Update();
        }
	}
	std::shared_ptr<GameObject> Scene::CreateGameObject()
	{
		auto gameObject = std::make_shared<GameObject>();
		gameObject->id = m_GameObjectID++;
        gameObject->SetGameObjectPtr(gameObject);
		m_GameObjects[gameObject->id] = gameObject;
		return gameObject;
	}
	std::unordered_map<int,std::shared_ptr<GameObject>>& Scene::GetGameObjects()
	{
		return m_GameObjects;
	}

	Json::Value Scene::ToJson()
	{
		Json::Value root;
		for (auto& [key,gameObject]:m_GameObjects)
		{
			root[gameObject->id] = gameObject->ToJson();
			root[gameObject->id]["name"] = gameObject->name;
		}
		return root;
	}
	void Scene::FromJson(const Json::Value& root)
	{
		for (auto it = root.begin(); it != root.end(); ++it) {
			int key = it.key().asInt();  
			const Json::Value& value = *it;

			if(m_GameObjects.find(key) != m_GameObjects.end())
				continue;

            auto gameObject = CreateGameObject();
            gameObject->FromJson(value);
			gameObject->name = value["name"].asString();
			gameObject->id = key;
		}
	}

	void Scene::SaveScene(const std::string& path, const std::string& name)
	{
		auto root = ToJson();
		std::filesystem::create_directories(path);
		std::string filePath = path + "/" + name + ".json";
		std::ofstream file(filePath);
        file << root;
        file.close();
	}

	void Scene::FindCameraFromGameObjects()
	{
        for (auto& [key,gameObject] : m_GameObjects)
        {
            if (gameObject->GetComponent<Camera>())
            {
                mainCamera = gameObject->GetComponent<Camera>();
                break;
            }
        }
	}
}