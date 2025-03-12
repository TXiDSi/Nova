#include "vector"
#include "json/json.h"

#include "NovaPch.h"
#include "Nova/Core/GameObject.h"
#include "Nova/Core/Component.h"

#include "Nova/Component/Transform.h"
#include "Nova/Component/MeshRenderer.h"
#include "Nova/Component/Camera.h"

namespace Nova
{
	GameObject::GameObject(std::string name)
	{
		this->name = name;
		transform = this->AddComponent<Transform>();
	}
	void GameObject::Awake()
	{
		for (auto& [key,component] : m_Components)
		{
			component->Awake();
		}
	}
	void GameObject::Start()
	{
        for (auto& [key, component] : m_Components)
        {
            component->Start();
        }
	}
	void GameObject::Update()
	{
        for (auto& [key, component] : m_Components)
        {
            component->Update();
        }
	}
	void GameObject::OnDestroy()
	{
        for (auto& [key, component] : m_Components)
        {
            component->OnDestroy();
        }
	}
	void GameObject::OnDisable()
	{
        for (auto& [key, component] : m_Components)
        {
            component->OnDisable();
        }
	}
	void GameObject::OnEnable()
	{
        for (auto& [key, component] : m_Components)
        {
            component->OnEnable();
        }
	}
	void GameObject::OnImGui()
	{
		ImGui::Text("Name:");
		ImGui::SameLine();
		char buffer[256];
		strncpy(buffer, name.c_str(), sizeof(buffer));
		buffer[sizeof(buffer) - 1] = '\0';
		if (ImGui::InputText("##Name", buffer, sizeof(buffer)))
		{
			name = std::string(buffer);
		}

        for (auto& [key, component] : m_Components)
        {
            component->OnImGui();
        }
	}


	Json::Value GameObject::ToJson()
	{
		Json::Value root;
		for (auto [key, value] : m_Components)
		{
			std::string name;
			if (key == typeid(Transform))
			{
				name = "Transform";
			}
            else if (key == typeid(MeshRenderer))
            {
                name = "MeshRenderer";
            }
            else if (key == typeid(Camera))
            {
                name = "Camera";
            }

			if (name.empty())
				return root;
			
			root[name] = value->ToJson();
		}
		return root;
	}

	void GameObject::FromJson(const Json::Value& root)
	{
		for (auto it = root.begin(); it != root.end(); ++it)
		{
			std::string key = it.key().asString();
			Json::Value value = *it;

			if (key == "Transform")
			{
                transform = AddComponent<Transform>();
                transform->FromJson(value);
				transform->gameObject = GetGameObjectPtr();
			}
            else if (key == "MeshRenderer")
            {
                auto meshRenderer = AddComponent<MeshRenderer>();
                meshRenderer->FromJson(value);
                meshRenderer->gameObject = GetGameObjectPtr();
            }
            else if (key == "Camera")
            {
                auto camera = AddComponent<Camera>();
                camera->FromJson(value);
                camera->gameObject = GetGameObjectPtr();
            }
		}

	}



	void GameObject::SetGameObjectPtr(std::shared_ptr<GameObject> ptr)
	{
        m_GameObjectPtr = ptr;
	}
	std::shared_ptr<GameObject> GameObject::GetGameObjectPtr()
	{
		return m_GameObjectPtr;
	}
}