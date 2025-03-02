#include <NovaPch.h>
#include <Nova/Renderer/Camera.h>

namespace Nova
{
	Camera::Camera():m_Fov(glm::radians(45.0f)), m_Aspect(16.0f / 9.0f),
        m_Near(0.1f), m_Far(1000.0f),
		transform()
	{
        m_ProjectionMatrix = glm::perspective(m_Fov, m_Aspect, m_Near, m_Far);
	}
	Camera::~Camera()
	{
	}
	glm::mat4 Camera::GetViewMatrix()
	{
		glm::vec3 position = transform.GetPosition();
		glm::vec3 forward = transform.GetForward();
		glm::vec3 up = transform.GetUp();

		return glm::lookAt(position, position + forward, up);
	}
	glm::mat4 Camera::GetProjectionMatrix()
	{
        return m_ProjectionMatrix;
	}
	void Camera::SetProjectionParameters(float fov, float aspect, float nearClip, float farClip)
	{
        m_Fov = fov;
        m_Aspect = aspect;
        m_Near = nearClip;
        m_Far = farClip;
        m_ProjectionMatrix = glm::perspective(m_Fov, m_Aspect, m_Near, m_Far);
	}
}