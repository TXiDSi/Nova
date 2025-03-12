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

		// ͨ�� Component �̳�
		Json::Value ToJson() override;
		void FromJson(const Json::Value& json) override;

		glm::mat4 GetViewMatrix();
		glm::mat4 GetProjectionMatrix();

		/*
		* ���������ͶӰ����
		* fov ��ֱ������ӽǽǶ�
		* aspect ��߱�
		* near ���������ľ���
		* far �������Զ�ľ���
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