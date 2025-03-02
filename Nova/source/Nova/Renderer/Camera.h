#pragma once

#include "Nova/Component/Transform.h"
namespace Nova
{

	/*
	* 1.��������
	* ��Transform�ӿ� ���Ի�ȡ����任����
	* ���Ը���ͶӰ���� ��Ӧ���ж��ڵ�Ԥ�� ����Ϊ�˼�����͸��ͶӰ
	*/
	class Camera
	{
	public:
		Camera();
        ~Camera();

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
	public:
		Transform transform;
	private:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        float m_Fov;
        float m_Aspect;
        float m_Near;
        float m_Far;
	};
}