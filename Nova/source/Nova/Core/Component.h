#pragma once
#include "memory"
namespace Nova
{
	class GameObject;
	class Component
	{
	public:
		std::shared_ptr<GameObject> gameObject;
	public:
		Component(){ }
		void SetGameObject(std::shared_ptr<GameObject> go)
		{
			gameObject = go;
		}
		virtual ~Component() = default;

		// -----生命周期函数------
		virtual void Awake()		{ }
        virtual void Start()		{ }
		virtual void Update()		{ }
		virtual void OnEnable()		{ }
        virtual void OnDisable()	{ }
        virtual void OnDestroy()	{ }
		// ---------------------
	};


}
