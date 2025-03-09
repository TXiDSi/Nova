#pragma once
#include "memory"
#include "typeindex"
#include "unordered_map"
#include "Nova/Component/Transform.h"
namespace Nova
{
	class Component;
	class GameObject
	{
	public:
		GameObject() = default;
		
		template<typename T,typename... Args>
		void AddComponent(Args&&... args)
		{
			auto component = std::make_shared<T>(std::forward<Args>(args)...);
			m_Components[typeid(T)] = component;
			component->SetGameObject(GetGameObjectPtr());
		}
		template<typename T>
		std::shared_ptr<T> GetComponent()
		{
			auto it = m_Components.find(typeid(T));
			if (it != m_Components.end()) {
				return std::static_pointer_cast<T>(it->second);
			}
			return nullptr;
		}

		//------生命周期函数-------
		void Awake();
		void Start();
        void Update();
        void OnDestroy();
        void OnDisable();
        void OnEnable();
		//------------------------

		void SetGameObjectPtr(std::shared_ptr<GameObject> ptr);
		std::shared_ptr<GameObject> GetGameObjectPtr();

	public:
		std::shared_ptr<Transform> transform;
	private:
		std::unordered_map<std::type_index,std::shared_ptr<Component>> m_Components;
		std::shared_ptr<GameObject> m_GameObjectPtr;
		
	};
}