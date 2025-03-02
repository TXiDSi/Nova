#pragma once

#include "Nova/Component/Transform.h"
namespace Nova
{

	/*
	* 1.基础功能
	* 有Transform接口 可以获取相机变换矩阵
	* 可以更改投影矩阵 ，应当有对于的预设 但是为了简单先做透视投影
	*/
	class Camera
	{
	public:
		Camera();
        ~Camera();

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