#pragma once
#include "Nova/Core/Component.h"
#include "glm/glm.hpp"
namespace Nova
{
	class Camera:public Component
	{
	public:
		Camera();
		~Camera();

		// 通过 Component 继承
		Json::Value ToJson() override;
		void FromJson(const Json::Value& json) override;

		glm::mat4 GetViewMatrix();
		glm::mat4 GetProjectionMatrix();

		/*
		* 设置相机的投影参数
		* fov 垂直方向的视角角度
		* aspect 宽高比
		* near 离相机最近的距离
		* far 离相机最远的距离
		*/
		void SetProjectionParameters(float fov, float aspect, float nearClip, float farClip);
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		float m_Fov;
		float m_Aspect;
		float m_Near;
		float m_Far;
	};



}