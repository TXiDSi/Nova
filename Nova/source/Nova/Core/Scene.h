#pragma once

#include "vector"
#include "Nova/Core/GameObject.h"
#include "Nova/Component/Light.h"
#include "Nova/Component/Camera.h"

namespace Nova
{
	class Scene
	{
	public:
		void Update();

		std::shared_ptr<GameObject> CreateGameObject();
		std::unordered_map<int, std::shared_ptr<GameObject>>& GetGameObjects();

		Json::Value ToJson();
		void FromJson(const Json::Value &value);
		
		void SaveScene(const std::string& path,const std::string &name);

		//Temp Load Camera TODO::TianXin
		void FindCameraFromGameObjects();
	public:
		std::shared_ptr<Camera> mainCamera;
		std::shared_ptr<DirectionalLight>  light;
	private:
		std::unordered_map<int, std::shared_ptr<GameObject>> m_GameObjects;
		unsigned int m_GameObjectID = 0;
	};
}