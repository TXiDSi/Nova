#include "NovaPch.h"
#include "Nova/Core/GameObject.h"
#include "Nova/Core/Component.h"


namespace Nova
{
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


	void GameObject::SetGameObjectPtr(std::shared_ptr<GameObject> ptr)
	{
        m_GameObjectPtr = ptr;
	}
	std::shared_ptr<GameObject> GameObject::GetGameObjectPtr()
	{
		return m_GameObjectPtr;
	}
}